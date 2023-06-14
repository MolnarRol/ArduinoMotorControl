#include "TimerConfig.h"

void SetPwmDuty( float dutyPerc )
{
  if( dutyPerc > 100.0f || dutyPerc < 0.0f ) return;
  /* 
  The timer resolution can be adjusted in descrete steps by 0.125% 
  if we provide lower value than 0.125 than we turn of the PWM and set port to output logic LOW 


  TODO>
    - fix rozsah
    - upravit tak aby mohlo menit frekvenciu
  */
  if( dutyPerc < 0.125f )   
  {
    TCCR1A &= ~(1 << 7 );   // Turn of PWM
    PORTB &= ~(1 << 1 );    // set port to logic low
    return;
  }
  else
  {
    TCCR1A |= (1 << 7 );    // turn on PWM
  }  
  OCR1A = (uint16_t)( 8.0f * dutyPerc ) - 1;
};

float GetPwmDuty(){
  return ( (float)OCR1A + 1.0f ) / 8.0f; 
};

void PulseCaptureConfig()
{
  DDRB |= 0 << DDB4;  // Enable clock on T0 pin (D4)
  TCCR0A = 0;
  TCCR0B = 0;
  TCCR0B |= 0b111;    // Enable external clock source on T0 pin. Clock on rising edge
  TCNT0 = 0;
};

void PwmConfig()
{
  DDRB |= 1 << DDB1; // Set GPIO pin as output (D9)
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1A |= 0b10000010; // Enable fast PWM on channel A
  TCCR1B |= 0b00011001; // Enable fast PWM with no prescaling
  ICR1 = 800;
  OCR1A = 100;
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

