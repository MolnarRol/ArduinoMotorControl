#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>

#define WEAK __attribute__((weak))
#define DOUBLE_BUFF_MAX_SIZE 64

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    volatile uint8_t active_buffer;                 // index of sub_buffer that is currently written to
    // // void (*bufferFullCallback)( void* buffer );     // pointer to function that is called if one of the subbuffers is full
    struct 
    {
        uint8_t buffer_top;
        uint32_t values[DOUBLE_BUFF_MAX_SIZE];
    } sub_buffer[2];
  
} U32_DoubleBuffer_TypeDef;

void U32_DoubleBuffer_Flush( U32_DoubleBuffer_TypeDef* buffer );
inline void U32_DoubbleBuffer_Switch( U32_DoubleBuffer_TypeDef* buffer );
void U32_DoublleBuffer_Write( const uint32_t val, U32_DoubleBuffer_TypeDef* buffer );

void clearPulseBuffers();
void writePulseBuff( uint32_t val );


WEAK void U32_DoubleBuffer_FULL( void* buffer );

#ifdef __cplusplus
}
#endif

#endif  // BUFFER_H