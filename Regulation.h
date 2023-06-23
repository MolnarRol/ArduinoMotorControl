#ifndef _REGULATION_H_
#define _REGULATION_H_

#include "TimerConfig.h"
#include "config.h"

typedef struct param {
  float kp;
  float ki;
  float kd;
} paramTypeDef;

typedef struct limits {
  float out_max;
  float out_min;
} limitsTypeDef;

typedef struct PID {
  paramTypeDef params;
  limitsTypeDef limits;

  float setPoint;
  float T_ms;
  float integrator;
  float prevE;
  float scalingFactor;
  uint8_t enable;
} PID_TypeDef;

#ifdef __cplusplus
extern "C" {
#endif

  float updatePID(PID_TypeDef* handler, float y);
  void changeSetPoint(PID_TypeDef* handler, float newSetPoint);

  void startRegulation( PID_TypeDef* handler );
  void stopRegulation( PID_TypeDef* handler );
  
#ifdef __cplusplus
}
#endif
#endif
