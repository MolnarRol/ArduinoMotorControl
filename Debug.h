#ifndef _DEBUG_H_
#define _DEBUG_H_
#include "Arduino.h"

#ifdef __cplusplus
extern "C"{
#endif
/*
  Using Arduino pin D2 as debug pin
*/
inline void setPin();
inline void clearPin();
#ifdef __cplusplus
}
#endif
#endif