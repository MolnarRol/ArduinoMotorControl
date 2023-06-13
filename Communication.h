#include "Arduino.h"
#include "Commands.h"
#define UART_BUFF_LEN 32


struct Command
{
  String cmd;  
  void (*p_function)();
  String help;
};

void msgToCommand( String msg );
void helper();

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
