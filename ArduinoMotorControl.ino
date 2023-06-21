/*
  Test motor controll MCU project.

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

#include "Communication.h"
#include "Regulation.h"
#include "TimerConfig.h"
#include "Debug.h"

uint8_t n_pulses = 0;

#define ENC_N_PULSES 100

ISR( TIMER2_COMPA_vect )
{
  // Regulation each 2 ms
  n_pulses = readPulseCount();
}

void setup() {
  PulseCaptureConfig();       // Rotary encoder capture
  PwmConfig();                // Output PWM signal
  PeriodicInterruptConfig();  // Generation periodic interrupt each 2 ms

  Serial.begin(115200);
  clearTerminal( "" );

  pinMode(2, OUTPUT);         // Debug pin
  pinMode(7, OUTPUT);         // Brake pin
  pinMode(5, OUTPUT);         // Direction pin[defective]

  SetPwmDuty(0);              // Set speed to 0
  BRAKE_off_Callback("");     // Disengage brake
}

void loop() {
  printHeader();
  String msg = getStringUART();
  if( msg.length() > 0 )
  {
    Serial.println( msg );
    msgToCommand( msg );
  }
  else Serial.println();
  
  Serial.print("Pulse count: ");
  Serial.println(n_pulses);
  Serial.print("RPM: ");
  Serial.println( calcRPM(n_pulses, 2) );
}