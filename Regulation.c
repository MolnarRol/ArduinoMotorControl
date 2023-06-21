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
  if( tim_cnt == 0 ) return 0;
  const uint16_t sampleRate = 1000 / sampling_period_ms;
  const uint32_t n_pulses_min = 60 * (uint32_t)tim_cnt * sampleRate;
  return  n_pulses_min / ENC_N_PULSES ;
};