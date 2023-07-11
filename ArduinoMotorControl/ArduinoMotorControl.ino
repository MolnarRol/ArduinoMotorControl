#include "config.h"
#include "inc/Commands.h"
#include "inc/CommandCallbacks.h"
#include "inc/Communication.h"
#include "inc/Regulation.h"
#include "inc/TimerConfig.h"
#include "inc/TimingUtils.h"

extern uint16_t g_TIM0_ov;
extern PID_TypeDef PID_controller;
extern pulseBuffersTypeDef PulseBuffers;

/// Current motor rpm readout
float g_RPM = 0.0f;

#if ENC_WDG_EN == 1
  /// Encoder signal missing watchdog global variable.
  uint16_t ENC_WatchDog = 0;
#endif

/**
  Interrupt service routine called each 2 ms.
  Used for reading current rpm and PID new value calculation.
*/
ISR( TIMER2_COMPA_vect )
{
  sei();                                // Reenable interrupts to allow interrupt nesting   
  switchPulseBuff();                    // Switch pulse buffer
  g_RPM = getRPMfromPulses();           // Read current RPM
  if( PID_controller.enable ) 
  {
    //* Increment ENC_WatchDog */
    #if ( ENC_WDG_EN == 1 )
      ENC_WatchDog += REG_PERIOD_MS;
      if( ENC_WatchDog >= ENC_WDG_MS )
      {
        ENC_WatchDog = 0;
        MOTOR_off_Callback("");
      }
    #endif

    SetPwmDuty( updatePID( &PID_controller, g_RPM ) ); // PID speed regulation
  }
}
/**
  @warning Usage of EDGE_BOTH detenction should be used only if the encoder signal has fixed 50% duty cycle. 
  Otherwise use EDGE_RISING or EDGE_FALLING!
*/
ISR( PCINT2_vect )
{
<<<<<<< HEAD
  // Reading delta time between pin state change – times 2 for reading 1 period (ISR is called both on falling and rising edge)
  #if ( PULSE_DELTA_READ == EDGE_BOTH )
    writePulseBuff ( 2 * readPulseCount() );    
  #elif ( PULSE_DELTA_READ == EDGE_RISING )
    
  #elif ( PULSE_DELTA == EDGE_FALLING )

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
    if( encoderPinHigh() ) writePulseBuff ( readPulseCount() );
  #elif ( PULSE_DELTA == EDGE_FALLING )
    /* 
      Writing buffer only on rising edge -> encoder pin is low. 
    */
    if( !encoderPinHigh() ) writePulseBuff ( readPulseCount() );
  #else
    #error "[PULSE_DELTA_READ] <?> Specified macro is not defined!!!"
>>>>>>> d4517cc (Added initial doxygen documentation)
  #endif

  /*
    If encoder watchdog is enabled -> reset watchdog counter on new pulse.
  */
  #if ( ENC_WDG_EN == 1 )
    if( PID_controller.enable ) ENC_WatchDog = 0;
  #endif
}

ISR( TIMER0_COMPA_vect )
{
  g_TIM0_ov++;  // On overflow the variable is incremented -> getting more resolution out of timer ( 8 + 16 bits )
}

/// Arduino setup function
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
  pinMode(DEBUG_PIN, OUTPUT);       // Debug pin
  pinMode(BRK_PIN, OUTPUT);         // Brake pin
  pinMode(DIR_PIN, OUTPUT);         // Direction pin
  digitalWrite( BRK_PIN, 1 );       // Disengage brake

  #if ( REG_MOTOR_AUTOSTART == 1 )
    DisablePWM_HiZ();           // Disable high impedance state of PWM output pin
    EnablePWM();                // Enabling PWM
    extern MODE sellected_mode;
    sellected_mode = regulation;
    MOTOR_on_Callback("");
  #endif
}

/// Main code loop
/// This loop handles all UART communication
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