#include "CommandCallbacks.h"

/*
  User predefined speeds
*/
float speeds[] = SPEEDS;
const uint8_t speeds_len = sizeof(speeds) / sizeof(float);
uint8_t speed_idx = 0;

enum MODE sellected_mode = regulation;

void StatusCallback( String msg )
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

void MODE_Callback( String msg )
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

void MOTOR_off_Callback( String msg )
{
  if( sellected_mode == regulation )
  {
    stopRegulation( &PID_controller );
    PID_controller.enable = 0;
    PID_controller.motor_start = 1;
    SetPwmDuty(0.0f);
  }  
  DisablePWM();
  EnablePWM_HiZ();
};

void MOTOR_on_Callback( String msg )
{
  EnablePWM();
  DisablePWM_HiZ();
  if( sellected_mode == regulation )
  {
    PID_controller.motor_start = 1;
    PID_controller.enable = 1;
    startRegulation( &PID_controller );
  }  
};

void SPEED_Callback( String msg )
{
  speed_idx = (uint16_t)parseFloat( msg ) - 1;
  if( speed_idx >= speeds_len ) speed_idx = speeds_len - 1;
  changeSetPoint( &PID_controller, speeds[speed_idx] );
};

void SPEED_inc_Callback( String msg )
{
  speed_idx++;
  if( speed_idx == speeds_len ) speed_idx = speeds_len - 1;
  changeSetPoint( &PID_controller, speeds[speed_idx] );
};

void SPEED_dec_Callback( String msg )
{
  speed_idx--;
  if( speed_idx == 255 ) speed_idx = 0;
  changeSetPoint( &PID_controller, speeds[speed_idx] );
};

/*
  Regulation Callback functions
*/
void RPM_Callback( String msg )
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
  if( msg.length() > 0 ) SetPwmDuty( parseFloat( msg ) ); 
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
void BRAKE_on_Callback( String msg )
{
  digitalWrite( 7, 0 );
  MOTOR_off_Callback("");
};

void BRAKE_off_Callback( String msg )
{
  digitalWrite( 7, 1 );
};

/*
  Direction Callback functions
*/
void DIR_1_Callback( String msg )
{
  digitalWrite( 5, 1);
};

void DIR_2_Callback( String msg )
{
  digitalWrite( 5, 0);
};

void DIR_change_Callback( String msg )
{
  static uint8_t state = ( PORTD & ~(1 << 5) ) >> 5;    // P5
  state = !state;
  digitalWrite( 5, state );
};