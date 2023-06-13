#include "Commands.h"

void clearTerminal( String msg )
{
  for( uint8_t i; i < 50; i++ )
    {
      Serial.println();
    }
};