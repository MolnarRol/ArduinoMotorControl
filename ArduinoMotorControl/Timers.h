#ifndef _TIMERS_H_
#define _TIMERS_H_

#include <stdint.h>
#include "Arduino.h"
#include "config.h"
#ifdef __cplusplus
extern "C" {
#endif

<<<<<<<< Updated upstream:ArduinoMotorControl/TimerConfig.h
typedef struct pulseStruct {
  uint32_t pulses[PULSES_MAX];
  volatile uint8_t pulseIdx;
} pulseTypeDef;

typedef struct pulseBuffers {
  pulseTypeDef buffer[2];
  uint8_t idx;
} pulseBuffersTypeDef;

void switchPulseBuff();
void writePulseBuff( uint32_t val );
uint32_t calcTimCntAVG( uint32_t* values, uint8_t len );
float filter_1stOrder_r32(float r32ActualValue, float r32SmoothedValue, float r32SamplingTime_ms, float r32FilterTime_ms);
float getRPMfromPulses();
float calcRPM( const uint32_t cnt );

/*
  PWM duty setter/getter
*/
void SetPwmDuty( float dutyPerc );
float GetPwmDuty();
========
void PeriodicInterruptEnable();
void PulseCaptureEnable();
>>>>>>>> Stashed changes:ArduinoMotorControl/Timers.h

/*
  Config functions
*/
void PulseCaptureConfig();
void PeriodicInterruptConfig();
void PwmConfig();

/*
  PWM on/off
*/
void DisablePWM();
void EnablePWM();
void setPinHighPWM();
void setPinLowPWM();

/*
  High impedance on/off
*/
// void DisablePWM_HiZ();
// void EnablePWM_HiZ();

/*
  Misc functions
*/
float GetStepPWM( const uint16_t TOP );
uint32_t readPulseCount();

#ifdef __cplusplus
}
#endif
#endif