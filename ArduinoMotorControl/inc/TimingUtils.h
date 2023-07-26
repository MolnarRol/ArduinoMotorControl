#ifndef _TIMING_UTILS_H_
#define _TIMING_UTILS_H_

#include "Arduino.h"
#include "../config.h"
#include "Buffer.h"

extern float g_l_val;
// extern pulseBuffersTypeDef PulseBuffers;

uint32_t calcTimCntAVG( uint32_t* values, uint8_t len );
float filter_1stOrder_r32(float r32ActualValue, float r32SmoothedValue, float r32SamplingTime_ms, float r32FilterTime_ms);
float getRPMfromPulses( void );
float calcRPM( const uint32_t cnt );
#endif