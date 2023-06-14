/*
  Test motor controll mcu project.

  TODO:
    - Implement PID regulation
    - other misc pins

  Timer config:
    - Timer 0 (8-bit): Pulse counter of the roatary encoder - interupt on compare match
    - Timer 1 (16-BIT): PWM for regulation output
    - Timer 2 (8-bit): ISR for calling regulation function every 2 ms

  Input/Output pins:
    - D4: Rotary encoder input
    - D9: PWM output

  Additional info:  
    Documentation: https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
*/

#include <stdio.h>
#include "Communication.h"
#include "TimerConfig.h"
#include "Debug.h"

ISR( TIMER2_COMPA_vect )
{
  // Regulation each 2 ms
}

void setup() {
  PulseCaptureConfig();       // Rotary encoder capture
  PwmConfig();                // Output PWM signal
  PeriodicInterruptConfig();  // Generation periodic interrupt each 2 ms
  Serial.begin(115200);
  clearTerminal( "" );
  SetPwmDuty( 0.0f );
  pinMode(2, OUTPUT);
}

void loop() {
  Serial.print(">> ");
  while( Serial.available() == 0 ){};                     // Wait for input
  String msg = Serial.readStringUntil( '\n' );
  Serial.println(msg);
  if( msg.length() > 0 ) msgToCommand( msg );
  else Serial.println();
}

