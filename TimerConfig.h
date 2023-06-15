#ifndef _TIMER_CONFIG_H_
#define _TIMER_CONFIG_H

#include <stdint.h>
#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
  Config functions
*/
void PulseCaptureConfig();
void PeriodicInterruptConfig();
void PwmConfig();

/*
  PWM duty setter/getter
*/
void SetPwmDuty( float dutyPerc );
float GetPwmDuty();

/*
  PWM on/off
*/
void DisablePWM();
void EnablePWM();

/*
  Misc functions
*/
float GetStepPWM( const uint16_t TOP );



#ifdef __cplusplus
}
#endif
#endif