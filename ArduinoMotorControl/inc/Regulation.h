#ifndef _REGULATION_H_
#define _REGULATION_H_
#include "../config.h"
#include "TimerConfig.h"

/// Structure for PID regulator gains.
typedef struct {
  /// Proportial gain
  float kp;

  /// Integral gain
  float ki;

  /// Derivative gain
  float kd;
} PID_paramTypeDef;

/// Structure for PID regulator output limits.
/// Variables define regulator output interval.
typedef struct limits {

  /// Maximum value of regulator output.
  float out_max;

  /// Minimum value of regulator output.
  float out_min;
} PID_limitsTypeDef;

/**
  \defgroup regulation PID regulator
  @{
*/
typedef struct {
  /// Structure for PID regulator gains.
  PID_paramTypeDef params;

  /// Structure for PID regulator output limits.
  PID_limitsTypeDef limits;

  /// Setpoint variable.
  float setPoint;

  /// Period in [ms] of regulation output calculation.
  float T_ms;

  /// Value of integral.
  float integrator;

  /// Previous error term.
  float prevE;

  /// [Not documented yet]
  float scalingFactor;

  /// Variable for toggling on/off regulator.
  /// Options: 1 (on), 0 (off)
  uint8_t enable;
  uint8_t motor_start;  // if "1" – motor starts from 0 rpm with 100% duty – regulation starts after achieving RPM defined by macro SETPOINT_DEFAULT (config.h)

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
/// @}
#endif
#endif
