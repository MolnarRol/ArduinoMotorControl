#include "../inc/Timers.h"

/// Timer 0 overflow counter global variable.
/// Variable is used to increase limited timer resolution to more then 8 bits. Value is incremented by ISR( TIMER0_COMPA_vect ).
/// Variable is read and written to 0 by readPulseCount() function.
uint16_t g_TIM0_ov = 0;
float g_saved_duty = 0.0f;

/**
  @brief Function that configures Timer 1 as PWM output with fixed frequency(20kHz).
*/
void PwmConfig()
{
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1A |= 0b00000010; // Enable fast PWM on channel A
  TCCR1B |= 0b00011001; // Enable fast PWM with no prescaling
  ICR1 = 799;           /*magic number, use define with frequency and another that will calculate this value */
  OCR1A = 0;
};

/**
  @brief Function calculates minimum possible step of duty cycle[%].
  @param TOP Maximum value of timer counter before overflow or timer counter reset.
  @return Minimum possible step of duty cycle[%].
*/
static float GetStepPWM( const uint16_t TOP )
{
  return ((float)TOP + 1.0f ) / 100.0f;
};

/**
  @brief Function for setting PWM duty cycle
  @param dutyPerc Desired PWM duty cycle [%]
*/
void SetPwmDuty( const float dutyPerc )
{
  if( dutyPerc > 100.0f || dutyPerc < 0.0f ) return;

  const uint16_t top = ICR1;
  const float duty_step = GetStepPWM( top );
  const float duty_step_perc = 1.0f / duty_step;

  if( dutyPerc < duty_step_perc )
  {
    OCR1A = 0;
    DisablePWM();
    #if ( LOGIG_POLARITY == ACTIVE_HIGH )
      setPinLowPWM();
    #elif ( LOGIC_POLARITY == ACTIVE_LOW )
      setPinHighPWM();   
    #endif 
  }
  else if( dutyPerc > (100.0f - duty_step_perc) )
  {
    OCR1A = top;
    DisablePWM();
    #if ( LOGIG_POLARITY == ACTIVE_HIGH )
      setPinHighPWM();  
    #elif ( LOGIC_POLARITY == ACTIVE_LOW )
      setPinLowPWM(); 
    #endif
  }
  else
  {
    OCR1A = (uint16_t)( duty_step * dutyPerc ) - 1;
    EnablePWM();
  }   
};

/**
  @brief Function for getting current PWM duty cycle
  @return PWM duty cycle [%]
*/
float GetPwmDuty(){
  if( OCR1A == 0 ) return 0.0f;
  return 100.0f * (float)( OCR1A + 1 ) / (float)( ICR1 + 1 ); 
};

/**
  @brief Function that stops PWM generation.
*/
inline void DisablePWM()
{
  TCCR1A = 0;   // Turn of PWM
};

/**
  @brief Function that starts PWM generation.
*/
inline void EnablePWM()
{  
    #if ( LOGIG_POLARITY == ACTIVE_HIGH )
      TCCR1A |= 0b10000010; 
    #elif ( LOGIC_POLARITY == ACTIVE_LOW )
      TCCR1A |= 0b11000010;
    #endif


  // #if ( LOGIG_POLARITY == ACTIVE_LOW )
  //       // turn on PWM
  // #elif ( LOGIC_POLARITY == ACTIVE_HIGH )
  //       // turn on PWM
  // #endif
};

/**
  @brief Function sets PWM output pin high.
*/
inline void setPinHighPWM()
{
  PORTB |= (1 << 1 );    // set port to logic low
};

/**
  @brief Function sets PWM output pin low.
*/
inline void setPinLowPWM()
{
  PORTB &= ~(1 << 1);    // set port to logic low
};

/**
  @brief Function sets PWM output to high impedance state.
*/
// inline void EnablePWM_HiZ()
// {
//   DDRB &= ~( 1 << DDB1 );
// }

// /**
//   @brief Function sets PWM output to low impedance state.
// */
// inline void DisablePWM_HiZ()
// {
//   DDRB |= (1 << DDB1);
// };

/**
  @brief Function that configures Timer 2 to generate interrupt ISR( TIMER2_COMPA_vect ) each 2 ms.
  Interrupt is used for calling updatePID() and to increment global variable ENC_WatchDog.
*/
void PeriodicInterruptConfig()
{
  TCCR2A = 0;
  TCCR2B = 0;
  OCR2A = 249;            /*magic number, use define with frequency and another that will calculate this value */
  TCNT2 = 0;
};

inline void PeriodicInterruptEnable()
{
  TCCR2A |= 0b00000010;   // Enable Clear Timer on Compare Match
  TCCR2B |= 0b00000101;   // Enable CTC and set prescaler to 128
  TIMSK2 |= 0b00000010;   // Enable interupt from compare match –> timer reset
}

inline void PeriodicInterruptDisable()
{
  TCCR2A = 0;
  TCCR2B = 0;
  TIMSK2 = 0;
}

/**
  @brief Function that configures Timer 0 and D4 GPIO pin as pin change interrupt.
  Timer 0 is free running and is reseted only by readPulseCount(). Function readPulseCount()
  is called in ISR( PCINT2_vect ), which reacts to pin change event.
  
  Free running 8-bit timer config. We are not using counter overflow interrupt - is binded 
  to Arduino library and has issues compiling. Same functionality is achieved by output compare,
  where compare value is equal the TOP.
*/
void PulseCaptureConfig()
{
  /*
    Register reset.
  */
  TCCR0A = 0;
  TCCR0B = 0;
  OCR0A = 255;                  // Setting the top to timer max.

  /*
    Clear timer on compare match(CTC). Top is defined by OCRA register.
    No prescaling(prescaling by 1).
  */
  TCCR0A |= 0b00000010;
  TCCR0B |= 0b00000001;
  
  /*
    Pinchange interrupt on D4 (PORTD 4) PCINT20.
  */
  PCICR = 0;
  PCMSK2 = 0;
  PCICR |= ( 1 << PCIE2 );    // Pin Change Interrupt Enable 2.
  PCMSK2 |= ( 1 << PCINT20 ); // Enable pin change interrupt on PCINT20.
};

inline void PulseCaptureEnable()
{
  TIMSK0 |= ( 1 << (OCIE0A) );  // Enabling output compare interrupt.
  TCNT0 = 0;
}

inline void PulseCaptureDisable()
{
  TIMSK0 &= ~( 1 << (OCIE0A) );  // Enabling output compare interrupt.
}

/**
  @brief Function reads timer count between ISR( PCINT2_vect ) pin change interrupts.
  @return "Virtual" timer count.
  Function used global variable g_TIM0_ov and current timer count to calculate 
  extended count not limited by 8 bit Timer 0 resolution.
*/
inline uint32_t readPulseCount()
{
  uint32_t pulses = OCR0A * g_TIM0_ov;
  pulses += TCNT0;
  TCNT0 = 0;
  g_TIM0_ov = 0;    
  return pulses;
};

/**
  Function gets current state of encoder pin.
  Used in ISR( PCINT2_vect ).
  @return Non zero value if encoder pin is logic high.
*/
inline uint8_t encoderPinHigh()
{
  // return PORTD & ( 1 << PORTD4 );
  return digitalRead( 4 );
};

