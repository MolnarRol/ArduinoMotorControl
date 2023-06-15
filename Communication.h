
#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include <stdio.h>
#include <string.h>
#include "Arduino.h"
#include "Commands.h"
#include "Debug.h"

#define COMMAND_MAX_CHAR 16     // Maximum number of characters in a single word
#define MAX_WORDS_IN_PROMPT 2   // Maximum number of words that can be processed

/*
  String manipulation and function calling
*/
String getStringUART();
void printHeader();
void msgToCommand( String msg );
uint8_t stringToWords( String msg, String words[6] );
float parseFloat( String strNum );

/*
  Misc functions
*/
void clearTerminal( String msg );
void resetGroup( String msg );
void helper( String msg );

uint8_t charToDec( char ch ); 
uint32_t charStrToDec( char* numStr );
uint32_t powerOf10( uint8_t n );
#endif