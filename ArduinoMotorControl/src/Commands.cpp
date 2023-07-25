#include "../inc/Commands.h"

/*
  Commands for motor controll
*/
CommandTypeDef CONTROL_commands[] = 
{
  { "duty", PWM_duty_Callback },
  { "rpm", RPM_Callback },
  { "mode", &MODE_Callback },
  { "s", SPEED_Callback },
  { "+", SPEED_inc_Callback },
  { "-", SPEED_dec_Callback },
  { "stop", MOTOR_off_Callback }, //Turn on pwm modulation. Usage: on <duty> – if no duty is specified, then the last saved will be used.
  { "start", MOTOR_on_Callback },
  { "__End__", NULL }
};

CommandGroupTypeDef CONTROL = 
{
  "ct",
  CONTROL_commands
};

/*
  Commands for brake on/off
*/
CommandTypeDef BRAKE_commands[] = 
{
  { "on", BRAKE_on_Callback },
  { "off", BRAKE_off_Callback },
  { "__End__", NULL }
};

CommandGroupTypeDef BRAKE = 
{
  "brake",
  BRAKE_commands
};

/*
  Commands for changing direction
*/
CommandTypeDef DIR_commands[] = 
{
  { "cw", DIR_1_Callback },
  { "ccw", DIR_2_Callback },
  { "chDir", DIR_change_Callback },
  { "__End__", NULL }
};

CommandGroupTypeDef DIR = 
{
  "dir",
  DIR_commands
};

/*
  Main array of command groups
*/
CommandGroupTypeDef* CommandGroupArr[] = 
{
  &CONTROL,
  &DIR, 
  &BRAKE,
  NULL
};

/*
  Misc commands
*/
CommandTypeDef MiscCommands[] =
{
  { "clear", clearTerminal },
  { "back", resetGroup },
  { "status",StatusCallback },
  { "help", helper },
  { "t", test },
  { "__End__", NULL }
};