#include "Arduino.h"

struct Command
{
  String cmd;  
  void (*p_function)( String msg );
  String help;
};

void clearTerminal( String msg );
void helper( String msg );