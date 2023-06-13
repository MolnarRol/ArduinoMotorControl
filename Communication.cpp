#include "Communication.h"

char UART_buff[UART_BUFF_LEN];

Command CommandList[] = 
{
  { "clear", &clearTerminal },
  { "__End__", NULL }
}; 

void msgToCommand( String msg )
{
  if( msg == CommandList[0].cmd )
  {
    CommandList[0].p_function();
    return;
  }
  Serial.println(msg);
};