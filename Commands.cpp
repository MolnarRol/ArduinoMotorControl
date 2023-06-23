#include "Commands.h"



/*
  Commands for regulation
*/
CommandTypeDef REG_commands[] = 
{
  { "rpm", &RPM_Callback, "Read/Write rpm. rpm <new>" },
  { "on", &REG_on_Callback, "Regulation off." },
  { "off", &REG_off_Callback, "Regulation on" },
  { "__End__", NULL }
};

CommandGroupTypeDef REG =
{
  "reg",
  "Commands for regulation",
  REG_commands
};

/*
  Commands for PWM settings
*/
CommandTypeDef PWM_commands[] = 
{
  { "duty", &PWM_duty_Callback, "" },
  { "on", &PWM_on_Callback, "" }, //Turn on pwm modulation. Usage: on <duty> – if no duty is specified, then the last saved will be used.
  { "off", &PWM_off_Callback, "Turn off pwm modulation. Sets PWM to 0 duty." },
  { "__End__", NULL }
};

CommandGroupTypeDef PWM = 
{
  "pwm",
  "Commands used for PWM manipulation",
  PWM_commands
};

/*
  Commands for brake on/off
*/
CommandTypeDef BRAKE_commands[] = 
{
  { "on", &BRAKE_on_Callback, "" },
  { "off", &BRAKE_off_Callback, "" },
  { "__End__", NULL }
};

CommandGroupTypeDef BRAKE = 
{
  "brake",
  "Brake control",
  BRAKE_commands
};

/*
  Commands for changing direction
*/
CommandTypeDef DIR_commands[] = 
{
  { "cw", &DIR_1_Callback, "" },
  { "ccw", &DIR_2_Callback, "" },
  { "chDir", &DIR_change_Callback, "" },
  { "__End__", NULL }
};

CommandGroupTypeDef DIR = 
{
  "dir",
  "Direction control",
  DIR_commands
};

/*
  Main array of command groups
*/
CommandGroupTypeDef* CommandGroupArr[] = 
{
  &REG,
  &PWM,
  &DIR, 
  &BRAKE,
  NULL
};

/*
  Misc commands
*/
CommandTypeDef MiscCommands[] =
{
  { "clear", &clearTerminal, "Clear output terminal" },
  { "back", &resetGroup, "" },
  // { "help", &helper, "" },
  { "__End__", NULL }
};