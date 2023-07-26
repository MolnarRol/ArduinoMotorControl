#ifndef _COMMAND_CALLBACKS_H_
#define _COMMAND_CALLBACKS_H_

#include "main.h"

/**
  \defgroup callbacks Callback functions
  \ingroup command_def
  @{
*/

/**
  \defgroup control_callbacks Control <ct> callbacks
  Control callback functions
  @{
*/
enum MODE {
  MANUAL,
  REGULATION
};

extern enum MODE sellected_mode;

void MODE_Callback          ( const String msg );
void MOTOR_off_Callback     ( const String msg );
void MOTOR_on_Callback      ( const String msg );
void PWM_duty_Callback      ( const String msg );
void RPM_Callback           ( const String msg );
void SPEED_Callback         ( const String msg );
void SPEED_inc_Callback     ( const String msg );
void SPEED_dec_Callback     ( const String msg );
/// @}

/**
  \defgroup direction_callbacks Direction <dir> callbacks
  Direction callback functions
  @{
*/
void DIR_1_Callback         ( const String msg );
void DIR_2_Callback         ( const String msg );
void DIR_change_Callback    ( const String msg );
/// @}

/**
  \defgroup brake_callbacks Brake <brake> callbacks
  Brake callback functions
  @{
*/
void BRAKE_on_Callback      ( const String msg );
void BRAKE_off_Callback     ( const String msg );
/// @}
void StatusCallback         ( const String msg );
/// @}
#endif