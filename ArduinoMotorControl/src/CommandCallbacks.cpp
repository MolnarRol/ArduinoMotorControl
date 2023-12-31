#include "../config.h"
#include "../inc/APP_Interrupts.h"
#include "../inc/Communication.h"
#include "../inc/CommandCallbacks.h"
#include "../inc/Timers.h"
#include "../inc/TimingUtils.h"
#include "../inc/Regulation.h"

/*
  User predefined speeds
  --------------------------------------------------------------------------------
*/
const float speeds[] = SPEEDS;
const uint8_t speeds_len = sizeof(speeds) / sizeof(float);
uint8_t speed_idx = 0;
/* ------------------------------------------------------------------------------- */

enum MODE sellected_mode = regulation;
uint8_t g_flag_motor_running = 0;

void StatusCallback( const String msg )
{
  Serial.print("Sellected mode: ");
  if( sellected_mode == regulation ) Serial.println( "Regulation" );
  else Serial.println( "Manual PWM" );
  
  Serial.print("Current RPM: ");
  Serial.println(g_RPM);
  PWM_duty_Callback("");
};

#if ENC_WDG_EN == 1
  extern uint16_t ENC_WatchDog;
#endif

/**
  TEST
*/
void MODE_Callback( const String msg )
{
  if( msg ==  "man")
  {
    sellected_mode = manual;
    stopRegulation( &PID_controller );
  }
  else if( msg == "reg" )
  {
    sellected_mode = regulation;
    
    if( !g_flag_motor_running )
    {
      PID_controller.motor_start = 1;
    }
    else
    {
      startRegulation( &PID_controller );
    }
  }
  else if( msg.length() == 0 )
  {
    Serial.print("Mode: ");
    if( sellected_mode == regulation )
    {
      Serial.println("regulation");
    }
    else
    {
      Serial.println("manual");
    }
  }
};

void MOTOR_off_Callback( const String msg )
{
  if( !g_flag_motor_running ) return;
  if( sellected_mode == regulation ) stopRegulation( &PID_controller );  
  PulseCaptureDisable();
  PeriodicInterruptDisable();
  SetPwmDuty(0.0f);
  PID_controller.integrator = 0.0f;
  g_RPM = 0.0f;
  g_enc_first_edge = 1;
  PID_controller.motor_start = 1;
  g_flag_motor_running = 0;
};

void MOTOR_on_Callback( const String msg )
{
  if( g_flag_motor_running ) return;
  g_flag_motor_running = 1;
  clearPulseBuffers();
  SetPwmDuty( g_saved_duty );
  PeriodicInterruptEnable();
  PulseCaptureEnable();
};

void SPEED_Callback( const String msg )
{
  speed_idx = (uint16_t)parseFloat( msg ) - 1;
  if( speed_idx >= speeds_len ) speed_idx = speeds_len - 1;
  changeSetPoint( &PID_controller, speeds[speed_idx] );
};

void SPEED_inc_Callback( const String msg )
{
  speed_idx++;
  if( speed_idx == speeds_len ) speed_idx = speeds_len - 1;
  changeSetPoint( &PID_controller, speeds[speed_idx] );
};

void SPEED_dec_Callback( const String msg )
{
  speed_idx--;
  if( speed_idx == 255 ) speed_idx = 0;
  changeSetPoint( &PID_controller, speeds[speed_idx] );
};

/*
  Regulation Callback functions
*/
void RPM_Callback( const String msg )
{
  if( msg.length() > 0 ) 
  {
    changeSetPoint( &PID_controller, parseFloat( msg ) );
  }
  else
  {
    Serial.println( PID_controller.setPoint );
  }
};

/*
  PWM Callback functions
*/
void PWM_duty_Callback( String msg )
{
  if( msg.length() > 0 ) 
  {
    float duty = parseFloat( msg );
    if( g_flag_motor_running ) SetPwmDuty( duty ); 
    g_saved_duty = duty;
  }
  else
  {
    if( g_flag_motor_running )
    {
      Serial.print( F("PWM duty: ") );
      Serial.print( GetPwmDuty() );
      Serial.println( F("%") );
    }
    else
    {
      Serial.print( F("Set PWM duty(motor not running): ") );
      Serial.print( g_saved_duty );
      Serial.println( F("%") );
    }
  } 
};

/*
  Brake Callback functions
*/
void BRAKE_on_Callback( const String msg )
{
  #if ( LOGIG_POLARITY == ACTIVE_HIGH )
    digitalWrite( BRK_PIN, 1 );
  #elif ( LOGIC_POLARITY == ACTIVE_LOW )  
    digitalWrite( BRK_PIN, 0 );
  #endif
  
  MOTOR_off_Callback("");
};

void BRAKE_off_Callback( const String msg )
{
  #if ( LOGIG_POLARITY == ACTIVE_HIGH )
    digitalWrite( BRK_PIN, 0 );
  #elif ( LOGIC_POLARITY == ACTIVE_LOW )  
    digitalWrite( BRK_PIN, 1 );
  #endif
};

/*
  Direction Callback functions
*/
void DIR_1_Callback( const String msg )
{
  digitalWrite( DIR_PIN, 1);
};

void DIR_2_Callback( const String msg )
{
  digitalWrite( DIR_PIN, 0);
};

void DIR_change_Callback( const String msg )
{
  // static uint8_t state = ( PORTD & ~(1 << DIR_PIN) ) >> DIR_PIN;    // P5
  static uint8_t state = digitalRead( DIR_PIN );
  state = !state;
  digitalWrite( DIR_PIN, state );
};