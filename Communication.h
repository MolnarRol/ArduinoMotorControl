#include "Arduino.h"
#include "Commands.h"

#include <stdio.h>
#include <string.h>

#define UART_BUFF_LEN 32
#define COMMAND_MAX_CHAR 16
#define MAX_WORDS_IN_PROMPT 5

void msgToCommand( String msg );
float parseFloat( String strNum );
static uint8_t charToDec( char ch ); 
uint8_t stringToWords( String msg, String words[6] );




// struct CommandGroup
// {
//   String GroupName;
//   Command CommandList[];
// }

// struct Command
// {
//   String cmd;  
//   void (*p_function)( String msg );
//   String help;
// };

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
