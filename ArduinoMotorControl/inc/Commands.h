#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include "main.h"

/**
  \defgroup command_def Command group definitions
  Commands and command group declaration
  @{
*/
typedef struct Command
{
  const String cmd;                         // command string
  void (*p_function)( const String msg );   // called void function
} CommandTypeDef;

typedef struct CommandGroup
{
  const String identity;                    // Group identifier for example >>[identity]>>
  const CommandTypeDef* List;               // List of used commands
} CommandGroupTypeDef;
/// @}

extern CommandTypeDef MiscCommands[];
extern CommandGroupTypeDef* CommandGroupArr[];

#endif