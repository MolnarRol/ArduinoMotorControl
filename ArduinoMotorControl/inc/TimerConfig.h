#ifndef _TIMER_CONFIG_H_
#define _TIMER_CONFIG_H_

#include "Arduino.h"
#include "../config.h"

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
void setPinHighPWM();
void setPinLowPWM();

/*
  High impedance on/off
*/
void DisablePWM_HiZ();
void EnablePWM_HiZ();

/*
  Misc functions
*/
float GetStepPWM( const uint16_t TOP );
uint32_t readPulseCount();
<<<<<<< HEAD:ArduinoMotorControl/inc/TimerConfig.h
=======
uint8_t encoderPinHigh();
>>>>>>> parent of f48da27... Boost start - bugfix:ArduinoMotorControl/inc/Timers.h

uint8_t encoderPinHigh();
#ifdef __cplusplus
}
#endif
#endif