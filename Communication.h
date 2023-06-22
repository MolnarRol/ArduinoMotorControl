#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include "Arduino.h"
#include <string.h>
#include "Commands.h"
#include "Debug.h"
#include "config.h"

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