#include "../inc/APP_Interrupts.h"

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

  #if ( ENC_WDG_EN == 1 ) 
    if( ( ENC_WatchDog += REG_PERIOD_MS ) > ENC_WDG_MS ) halt();
  #endif
  
  #if ( START_BOOST_EN == 1 )
    if( PID_controller.motor_start )
    {
      if( g_RPM > MOTOR_RPM_REG_START ) 
      {
        PID_controller.motor_start = 0;
        startRegulation( &PID_controller );
      }
      else SetPwmDuty( 100.0f );
    }
  #endif

  if( PID_controller.enable ) SetPwmDuty( updatePID( &PID_controller, g_RPM ) ); // PID speed regulation
}

/**
  @warning Usage of EDGE_BOTH detenction should be used only if the encoder signal has fixed 50% duty cycle. 
  Otherwise use EDGE_RISING or EDGE_FALLING!
*/
ISR( PCINT2_vect )
{
  /*
    If encoder watchdog is enabled -> reset watchdog counter on new pulse.
  */
  // #if ( ENC_WDG_EN == 1 )
  //   ENC_WatchDog = 0;
  // #endif

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
    #error "Specified macro is not defined!!!"
  #endif
}

ISR( TIMER0_COMPA_vect )
{
    /* On overflow the variable is incremented -> getting more resolution out of timer ( 8 + 16 bits ) */
    ++g_TIM0_ov;
}