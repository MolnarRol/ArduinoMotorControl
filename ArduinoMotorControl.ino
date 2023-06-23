/*
  Test motor controll MCU project.

  Timer config:
    - Timer 0 (8-bit): Pulse counter of the roatary encoder - interupt on compare match
    - Timer 1 (16-bit): PWM for regulation output
    - Timer 2 (8-bit): ISR for calling regulation function every 2 ms

  Input/Output pins:
    - D4: Rotary encoder input
    - D5: Direction pin
    - D7: Brake pin
    - D9: PWM output

  Additional info:  
    Documentation: https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf

  Serial communication:
    - Set baud rate to 115200 baud
    - Carriage return
  
  For adding custom functions read README.md.
  Configuration file: config.h
*/

#include "Communication.h"
#include "CommandCallbacks.h"
#include "Regulation.h"
#include "TimerConfig.h"
#include "config.h"

extern uint16_t g_TIM0_ov;
extern PID_TypeDef PID_controller;
extern pulseBuffersTypeDef PulseBuffers;

ISR( TIMER2_COMPA_vect )
{
  sei();                                              // Reenable interrupts –> nesting interrupts
  switchPulseBuff();                                  // Switch pulse buffer
  if( PID_controller.enable ) 
  {
    SetPwmDuty( updatePID( &PID_controller, getRPMfromPulses() ) ); // PID speed regulation
  }
}

ISR( PCINT2_vect )
{
  // Reading delta time between pin state change – times 2 for reading 1 period (ISR is called both on falling and rising edge)
  writePulseBuff ( 2 * readPulseCount() );            
}

ISR( TIMER0_COMPA_vect )
{
  g_TIM0_ov++;  // On overflow the variable is incremented -> getting more resolution out of timer ( 8 + 16 bits )
}

void setup() {
  PulseCaptureConfig();       // Rotary encoder capture
  PwmConfig();                // Output PWM signal
  PeriodicInterruptConfig();  // Generation periodic interrupt each 2 ms

  Serial.begin( UART_BAUD );
  clearTerminal( "" );

  pinMode(2, OUTPUT);         // Debug pin
  pinMode(7, OUTPUT);         // Brake pin
  pinMode(5, OUTPUT);         // Direction pin
  
  #if PWM_ENABLED_ON_START == 1
    BRAKE_off_Callback("");     // Disengage brake
    DisablePWM_HiZ();           // Disable high impedance state of PWM output pin
    EnablePWM();                // Enabling PWM
  #endif

  #if REGULATION_ENABLED_ON_START == 1
    startRegulation( &PID_controller );
  #endif
}

void loop() {                     // Handling serial communication
  printHeader();            
  String msg = getStringUART();
  if( msg.length() > 0 )
  {
    Serial.println( msg );
    msgToCommand( msg );
  }
  else Serial.println(); 
}
