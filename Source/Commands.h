#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include <String.h>
#include "CommandCallbacks.h"

/*
  Commands and command group declaration
*/
typedef struct Command
{
  String cmd;                         // command string
  void (*p_function)( String msg );   // called void function
  String help;                        // help command string
} CommandTypeDef;

typedef struct CommandGroup
{
  String identity;                    // Group identifier for example >>[identity]>>
  String descript;                    // description in help command
  CommandTypeDef* List;               // List of used commands
} CommandGroupTypeDef;

#endif