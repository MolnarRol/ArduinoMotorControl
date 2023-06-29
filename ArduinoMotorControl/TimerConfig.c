#include "TimerConfig.h"

uint16_t g_TIM0_ov = 0;

pulseBuffersTypeDef PulseBuffers = {
  .idx = 0,
  .buffer[0].pulseIdx = 0,
  .buffer[1].pulseIdx = 0
};

inline void writePulseBuff( uint32_t val )
{
  pulseTypeDef* p_buff = &PulseBuffers.buffer[ PulseBuffers.idx ];
  p_buff->pulses[ p_buff->pulseIdx++ ] = val;
  if( p_buff->pulseIdx == PULSES_MAX ) p_buff->pulseIdx = 0;
};

inline void switchPulseBuff()
{
  if( PulseBuffers.idx == 0 ) PulseBuffers.idx = 1;
  else PulseBuffers.idx = 0;
};

float getRPMfromPulses()
{
  uint8_t buff_i;
  static float l_val = 0.0f;

  if( PulseBuffers.idx == 0 ) buff_i = 1;
  else buff_i = 0;

  uint32_t cnt_avg = calcTimCntAVG( PulseBuffers.buffer[ buff_i ].pulses, PulseBuffers.buffer[ buff_i ].pulseIdx );

  uint32_t cnt_filtered = filter_1stOrder_r32( cnt_avg, l_val, 2.0f , FIR_TIME );
  l_val = cnt_filtered;

  PulseBuffers.buffer[ buff_i ].pulseIdx = 0;
  return calcRPM( cnt_filtered );
};

float filter_1stOrder_r32(float r32ActualValue, float r32SmoothedValue, float r32SamplingTime_ms, float r32FilterTime_ms) {

    float r32FilterCoef;

    r32FilterCoef = r32SamplingTime_ms/(r32SamplingTime_ms+r32FilterTime_ms);
    return (r32FilterCoef*r32ActualValue + (1-r32FilterCoef)*(r32SmoothedValue));

}

inline float calcRPM( const uint32_t cnt )
{
  float delta_us = (float)cnt * TIM_STEP_us;
  float cnt_per_rev = 60e6f / (float)( ENC_N_PULSES * delta_us );
  return cnt_per_rev;
};

void SetPwmDuty( float dutyPerc )
{
  if( dutyPerc > 100.0f || dutyPerc < 0.0f ) return;

  const uint16_t TOP = ICR1;
  const float DUTY_STEP = GetStepPWM( TOP );
  const float DUTY_STEP_PERC = 1.0f / DUTY_STEP;

  if( dutyPerc < DUTY_STEP_PERC )
  {
    OCR1A = 0;
    DisablePWM();
    setPinHighPWM();    
  }
  else if( dutyPerc > (100.0f - DUTY_STEP_PERC) )
  {
    OCR1A = TOP;
    DisablePWM();
    setPinLowPWM();
  }
  else
  {
    OCR1A = (uint16_t)( DUTY_STEP * dutyPerc ) - 1;
    EnablePWM();
  }   
};

float GetPwmDuty(){
  if( OCR1A == 0 ) return 0.0f;
  return 100.0f * (float)( OCR1A + 1 ) / (float)( ICR1 + 1 ); 
};

/*
  For reading risinge edge of a pulse
*/
// void PulseCaptureConfig()
// {
//   DDRB |= 0 << DDB4;  // Enable clock on T0 pin (D4)
//   TCCR0A = 0;
//   TCCR0B = 0;
//   TCCR0B |= 0b111;    // Enable external clock source on T0 pin. Clock on rising edge
//   TCNT0 = 0;
// };

void PulseCaptureConfig()
{
  /*
    Free running timer config
  */
  TCCR0A = 0;
  TCCR0B = 0;
  TCCR0A |= 0b00000010;      // CTC
  TCCR0B |= 0b00000001;    // Prescaling by 1
  OCR0A = 255;
  TIMSK0 |= ( 1 << (OCIE0A) );

  /*
    Pinchange interrupt on D4 (PORTD 4) PCINT20
  */
  PCICR |= 1 << (PCIE2);
  PCMSK2 |= 1 << (PCINT20);
};

void PwmConfig()
{
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1A |= 0b00000010; // Enable fast PWM on channel A
  TCCR1B |= 0b00011001; // Enable fast PWM with no prescaling
  ICR1 = 799;
  OCR1A = 0;
};

void PeriodicInterruptConfig()
{
  TCCR2A = 0;
  TCCR2B = 0;
  TCCR2A |= 0b00000010;   // Enable Clear Timer on Compare Match
  TCCR2B |= 0b00000101;   // Enable CTC and set prescaler to 128
  TIMSK2 |= 0b00000010;   // Enable interupt from compare match –> timer reset
  OCR2A = 249;
  TCNT2 = 0;
};

inline void DisablePWM()
{
  TCCR1A &= ~(0b11000000);   // Turn of PWM
  
};

inline void EnablePWM()
{  
  TCCR1A |= 0b11000000;    // turn on PWM
};

inline void setPinHighPWM()
{
  PORTB |= (1 << 1 );    // set port to logic low
};

inline void setPinLowPWM()
{
  PORTB &= ~(1 << 1 );    // set port to logic low
};

inline void EnablePWM_HiZ()
{
  DDRB &= ~(1 << DDB1);
}

inline void DisablePWM_HiZ()
{
  DDRB |= 1 << DDB1;
};

// Fix exact duty
float GetStepPWM( const uint16_t TOP )
{
  return ((float)TOP + 1.0f ) / 100.0f;
};

inline uint32_t readPulseCount()
{
  uint32_t pulses = OCR0A * g_TIM0_ov;
  pulses += TCNT0;
  TCNT0 = 0;
  g_TIM0_ov = 0;    
  return pulses;
};

uint32_t calcTimCntAVG( uint32_t* values, uint8_t len )
{
  if( len == 0 ) return 4294967295;
  uint32_t sum = 0;
  for( uint32_t i = 0; i < len; i++ )
  {
    sum += values[i];
  }
  return sum / len;
};