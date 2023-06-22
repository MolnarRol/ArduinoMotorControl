#ifndef _REGULATION_H_
#define _REGULATION_H_

#include "Arduino.h"

typedef struct param{
  float kp;
  float ki;
  float kd;
} paramTypeDef;

typedef struct limits{
  float out_max;
  float out_min;
} limitsTypeDef;

typedef struct PID{
  paramTypeDef params;
  limitsTypeDef limits;
  
  float setPoint;
  float T_ms;
  float integrator;
  float prevE;  
  
} PID_TypeDef;



#ifdef __cplusplus
extern "C" {
#endif

float updatePID( PID_TypeDef* handler, float y );
// uint16_t calcRPM( const uint8_t tim_cnt, const uint8_t sampling_period_ms );


#ifdef __cplusplus
}
#endif
#endif
