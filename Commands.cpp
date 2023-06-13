#include "Commands.h"

void clearTerminal()
{
  for( uint8_t i; i < 50; i++ )
    {
      Serial.println();
    }
};