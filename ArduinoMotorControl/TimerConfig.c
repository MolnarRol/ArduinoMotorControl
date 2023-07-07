#include "TimerConfig.h"

uint16_t g_TIM0_ov = 0;

void SetPwmDuty( float dutyPerc )
{
  if( dutyPerc > 100.0f || dutyPerc < 0.0f ) return;

  const uint16_t top = ICR1;
  const float duty_step = GetStepPWM( top );
  const float duty_step_perc = 1.0f / duty_step;

  if( dutyPerc < duty_step_perc )
  {
    OCR1A = 0;
    DisablePWM();
    setPinHighPWM();    
  }
  else if( dutyPerc > (100.0f - duty_step_perc) )
  {
    OCR1A = top;
    DisablePWM();
    setPinLowPWM();
  }
  else
  {
    OCR1A = (uint16_t)( duty_step * dutyPerc ) - 1;
    EnablePWM();
  }   
};

float GetPwmDuty(){
  if( OCR1A == 0 ) return 0.0f;
  return 100.0f * (float)( OCR1A + 1 ) / (float)( ICR1 + 1 ); 
};

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
  ICR1 = 799;           /*magic number, use define with frequency and another that will calculate this value */
  OCR1A = 0;
};

void PeriodicInterruptConfig()
{
  TCCR2A = 0;
  TCCR2B = 0;
  TCCR2A |= 0b00000010;   // Enable Clear Timer on Compare Match
  TCCR2B |= 0b00000101;   // Enable CTC and set prescaler to 128
  TIMSK2 |= 0b00000010;   // Enable interupt from compare match –> timer reset
  OCR2A = 249;            /*magic number, use define with frequency and another that will calculate this value */
  TCNT2 = 0;
};

/* there are several ways of changing bits in registers, maybe stick with one way is better */
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

