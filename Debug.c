#include "Debug.h"

inline void setPin()
{
  PORTD |= 0b00000100;
};

inline void clearPin()
{
  PORTD &= 0b11111011;
};