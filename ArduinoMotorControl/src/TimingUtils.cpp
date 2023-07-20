#include "../inc/TimingUtils.h"

 float g_l_val = 0.0f;

pulseBuffersTypeDef PulseBuffers = {0};
//  = {
//   .idx = 0,
//   .buffer[0].pulseIdx = 0,
//   .buffer[1].pulseIdx = 0
// };
void clearPulseBuffers()
{
  PulseBuffers.idx = 0;
  PulseBuffers.buffer[0].pulseIdx = 0;
  PulseBuffers.buffer[1].pulseIdx = 0;
}

void writePulseBuff( uint32_t val )
{
  pulseTypeDef* p_buff = &PulseBuffers.buffer[ PulseBuffers.idx ];
  p_buff->pulses[ p_buff->pulseIdx++ ] = val;
  if( p_buff->pulseIdx >= PULSES_MAX ) p_buff->pulseIdx = 0;
};

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
  uint32_t cnt_avg = calcTimCntAVG( PulseBuffers.buffer[ buff_i ].pulses, PulseBuffers.buffer[ buff_i ].pulseIdx );

  #if ( SPEED_FILTER_EN == 1 )
    g_l_val = filter_1stOrder_r32( cnt_avg, g_l_val, (float) REG_PERIOD_MS, FIR_TIME );
  #else
    g_l_val = cnt_avg;
  #endif

  PulseBuffers.buffer[ buff_i ].pulseIdx = 0;
  return calcRPM( g_l_val );
};

inline float calcRPM( const uint32_t cnt )
{
  if( cnt == 0 ) return 0.0f;
  float delta_us = (float)cnt * TIM_STEP_us;
  float cnt_per_rev = US_IN_MIN / (float)( ENC_N_PULSES * delta_us );
  return cnt_per_rev;
};