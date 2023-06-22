/*
  Test motor controll MCU project.

  Timer config:
    - Timer 0 (8-bit): Pulse counter of the roatary encoder - interupt on compare match
    - Timer 1 (16-bit): PWM for regulation output
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

float Error;

extern uint16_t g_TIM0_ov;
extern PID_TypeDef PID_controller;
extern pulseBuffersTypeDef PulseBuffers;

uint32_t DEBUG = 0;
float RPM;

ISR( TIMER2_COMPA_vect )
{
  sei();   // Reenable interrupts
  switchPulseBuff();
  RPM = getRPMfromPulses();
  SetPwmDuty( updatePID( &PID_controller, (RPM / 60.0f) ) );
}

uint8_t test = 0;
ISR( PCINT2_vect )
{
  writePulseBuff ( 2 * readPulseCount() );
}

ISR( TIMER0_COMPA_vect )
{
  g_TIM0_ov++;
}

void setup() {
  PulseCaptureConfig();       // Rotary encoder capture
  PwmConfig();                // Output PWM signal
  PeriodicInterruptConfig();  // Generation periodic interrupt each 2 ms

  Serial.begin(115200);
  clearTerminal( "" );

  pinMode(2, OUTPUT);         // Debug pin
  pinMode(7, OUTPUT);         // Brake pin
  pinMode(5, OUTPUT);         // Direction pin

  // SetPwmDuty(0);              // Set speed to 0
  // BRAKE_off_Callback("");     // Disengage brake

  // DEBUG
  // SetPwmDuty(5.0f);
  BRAKE_off_Callback("");     // Disengage brake
  DisablePWM_HiZ();
  EnablePWM();
}

void loop() {
  // printHeader();
  // String msg = getStringUART();
  // if( msg.length() > 0 )
  // {
  //   Serial.println( msg );
  //   msgToCommand( msg );
  // }
  // else Serial.println();

  Serial.print(0);
  Serial.print(" ");
  Serial.print( 10.0f * GetPwmDuty() );
  Serial.print(" ");
  Serial.println(RPM);
  
}

