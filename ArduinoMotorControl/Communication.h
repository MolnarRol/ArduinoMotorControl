#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include "Arduino.h"
#include <string.h>
<<<<<<< Updated upstream:ArduinoMotorControl/Communication.h
#include "Commands.h"
#include "config.h"
=======

#include "../config.h"
#include "CommandCallbacks.h"

// debug
#include "Timers.h"

>>>>>>> Stashed changes:ArduinoMotorControl/inc/Communication.h

/*
  String manipulation and function calling
*/
String getStringUART();
void printHeader();
void msgToCommand( String msg );
void resetGroup( String msg );
float parseFloat( String strNum );

/*
  Global functions
*/
void clearTerminal( String msg );
void helper( String msg );
<<<<<<< Updated upstream:ArduinoMotorControl/Communication.h

/**
 * Static functions
*/
static uint32_t charStrToDec( char* numStr );
static uint8_t charToDec( char ch ); 
static uint8_t stringToWords( String msg, String words[6] );
static uint32_t powerOf10( const uint8_t n );
=======
void test( String msg );
uint32_t powerOf10( uint8_t n );
>>>>>>> Stashed changes:ArduinoMotorControl/inc/Communication.h
#endif