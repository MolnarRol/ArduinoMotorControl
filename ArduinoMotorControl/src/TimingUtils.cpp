#include "../inc/TimingUtils.h"

float g_l_val = 0.0f;
pulseBuffersTypeDef PulseBuffers = {0};

uint32_t calcTimCntAVG( uint32_t* values, uint8_t len )
{
  if( len == 0 ) return 0;
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

float getRPMfromPulses( void )
{
  const uint8_t buff_i = PulseBuffers.idx ^ 1;
  static float l_val = 0.0f;
  uint32_t cnt_avg = calcTimCntAVG( PulseBuffers.buffer[ buff_i ].pulses, PulseBuffers.buffer[ buff_i ].pulseIdx );
  // l_val = filter_1stOrder_r32( cnt_avg, l_val, (float) REG_PERIOD_MS, FIR_TIME );
  l_val = cnt_avg;
  PulseBuffers.buffer[ buff_i ].pulseIdx = 0;
  return calcRPM( l_val );
};

inline float calcRPM( const uint32_t cnt )
{
  if( cnt == 0 ) return 0.0f;
  float delta_us = (float)cnt * TIM_STEP_us;
  float cnt_per_rev = US_IN_MIN / (float)( ENC_N_PULSES * delta_us );
  return cnt_per_rev;
};