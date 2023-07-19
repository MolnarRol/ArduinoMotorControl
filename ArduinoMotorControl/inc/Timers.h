#ifndef _TIMERS_H_
#define _TIMERS_H_

#include "Arduino.h"
#include "../config.h"

#ifdef __cplusplus
extern "C" {
#endif

static float GetStepPWM( const uint16_t TOP );


void PeriodicInterruptEnable( void );
void PeriodicInterruptDisable( void );

void PulseCaptureEnable( void );
void PulseCaptureDisable( void );

/*
  Config functions
*/
void PulseCaptureConfig( void );
void PeriodicInterruptConfig( void );
void PwmConfig( void );

/*
  PWM duty setter/getter
*/
void SetPwmDuty( float dutyPerc );
float GetPwmDuty( void );

/*
  PWM on/off
*/
// void DisablePWM( void );
// void EnablePWM( void );
// void setPinHighPWM( void );
// void setPinLowPWM( void );

void DisablePWM();
void EnablePWM();
void setPinHighPWM();
void setPinLowPWM();

/*
  High impedance on/off
*/
// void DisablePWM_HiZ();
// void EnablePWM_HiZ();

/*
  Misc functions
*/

uint32_t readPulseCount();
uint8_t encoderPinHigh();

#ifdef __cplusplus
}
#endif
#endif