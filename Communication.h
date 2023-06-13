#include "Arduino.h"
#include "Commands.h"
#define UART_BUFF_LEN 32


struct Command
{
  String cmd;  
  void (*p_function)( String msg );
  String help;
};

void msgToCommand( String msg );
void helper( String msg );

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
