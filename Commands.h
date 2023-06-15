
#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include "Arduino.h"
#include "Communication.h"
#include "TimerConfig.h"

void helper( String msg );

void PWM_duty_Callback( String msg );
void PWM_on_Callback( String msg );
void PWM_off_Callback( String msg );

typedef struct Command
{
  String cmd;                         // command string
  void (*p_function)( String msg );   // called void function
  String help;                        // help command string
} CommandTypeDef;

typedef struct CommandGroup
{
  String identity;                    // Group identifier for example >>[identity]>>
  String descript;                    // description in help command
  CommandTypeDef* List;               // List of used commands
} CommandGroupTypeDef;

#endif