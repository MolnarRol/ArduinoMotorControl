#ifndef _TIMING_UTILS_H_
#define _TIMING_UTILS_H_

#include "Arduino.h"
#include "../config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct pulseStruct {
  uint32_t pulses[PULSES_MAX];
  volatile uint8_t pulseIdx;
} pulseTypeDef;

typedef struct pulseBuffers {
  pulseTypeDef buffer[2];
  uint8_t idx;
} pulseBuffersTypeDef;

<<<<<<< HEAD
void switchPulseBuff();
void writePulseBuff( const uint32_t val );
=======
void writePulseBuff( uint32_t val );
>>>>>>> parent of f48da27... Boost start - bugfix
uint32_t calcTimCntAVG( uint32_t* values, uint8_t len );
float filter_1stOrder_r32(float r32ActualValue, float r32SmoothedValue, float r32SamplingTime_ms, float r32FilterTime_ms);
float getRPMfromPulses();
float calcRPM( const uint32_t cnt );

#ifdef __cplusplus
}
#endif
#endif