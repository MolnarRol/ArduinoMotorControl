#include "Arduino.h"

// typedef struct Command
// {
//   String cmd;                         // command string
//   void (*p_function)( String msg );   // called void function
//   String help;                        // help command string
// } CommandTypeDef;

// typedef struct CommandGroup
// {
//   String identity;                    // Group identifier for example >>[identity]>>
//   String descript;                    // description in help command
//   CommandTypeDef List[];              // List of used commands
// } CommandGroupTypeDef;

// typedef struct CommandMainStruct
// {
//   CommandTypeDef MiscCommands[];
//   CommandGroupTypeDef groups[];  
// } CommandMainStructTypeDef;

void SetPwmDuty( float dutyPerc );

void clearTerminal( String msg );
void helper( String msg );