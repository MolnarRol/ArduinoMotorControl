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

  Serial communication:
    - Set baud rate to 115200 baud
    - Carriage return

  Additional info:  
    For adding custom functions read README.md.
    Configuration file: config.h
    MCU Documentation: https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
*/

#include "Communication.h"
#include "CommandCallbacks.h"
#include "Regulation.h"
#include "TimerConfig.h"
#include "config.h"

extern uint16_t g_TIM0_ov;
extern PID_TypeDef PID_controller;
extern pulseBuffersTypeDef PulseBuffers;

float g_RPM = 0.0f;

#if ENC_WDG_EN == 1
  uint16_t ENC_WatchDog = 0;
#endif

ISR( TIMER2_COMPA_vect )
{
  sei();                        // Reenable interrupts –> nesting interrupts   
  switchPulseBuff();            // Switch pulse buffer
  g_RPM = getRPMfromPulses();   // Read current RPM
  if( PID_controller.enable ) 
  {

    #if ENC_WDG_EN == 1
      ENC_WatchDog += 2;
      if( ENC_WatchDog >= ENC_WDG_MS )
      {
        ENC_WatchDog = 0;
        MOTOR_off_Callback("");
      }
    #endif

    SetPwmDuty( updatePID( &PID_controller, g_RPM ) ); // PID speed regulation
  }
}

ISR( PCINT2_vect )
{
<<<<<<< Updated upstream
  // Reading delta time between pin state change – times 2 for reading 1 period (ISR is called both on falling and rising edge)
  writePulseBuff ( 2 * readPulseCount() );    
=======
  /* 
    Measuring delta time between pin state change 
  */
  #if ( PULSE_DELTA_READ == EDGE_BOTH )
    /* 
      Aproximating number of pulses. 
      Possible only when duty cycle of the signal is 50%!!! 
    */
    writePulseBuff ( 2 * readPulseCount() );                
  #elif ( PULSE_DELTA_READ == EDGE_RISING )
    /* 
      Writing buffer only on rising edge -> encoder pin is high. 
    */
    if( digitalRead( 4 ) ) 
    {
      writePulseBuff ( readPulseCount() );
    }
  #elif ( PULSE_DELTA == EDGE_FALLING )
    /* 
      Writing buffer only on rising edge -> encoder pin is low. 
    */
    if( !encoderPinHigh() ) writePulseBuff ( readPulseCount() );
  #else
    #error "[PULSE_DELTA_READ] <?> Specified macro is not defined!!!"
  #endif
>>>>>>> Stashed changes

  #if ENC_WDG_EN == 1
    if( PID_controller.enable ) ENC_WatchDog = 0;
  #endif
}

ISR( TIMER0_COMPA_vect )
{
  g_TIM0_ov++;  // On overflow the variable is incremented -> getting more resolution out of timer ( 8 + 16 bits )
}

void setup() {
  /*
    Timer setup functions
  */
  PulseCaptureConfig();       // Rotary encoder capture
  PwmConfig();                // Output PWM signal
  PeriodicInterruptConfig();  // Generation periodic interrupt each 2 ms

  /*
    UART setup
  */
  Serial.begin( UART_BAUD );
  clearTerminal( "" );

  /*
    Digital pin setup
  */
  pinMode(2, OUTPUT);         // Debug pin
  pinMode(7, OUTPUT);         // Brake pin
  pinMode(5, OUTPUT);         // Direction pin
  digitalWrite( 7, 1 );       // Disengage brake

<<<<<<< Updated upstream
  #if REG_MOTOR_AUTOSTART == 1
    DisablePWM_HiZ();           // Disable high impedance state of PWM output pin
=======
  pinMode(9, OUTPUT );
  EnablePWM();
  SetPwmDuty(0);

  #if ( REG_MOTOR_AUTOSTART == 1 )
    // DisablePWM_HiZ();           // Disable high impedance state of PWM output pin
>>>>>>> Stashed changes
    EnablePWM();                // Enabling PWM
    extern MODE sellected_mode;
    sellected_mode = regulation;
    MOTOR_on_Callback("");
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