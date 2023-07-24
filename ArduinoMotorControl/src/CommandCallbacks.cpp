#include "../inc/CommandCallbacks.h"

/*
  User predefined speeds
  --------------------------------------------------------------------------------
*/
const float speeds[] = SPEEDS;
const uint8_t speeds_len = sizeof(speeds) / sizeof(float);
uint8_t speed_idx = 0;
/* ------------------------------------------------------------------------------- */

enum MODE sellected_mode = regulation;
// extern pulseBuffersTypeDef PulseBuffers;
extern float g_l_val;
extern uint8_t g_enc_first_edge;
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
    startRegulation( &PID_controller );
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
  if( sellected_mode == regulation ) stopRegulation( &PID_controller );  
  SetPwmDuty(0.0f);
  // EnablePWM_HiZ();
  PulseCaptureDisable();
  PeriodicInterruptDisable();
};

void MOTOR_on_Callback( const String msg )
{
  g_RPM = 0.0f;
  // g_l_val = 0.0f;
  g_enc_first_edge = 1;
  PID_controller.motor_start = 1;
  // resetPulseCount();
  clearPulseBuffers();

  #if ( START_BOOST_EN == 1 )
    if( sellected_mode == regulation ) 
    {
      PID_controller.motor_start = 1;

    }
  // #else
  //   SetPwmDuty( 0.0f );
  #endif
  
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
    SetPwmDuty( parseFloat( msg ) ); 
  }
  else
  {
    Serial.print("PWM duty: ");
    Serial.print( GetPwmDuty() );
    Serial.println("%");
  } 
};

/*
  Brake Callback functions
*/
void BRAKE_on_Callback( const String msg )
{
  digitalWrite( BRK_PIN, 0 );
  MOTOR_off_Callback("");
};

void BRAKE_off_Callback( const String msg )
{
  digitalWrite( BRK_PIN, 1 );
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
  static uint8_t state = ( PORTD & ~(1 << DIR_PIN) ) >> DIR_PIN;    // P5
  state = !state;
  digitalWrite( DIR_PIN, state );
};