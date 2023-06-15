#ifndef _TIMER_CONFIG_H_
#define _TIMER_CONFIG_H

#include <stdint.h>
#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif
void SetPwmDuty( float dutyPerc );
float GetPwmDuty();

void PulseCaptureConfig();
void PeriodicInterruptConfig();
void PwmConfig();

static void DisablePWM();
static void EnablePWM();
static float GetStepPWM( const uint16_t TOP );
void SetPwmDuty( float dutyPerc );
float GetPwmDuty();

#ifdef __cplusplus
}
#endif
#endif