#include "../inc/APP_Interrupts.h"

extern uint16_t g_TIM0_ov;
extern PID_TypeDef PID_controller;
extern pulseBuffersTypeDef PulseBuffers;
extern MODE sellected_mode;

/// Current motor rpm readout
float g_RPM = 0.0f;
uint8_t g_enc_first_edge = 1;

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
  sei();                                    // Reenable interrupts to allow interrupt nesting   
  PulseBuffers.idx ^= 1;                    // Switch pulse buffer
  g_RPM = getRPMfromPulses();               // Read current RPM

  if( sellected_mode == manual ) return;

  /* If watchdog was not reset in time -> halts MCU */
  #if ( ENC_WDG_EN == 1 )
    if( ( ENC_WatchDog += REG_PERIOD_MS ) > ENC_WDG_MS ) halt();
  #endif

  if( PID_controller.enable ) 
  {
    SetPwmDuty( updatePID( &PID_controller, g_RPM ) ); // PID speed regulation
  } 
  else 
  {
    /* Boost functionality -> Starts regulation after reaching defined RPM. */
    #if ( START_BOOST_EN == 1 )
      if(  PID_controller.motor_start )
      {
        if( g_RPM > MOTOR_RPM_REG_START ) startRegulation( &PID_controller );
        else SetPwmDuty( 100.0f ); 
      }
    #else
      PID_controller.enable = 1;
    #endif
  }
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
  #if ( ENC_WDG_EN == 1 )
    ENC_WatchDog = 0;
  #endif
  /* 
    Measuring delta time between pin state change 
  */
  #if ( PULSE_DELTA_READ == EDGE_BOTH )

    /* 
      Aproximating number of pulses. 
      Possible only when duty cycle of the signal is 50%!!! 
    */
    if( g_enc_first_edge == 0 ) writePulseBuff ( 2 * readPulseCount() ); 
    else g_enc_first_edge = 0;               
  #elif ( PULSE_DELTA_READ == EDGE_RISING )
    /* 
      Writing buffer only on rising edge -> encoder pin is high. 
    */
    if( encoderPinHigh() ) 
    {
      if( g_enc_first_edge == 0 ) writePulseBuff ( readPulseCount() );
      else 
      {
        g_enc_first_edge = 0;
        // resetPulseCount();
      }
    }
  #elif ( PULSE_DELTA == EDGE_FALLING )
    /* 
      Writing buffer only on rising edge -> encoder pin is low. 
    */
    if( !encoderPinHigh() ) 
    {
      if( g_enc_first_edge == 0 ) writePulseBuff ( readPulseCount() );
      else g_enc_first_edge = 0;
    }
  #else
    #error "Specified macro is not defined!!!"
  #endif
}

ISR( TIMER0_COMPA_vect )
{
    /* On overflow the variable is incremented -> getting more resolution out of timer ( 8 + 16 bits ) */
    ++g_TIM0_ov;
}