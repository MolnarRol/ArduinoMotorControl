#include <string.h>
#include <stdint.h>
#include "Arduino.h"

#include "config.h"
#include "inc/main.h"
#include "inc/APP_Interrupts.h"
#include "inc/Commands.h"
#include "inc/CommandCallbacks.h"
#include "inc/Communication.h"
#include "inc/Regulation.h"
#include "inc/Timers.h"
#include "inc/TimingUtils.h"
#include "inc/StateMachine.h"


// global_flags_TypeDef g_flags = {
//   g_enc_first_edge = 1
// };

/// Arduino setup function
void setup() {
  /*
    UART setup
  */
  Serial.begin( UART_BAUD );
  // float bytesToFloat( const uint8_t bytes[4] );
  // void floatToBytes( const float input, uint8_t bytes[4] );
  float x = 3.14f;
  uint8_t bytes[4];
  floatToBytes( x, bytes );
  char byteArray[5];

  for( uint8_t i = 0; i < 4; i++ )
  {
    byteArray[i] = (char)bytes[i];
    Serial.println( (char)bytes[i], HEX );
  }
  byteArray[4] = 0;
  Serial.print( byteArray );
  

  while(1);
  
  // clearTerminal( "" );

  // #ifdef DEBUG
  //   Serial.println( F("[MCU reset]") );
  // #endif

  /*
    Timer setup functions
  */
  PulseCaptureConfig();       // Rotary encoder capture
  PwmConfig();                // Output PWM signal
  PeriodicInterruptConfig();  // Generation periodic interrupt each 2 ms

  /*
    Digital pin setup
  */
  pinMode(DEBUG_PIN, OUTPUT);       // Debug pin
  pinMode(BRK_PIN, OUTPUT);         // Brake pin
  pinMode(DIR_PIN, OUTPUT);         // Direction pin
  digitalWrite( BRK_PIN, 1 );       // Disengage brake


  // DisablePWM_HiZ();
  pinMode( 9, OUTPUT );
  SetPwmDuty( 0.0f );               // PWM is turned off
  // setPinHighPWM();
  pinMode( 4, INPUT ); // _PULLUP

  // MOTOR_on_Callback("");
  // while( 1 );

  // #ifdef DEBUG
  //   Serial.println( F("[Setup complete]") );
  // #endif
}

/**
 * Main code loop
 * This loop handles all UART communication
*/
void loop() {                    
  printHeader();            
  String msg = getStringUART();
  if( msg.length() > 0 )
  {
    Serial.println( msg );
    msgToCommand( msg );
  }
  else Serial.println(); 
}

/**
 * Function that stops MCU operation.
 * Can be called where the behavior of code can result to unexpected/bad behaviour. 
*/
void halt( void )
{
  SetPwmDuty(0.0f);     // Disable PWM
  cli();                // Globally disable interrupts
  while(1) {};          // Endless loop
}