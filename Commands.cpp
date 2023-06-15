#include "Commands.h"

/*
  PWM Callback functions
*/

void PWM_duty_Callback( String msg )
{
  if( msg.length() > 0 ) SetPwmDuty( parseFloat( msg ) );   // Bug: on 0
  else
  {
    Serial.print("PWM duty: ");
    Serial.print( GetPwmDuty() );
    Serial.println("%");
  } 
};

void PWM_on_Callback( String msg )
{
  if( msg.length() > 0 )
  {
    SetPwmDuty( parseFloat(msg) );
  }
  if( GetPwmDuty() != 0.0f ) EnablePWM();
  DisablePWM_HiZ();
};

void PWM_off_Callback( String msg )
{
  EnablePWM_HiZ();
  DisablePWM();  
};

/*
  Brake Callback functions
*/
void BRAKE_on_Callback( String msg )
{
  digitalWrite( 8, 1 );
};

void BRAKE_off_Callback( String msg )
{
  digitalWrite( 8, 0 );
};

/*
  Direction Callback functions
*/
void DIR_1_Callback( String msg )
{
  digitalWrite( 7, 1);
};

void DIR_2_Callback( String msg )
{
  digitalWrite( 7, 0);
};

void DIR_change_Callback( String msg )
{
  static uint8_t state = ( PORTD & ~(1 << 7) ) >> 7;    // PD7
  state = !state;
  digitalWrite( 7, state );
};