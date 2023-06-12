#include "TimerConfig.h"

void PulseCaptureConfig()
{
  DDRB |= 0 << DDB4;  // Enable clock on T0 pin (D4)
  TCCR0A = 0;
  TCCR0B = 0;
  TCCR0B |= 0b111;    // Enable external clock source on T0 pin. Clock on rising edge
  TCNT0 = 0;
};
void PeriodicInterruptConfig()
{

};
void PwmConfig()
{
  DDRB |= << DDRB1; // Set GPIO pin as output

};