#include "Commands.h"

/*
  Commands for motor controll
*/
CommandTypeDef CONTROL_commands[] = 
{
  { "duty", &PWM_duty_Callback, "" },
  { "rpm", &RPM_Callback, "Read/Write rpm. rpm <new>" },
  { "mode", &MODE_Callback },
  { "s", &SPEED_Callback },
  { "+", &SPEED_inc_Callback },
  { "-", &SPEED_dec_Callback },
  { "stop", &MOTOR_off_Callback, "" }, //Turn on pwm modulation. Usage: on <duty> – if no duty is specified, then the last saved will be used.
  { "start", &MOTOR_on_Callback, "Turn off pwm modulation. Sets PWM to 0 duty." },
  { "__End__", NULL }
};

CommandGroupTypeDef CONTROL = 
{
  "ct",
  "Commands used for motor control",
  CONTROL_commands
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
  { "clear", &clearTerminal, "Clear output terminal" },
  { "back", &resetGroup, "" },
  { "status", &StatusCallback, "" },
<<<<<<< Updated upstream:ArduinoMotorControl/Commands.cpp
  // { "help", &helper, "" },
=======
  { "help", &helper, "" },
  { "t", &test, "" },
>>>>>>> Stashed changes:ArduinoMotorControl/src/Commands.cpp
  { "__End__", NULL }
};