#include "Arduino.h"
#include "Commands.h"

#include <stdio.h>
#include <string.h>

#define UART_BUFF_LEN 32
#define COMMAND_MAX_CHAR 16
#define MAX_WORDS_IN_PROMPT 5

void msgToCommand( String msg );
uint8_t stringToWords( String msg, String words[6] );
float parseFloat( String strNum );

static uint8_t charToDec( char ch ); 
static inline uint32_t powerOf10( uint8_t n );



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
