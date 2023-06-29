#ifndef _COMMAND_CALLBACKS_H_
#define COMMAND_CALLBACKS_H_

#include <string.h>
#include "Communication.h"
#include "Commands.h"
#include "TimerConfig.h"
#include "Regulation.h"

extern PID_TypeDef PID_controller;

void MODE_Callback( String msg );
void MOTOR_off_Callback( String msg );
void MOTOR_on_Callback( String msg );
void PWM_duty_Callback( String msg );
void RPM_Callback( String msg );
void SPEED_Callback( String msg );
void SPEED_inc_Callback( String msg );
void SPEED_dec_Callback( String msg );

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
#endif