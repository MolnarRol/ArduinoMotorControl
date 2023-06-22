
#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include "Arduino.h"
#include "Communication.h"
#include "TimerConfig.h"
#include "Regulation.h"

extern PID_TypeDef PID_controller;
void RPM_Callback( String msg );
void REG_on_Callback( String msg );
void REG_off_Callback( String msg );

/*
  Direction Callback functions
*/
void DIR_1_Callback( String msg );
void DIR_2_Callback( String msg );
void DIR_change_Callback( String msg );

/*
  Brake Callback function
*/
void BRAKE_on_Callback( String msg );
void BRAKE_off_Callback( String msg );

/*
  PWM Callback functions
*/
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