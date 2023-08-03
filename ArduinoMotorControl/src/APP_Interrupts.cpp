#include "stdint.h"
#include "../inc/APP_Interrupts.h"
#include "../inc/CommandCallbacks.h"
#include "../inc/Timers.h"
#include "../inc/TimingUtils.h"
#include "../inc/Regulation.h"

float g_RPM_f32 = 0.0f;   /// Current motor rpm readout
uint8_t g_enc_first_edge_u8 = 1; /// Global flag

/** Encoder signal missing watchdog global variable. */
#if ENC_WDG_EN == 1  
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
  g_RPM_f32 = getRPMfromPulses();               

  if( sellected_mode == manual ) return;

  /* If watchdog was not reset in time -> halts MCU */
  #if ( ENC_WDG_EN == 1 )
    if( ( ENC_WatchDog += REG_PERIOD_MS ) > ENC_WDG_MS ) halt();
  #endif

  SetPwmDuty( updatePID( &PID_controller, g_RPM_f32 ) );
}

/**
  @warning Usage of EDGE_BOTH detenction should be used only if the encoder signal has fixed 50% duty cycle. 
  Otherwise use EDGE_RISING or EDGE_FALLING!
*/
ISR( PCINT2_vect )
{
  uint32_t pulse_count_u32 = 0;

  #if ( ENC_WDG_EN == 1 )
    ENC_WatchDog = 0;
  #endif

  if( encoderPinHigh() ) 
  {
    if( !g_enc_first_edge_u8 ){
      pulse_count_u32 = readPulseCount();
    } 
    else 
    {
      g_enc_first_edge_u8 = 0;
      resetPulseCount();
      return;
    }
  }
  else 
  {
    return;
  }

  #if ( START_BOOST_EN == 1 )
    if( PID_controller.motor_start )
    {
      g_RPM_f32 = calcRPM( pulse_count_u32 );
      if( g_RPM_f32 >= 500 )
      {
        PeriodicInterruptEnable();
        startRegulation( &PID_controller );
        SetPwmDuty( updatePID( &PID_controller, g_RPM_f32 ) );
        PID_controller.motor_start = 0;
      }
      return;
    }
  #endif

  writePulseBuff( pulse_count_u32 );
}

ISR( TIMER0_COMPA_vect )
{
    /* On overflow the variable is incremented -> getting more resolution out of timer ( 8 + 16 bits ) */
    ++g_TIM0_ov;
}