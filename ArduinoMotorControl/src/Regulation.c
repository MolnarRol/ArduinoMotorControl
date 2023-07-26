#include "../inc/Regulation.h"

PID_TypeDef PID_controller = {

  .params = {
    .kp = KP,
    .ki = KI,
    .kd = KD
  },

  .limits = {
    .out_max = 100.0f,
    .out_min = 0.0f
  },

  .setPoint = SETPOINT_DEFAULT,
  .T_ms = REG_PERIOD_MS,
  .integrator = 0.0f,
  .prevE = 0.0f,
  .scalingFactor = 60.0f,
  
  .enable = 0,
  .motor_start = 1
};

/**
  @param handler PID regulation struct that is used to calculate the regulation output.
  @param y Regulated system output variable.
  @return Regulator output for controlled system.
*/
float updatePID( PID_TypeDef* handler, float y )
{
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

  #if ARW_EN == 1
    if( I > handler->limits.out_max )
    {
      handler->integrator = handler->limits.out_max / KI;
    }
    else if( I < handler->limits.out_min )
    {
      handler->integrator = handler->limits.out_min / KI;
    }
  #endif

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
  }
  else if( U < handler->limits.out_min ) 
  {
    U = handler->limits.out_min;
  };

 return U;
};

void changeSetPoint( PID_TypeDef* handler, float newSetPoint )
{
  if( newSetPoint >= RPM_MIN && newSetPoint <= RPM_MAX ) handler->setPoint = newSetPoint;
}

inline void startRegulation( PID_TypeDef* handler )
{
  handler->integrator = GetPwmDuty() / handler->params.ki;    // integrator preload
  handler->enable = 1;
};

inline void stopRegulation( PID_TypeDef* handler )
{
  handler->enable = 0;
};

inline void boostStartHandler( PID_TypeDef* handler, const float RPM )
{
  if(  handler->motor_start )
  {
    if( RPM > MOTOR_RPM_REG_START ) 
    {
      handler->motor_start = 0;
      startRegulation( handler );
    }
    else SetPwmDuty( 100.0f );
  }
};