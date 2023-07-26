#ifndef MAIN_H
#define MAIN_H

#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

void halt( void );

typedef struct {
  uint8_t g_enc_first_edge : 1;
} global_flags_TypeDef;

extern global_flags_TypeDef g_flags;

#ifdef __cplusplus
}
#endif
#endif