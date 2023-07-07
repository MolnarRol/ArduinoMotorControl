#include "TimingUtils.h"

pulseBuffersTypeDef PulseBuffers = {
  .idx = 0,
  .buffer[0].pulseIdx = 0,
  .buffer[1].pulseIdx = 0
};

inline void switchPulseBuff()
{
  PulseBuffers.idx ^= 1;
};

inline void writePulseBuff( uint32_t val )
{
  pulseTypeDef* p_buff = &PulseBuffers.buffer[ PulseBuffers.idx ];
  p_buff->pulses[ p_buff->pulseIdx++ ] = val;
  if( p_buff->pulseIdx >= PULSES_MAX ) p_buff->pulseIdx = 0;
};

uint32_t calcTimCntAVG( uint32_t* values, uint8_t len )
{
  if( len == 0 ) return 0xFFFFFFFF;
  uint32_t sum = 0;
  for( uint32_t i = 0; i < len; i++ )
  {
    sum += values[i];
  }
  return sum / len;
};

float filter_1stOrder_r32(float r32ActualValue, float r32SmoothedValue, float r32SamplingTime_ms, float r32FilterTime_ms) {

    float r32FilterCoef;

    r32FilterCoef = r32SamplingTime_ms/(r32SamplingTime_ms+r32FilterTime_ms);
    return (r32FilterCoef*r32ActualValue + (1-r32FilterCoef)*(r32SmoothedValue));

}

float getRPMfromPulses()
{
  uint8_t buff_i;
  static float l_val = 0.0f;

  PulseBuffers.idx ^= 1;

  uint32_t cnt_avg = calcTimCntAVG( PulseBuffers.buffer[ buff_i ].pulses, PulseBuffers.buffer[ buff_i ].pulseIdx );

  uint32_t cnt_filtered = filter_1stOrder_r32( cnt_avg, l_val, 2.0f , FIR_TIME );
  l_val = cnt_filtered;

  PulseBuffers.buffer[ buff_i ].pulseIdx = 0;
  return calcRPM( cnt_filtered );
};

inline float calcRPM( const uint32_t cnt )
{
  float delta_us = (float)cnt * TIM_STEP_us;
  float cnt_per_rev = US_IN_MIN / (float)( ENC_N_PULSES * delta_us );
  return cnt_per_rev;
};