#include "TimerConfig.h"

ISR( TIMER2_COMPA_vect )
{

}

void setup() {
  PulseCaptureConfig();       // Rotary encoder capture
  PwmConfig();                // Output PWM signal
  PeriodicInterruptConfig();  // Generation periodic interrupt each 2 ms

  Serial.begin(115200);
}

void loop() {
}
