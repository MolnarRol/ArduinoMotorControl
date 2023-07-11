#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include <string.h>
#include "../config.h"
#include "CommandCallbacks.h"

/**
  \defgroup command_def Command group definitions
  Commands and command group declaration
  @{
*/
typedef struct Command
{
  const String cmd;                         // command string
  void (*p_function)( const String msg );   // called void function
  const String help;                        // help command string
} CommandTypeDef;

typedef struct CommandGroup
{
  const String identity;                    // Group identifier for example >>[identity]>>
  const String descript;                    // description in help command
  const CommandTypeDef* List;               // List of used commands
} CommandGroupTypeDef;
/// @}

#endif