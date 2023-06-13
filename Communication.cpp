#include "Communication.h"

char UART_buff[UART_BUFF_LEN];

Command CommandList[] = 
{
  { "clear", &clearTerminal, "Clear output terminal" },
  { "help", &helper, "Print all possible commands" },
  { "pid on", NULL, "Turn on PID regulation" },
  { "__End__", NULL }
}; 

void msgToCommand( String msg )
{
  uint8_t id = 0;  
  if( msg != "clear" ) Serial.println(msg);

  while( CommandList[id].cmd != "__End__" )
  {
    if( msg == CommandList[id].cmd )
    {      
      CommandList[id].p_function();
      return;
    }    
    id++;
  }  
  Serial.println( "\t\"" + msg + "\" is invalid command");
};

void helper()
{
  Serial.println("All possible commands:");
  uint8_t id = 0;  

  while( CommandList[id].cmd != "__End__"  )
  {
    Serial.println("\t- " + CommandList[id].cmd + ":\t\t" + CommandList[id].help );
    id++;
  }  
};
