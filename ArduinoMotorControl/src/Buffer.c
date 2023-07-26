#include "../inc/Buffer.h"

// void writePulseBuff( uint32_t val )
// {
//   pulseTypeDef* p_buff = &PulseBuffers.buffer[ PulseBuffers.idx ];
//   p_buff->pulses[ p_buff->pulseIdx++ ] = val;
//   if( p_buff->pulseIdx >= PULSES_MAX ) p_buff->pulseIdx = 0;
// };

void U32_DoubleBuffer_Flush( U32_DoubleBuffer_TypeDef* buffer )
{   
    buffer->active_buffer = 0;
    buffer->sub_buffer[0].buffer_top = 0;
    buffer->sub_buffer[1].buffer_top = 0;
};

inline void U32_DoubbleBuffer_Switch( U32_DoubleBuffer_TypeDef* buffer )
{
    buffer->active_buffer ^= 1;
};

void U32_DoublleBuffer_Write( const uint32_t val, U32_DoubleBuffer_TypeDef* buffer )
{
    const uint8_t sub_buffer_top =  buffer->sub_buffer[ buffer->active_buffer ].buffer_top++;
    buffer->sub_buffer[ buffer->active_buffer ].values[sub_buffer_top] = val;
}

WEAK void U32_DoubleBuffer_FULL( void* buffer )
{

};