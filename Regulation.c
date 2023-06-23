#include "Regulation.h"

PID_TypeDef PID_controller = {

  .params = {
    .kp = Kp,
    .ki = Ki,
    .kd = Kd
  },

  .limits = {
    .out_max = 100.0f,
    .out_min = 0.0f
  },

  .setPoint = SETPOINT_DEFAULT,
  .T_ms = 2.0f,
  .integrator = 0.0f,
  .prevE = 0.0f,
  .scalingFactor = 60.0f,
  .enable = 0

};

float updatePID( PID_TypeDef* handler, float y )
{
  if( !handler->enable )
  {
    return 0.0f;
  }

  float U = 0;
  float P = 0;
  float I = 0;
  float D = 0;

  const float T = handler->T_ms / 1000.0f;                                // Conversion from [ms] -> [s]
  const float E = ( handler->setPoint - y ) / handler->scalingFactor;     // Regulation error calculation

  /*
    Proporial term
  */
  P = E * handler->params.kp;

  /*
    Integral term
  */
  handler->integrator += E;
  I = handler->params.ki * handler->integrator ;

  /*
    Derivative term
  */
  D = handler->params.kd * ( ( E - handler->prevE ) ); 
  handler->prevE = E;

  /*
    Calculated regulation output
  */
  U =  P + I + D;  

  /*
    Clamp output to defined interval
  */
  if( U > handler->limits.out_max )
  {
    U = handler->limits.out_max;
    handler->integrator -= E;         // Anti reset windup
  }
  else if( U < handler->limits.out_min ) U = handler->limits.out_min;

  return U;
};

void changeSetPoint( PID_TypeDef* handler, float newSetPoint )
{
  if( newSetPoint >= RPM_MIN && newSetPoint <= RPM_MAX ) handler->setPoint = newSetPoint;
}

void startRegulation( PID_TypeDef* handler )
{
  handler->enable = 1;
};

void stopRegulation( PID_TypeDef* handler )
{
  handler->enable = 0;
  handler->integrator = 0.0f;
  handler->prevE = 0.0f;
  handler->setPoint = SETPOINT_DEFAULT;
};
