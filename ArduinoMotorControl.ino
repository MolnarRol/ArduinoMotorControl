#include "TimerConfig.h"

ISR( TIMER2_COMPA_vect )
{

}

void setup() {
  pinMode( 12, OUTPUT );
  PulseCaptureConfig();
  PwmConfig();
  PeriodicInterruptConfig();
  Serial.begin(115200);
}

void loop() {
}
