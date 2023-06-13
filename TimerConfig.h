#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "Arduino.h"


void PulseCaptureConfig();
void PeriodicInterruptConfig();
void PwmConfig();
void SetPwmDuty( float dutyPerc );  // 100% = 1000 promile

#ifdef __cplusplus
}
#endif