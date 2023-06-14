#include "Commands.h"

// typedef struct Command
// {
//   String cmd;                         // command string
//   void (*p_function)( String msg );   // called void function
//   String help;                        // help command string
// } CommandTypeDef;

// typedef struct CommandGroup
// {
//   String identity;                    // Group identifier for example >>[identity]>>
//   String descript;                    // description in help command
//   CommandTypeDef List[];              // List of used commands
// } CommandGroupTypeDef;

// typedef struct CommandMainStruct
// {
//   CommandGroupTypeDef groups[];
//   CommandTypeDef MiscCommands[];
// }

// CommandGroupTypeDef PWM = 
// {
//   "PWM",
//   "Commands used for PWM manipulation",
//   {}
// };



void clearTerminal( String msg )
{
  for( uint8_t i; i < 50; i++ ) Serial.println();
};

void SetPwmDuty( float dutyPerc )
{
  if( dutyPerc > 100.0f || dutyPerc < 0.0f ) return;
  /* 
  The timer resolution can be adjusted in descrete steps by 0.125% 
  if we provide lower value than 0.125 than we turn of the PWM and set port to output logic LOW 
  */
  if( dutyPerc < 0.125f )   
  {
    TCCR1A &= ~(1 << 7 );   // Turn of PWM
    PORTB &= ~(1 << 1 );    // set port to logic low
    return;
  }
  else
  {
    TCCR1A |= (1 << 7 );    // turn on PWM
  }  
  OCR1A = (uint16_t)( 8.0f * dutyPerc ) - 1;
};

// void helper( String msg )
// {
//   Serial.println("All possible commands:");
//   uint8_t id = 0;  

//   while( CommandList[id].cmd != "__End__"  )
//   {
//     Serial.println("\t- " + CommandList[id].cmd + ":\t\t" + CommandList[id].help );
//     id++;
//   }  
// };
