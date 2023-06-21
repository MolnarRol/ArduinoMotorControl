/*
  Test motor controll MCU project.

  Timer config:
    - Timer 0 (8-bit): Pulse counter of the roatary encoder - interupt on compare match
    - Timer 1 (16-bit): PWM for regulation output
    - Timer 2 (8-bit): ISR for calling regulation function every 2 ms

  Input/Output pins:
    - D4: Rotary encoder input
    - D9: PWM output

  Additional info:  
    Documentation: https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
*/

#include "Communication.h"
#include "Regulation.h"
#include "TimerConfig.h"
#include "Debug.h"

extern uint16_t g_TIM0_ov;

uint8_t pulses[40];
uint8_t n_pulses = 0; // DEBUG variable
uint32_t DEBUG = 0;
uint8_t pulseReadBlock = 0;

uint8_t calcTimCntAVG( uint8_t* values, uint8_t len );

ISR( TIMER2_COMPA_vect )
{
  sei();   // Reenable interrupts
  // pulseReadBlock = 1;
  // uint8_t avg = calcTimCntAVG(pulses, n_pulses);
  // n_pulses = 0;
  // pulseReadBlock = 0;
  // uint16_t rpm = calcRPM(avg); //calcRPM(

  // n_pulses = 0;
  // Serial.print("AVG: ");
  //Serial.println(rpm);
}

boolean test = 0;

ISR( PCINT2_vect )
{
  // if( !pulseReadBlock )
  // {
  //   if( ( PORTD & ~(1 << PORTD4) ) > 0 ) {
      // pulses[n_pulses++] = readPulseCount();
      DEBUG = 2 * readPulseCount();
  //   }
  // }  
}

ISR( TIMER0_COMPA_vect )
{
  g_TIM0_ov++;
}

void setup() {
  PulseCaptureConfig();       // Rotary encoder capture
  PwmConfig();                // Output PWM signal
  PeriodicInterruptConfig();  // Generation periodic interrupt each 2 ms

  Serial.begin(115200);
  clearTerminal( "" );

  pinMode(2, OUTPUT);         // Debug pin
  pinMode(7, OUTPUT);         // Brake pin
  pinMode(5, OUTPUT);         // Direction pin

  // SetPwmDuty(0);              // Set speed to 0
  // BRAKE_off_Callback("");     // Disengage brake

  // DEBUG
  SetPwmDuty(25.0f);
  BRAKE_off_Callback("");     // Disengage brake
  DisablePWM_HiZ();
  EnablePWM();
}

void loop() {
  // printHeader();
  // String msg = getStringUART();
  // if( msg.length() > 0 )
  // {
  //   Serial.println( msg );
  //   msgToCommand( msg );
  // }
  // else Serial.println();



  // Serial.print("Pulse count: ");
  Serial.println(DEBUG);
  // Serial.print("RPM: ");
  // Serial.println( calcRPM(n_pulses, 2) );
}

uint8_t calcTimCntAVG( uint8_t* values, uint8_t len )
{
  if( len == 0 ) return 0;
  uint16_t sum = 0;
  for( uint8_t i = 0; i < len; i++ )
  {
    sum += values[i];
  }
  return sum / len;
};