#include "Regulation.h"

PID_TypeDef PID_controller = {
  .params = {
    .kp = 0.15f,
    .ki = 0.005f,
    .kd = 1.00f
  },
  .limits = {
    .out_max = 100.0f,
    .out_min = 0.0f
  },
  .setPoint = 2100.0f / 60.0f,
  .T_ms = 2.0f,
  .integrator = 0.0f,
  .prevE = 0.0f
};

// typedef struct param {
float updatePID( PID_TypeDef* handler, float y )
{
  float U = 0;
  float P = 0;
  float I = 0;
  float D = 0;

  const float T = handler->T_ms / 1000.0f;
  const float E = handler->setPoint - y;

  //Error = E;

  P = E * handler->params.kp;

  handler->integrator += E;
  I = handler->params.ki * handler->integrator ;


  D = handler->params.kd * ( ( E - handler->prevE ) ); 
  handler->prevE = E;


  U =  P + I + D;  

  /*
    Clamp output to defined interval
  */
  if( U > handler->limits.out_max ) U = handler->limits.out_max;
  else if( U < handler->limits.out_min ) U = handler->limits.out_min;

  return U;
};



// inline uint16_t calcRPM( const uint8_t tim_cnt, const uint8_t sampling_period_ms )
// {
//   if( tim_cnt == 0 ) return 0;
//   const uint16_t sampleRate = 1000 / sampling_period_ms;
//   const uint32_t n_pulses_min = 60 * (uint32_t)tim_cnt * sampleRate;
//   return  n_pulses_min / ENC_N_PULSES ;
// };