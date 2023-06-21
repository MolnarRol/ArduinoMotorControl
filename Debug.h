#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#ifdef __cplusplus
extern "C" {
#endif
/*
  Using Arduino pin D2 as debug pin
*/
void setPin();
void clearPin();
#ifdef __cplusplus
}
#endif
#endif