#include "Commands.h"

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

void PWM_on_Callback( String msg )
{
  if( msg.length() > 0 ) SetPwmDuty( parseFloat(msg) );
  DisablePWM_HiZ();
  EnablePWM();
};

void PWM_off_Callback( String msg )
{
  EnablePWM_HiZ();
  DisablePWM();  
};