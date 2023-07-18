#include "inc/main.h"

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
  setPinHighPWM();

  #if ( REG_MOTOR_AUTOSTART == 1 )
    DisablePWM_HiZ();           // Disable high impedance state of PWM output pin
    EnablePWM();                // Enabling PWM
    extern MODE sellected_mode;
    sellected_mode = regulation;
    MOTOR_on_Callback("");
  #endif

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
  else Serial.println(); 
}


void halt( void )
{
  DisablePWM();
  setPinHighPWM();
  cli();
  while(1);
}