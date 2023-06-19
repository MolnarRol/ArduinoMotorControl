#include "Regulation.h"

#define ENC_N_PULSES 100


// typedef struct param {
//   float kp;
//   float ki;
//   float kd;
// } paramTypeDef;

// typedef struct PID {
//   struct param 
// } PID_TypeDef;

// float updatePID( float setPoint, float y )
// {
//   const float E = setPoint - y;


// };

inline uint16_t calcRPM( const uint8_t tim_cnt, const uint8_t sampling_period_ms )
{
  const uint8_t samplingRate = 1000 / sampling_period_ms;
  return ( ENC_N_PULSES * 60 ) / ( tim_cnt * samplingRate);
};