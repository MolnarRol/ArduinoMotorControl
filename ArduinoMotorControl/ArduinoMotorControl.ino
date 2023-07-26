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

// global_flags_TypeDef g_flags = {
//   g_enc_first_edge = 1
// };

/// Arduino setup function
void setup() {
  /*
    UART setup
  */
  Serial.begin( UART_BAUD );
  clearTerminal( "" );

  #ifdef DEBUG
    Serial.println( F("[MCU reset]") );
  #endif

  /*
    Timer setup functions
  */
  PulseCaptureConfig();             // Rotary encoder capture
  PwmConfig();                      // Output PWM signal
  PeriodicInterruptConfig();        // Generation periodic interrupt each 2 ms

  /*
    Digital pin setup
  */
  pinMode(DEBUG_PIN, OUTPUT);       // Debug pin
  pinMode(BRK_PIN, OUTPUT);         // Brake pin
  pinMode(DIR_PIN, OUTPUT);         // Direction pin
  digitalWrite( BRK_PIN, 1 );       // Disengage brake

  pinMode( 9, OUTPUT );
  SetPwmDuty( 0.0f );               // PWM is turned off
  pinMode( 4, INPUT );

  #ifdef DEBUG
    Serial.println( F("[Setup complete]") );
  #endif
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