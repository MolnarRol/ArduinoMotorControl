#ifndef _REGULATION_H_
#define _REGULATION_H_

#include "Arduino.h"

// typedef struct param{
//   float kp;
//   float ki;
//   float kd;
// } paramTypeDef;

// typedef struct PID{
//   paramTypeDef params;
// } PID_TypeDef;

#ifdef __cplusplus
extern "C" {
#endif

uint16_t calcRPM( const uint8_t tim_cnt, const uint8_t sampling_period_ms );
float updatePID( float setPoint, float y );

#ifdef __cplusplus
}
#endif
#endif
