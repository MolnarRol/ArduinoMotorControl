#ifndef _TIMER_CONFIG_H_
#define _TIMER_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "Arduino.h"

void SetPwmDuty( float dutyPerc );
float GetPwmDuty();

void PulseCaptureConfig();
void PeriodicInterruptConfig();
void PwmConfig();

#ifdef __cplusplus
}
#endif
#endif