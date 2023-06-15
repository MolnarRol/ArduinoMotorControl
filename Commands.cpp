#include "Commands.h"

void clearTerminal( String msg )
{
  for( uint8_t i; i < 50; i++ ) Serial.println();
};

void PWM_duty_Callback( String msg )
{
  if( msg.length() > 0 ) 
  {
    float a = parseFloat( msg );
    setPin();
    SetPwmDuty( a );
    clearPin();
  }
  else 
  {
    Serial.print("PWM duty: ");
    Serial.println(GetPwmDuty());
  }
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

CommandTypeDef PWM_commands[] = 
{
  { "duty", &PWM_duty_Callback, "Clear output terminal" },
  { "__End__", NULL }
};

CommandGroupTypeDef PWM = 
{
  "PWM",
  "Commands used for PWM manipulation",
  PWM_commands
};

CommandGroupTypeDef* CommandGroupArr[] = 
{
  &PWM,
  NULL
};