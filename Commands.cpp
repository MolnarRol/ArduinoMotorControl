#include "Commands.h"

void PWM_duty_Callback( String msg )
{
  if( msg.length() > 0 ) 
  {
    SetPwmDuty( parseFloat( msg ) );
  }
  else 
  {
    Serial.print("PWM duty: ");
    Serial.println(GetPwmDuty());
  }
};

void PWM_on_Callback( String msg )
{
  EnablePWM();
};

void PWM_off_Callback( String msg )
{
  if( msg.length() == 0 ) DisablePWM();
};

// void helper( String msg )
// {
//   Serial.println("All possible commands:");
//   uint8_t id = 0;  

//   while( CommandList[id].cmd != "__End__"  )
//   {
//     Serial.println("\t- " + CommandList[id].cmd + ":\t\t" + CommandList[id].help );
//     id++;
//   }  
// };



