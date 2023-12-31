@mainpage Project documentation

**For complete project documentation see documentation generated by doxygen: doc/html/index.html.**
# Default project peripherals configurations and IO pins

[MCU Documentation](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)

## Timers

Timer            | Function 
:--------------: | -----------------------------------------------------------------
Timer 0 (8-bit)  | Pulse counter of the rotary encoder - interrupt on compare match
Timer 1 (16-bit) | PWM for regulation output
Timer 2 (8-bit)  | ISR for calling regulation function every 2 ms

# Timer 0 - Pulse counter


## IO

Arduino pin | Atmega pin | Function
:---------: | :--------: | ----------------
D4          | PD4        | Rotary encoder input
D5          | PD5        | Direction pin
D7          | PD7        | Brake pin
D9          | PB1        | PWM output

## Serial communication

Baud rate | End character
:-------: | ---------------
115200    | Carriage return


# Configuration
  Configuration is done by modifying the config.h file with [macros](group__config.html).
  For commands information read the software manual.

# Adding custom function group

1.) Define new command group (Commands.cpp):

      CommandGroupTypeDef <name> = 
      {
        <identity>,         // string compared
        <descriptor>,       // brief description of command group (help command) [in progress]
        <array>             // pointer to array creted in 2.)
      }      
2.) Define command array (Commands.cpp):
      
      CommandTypeDef array[] =
      {
        { <command>, &functionCallbackPointer, <descriptor> },  // Command creation
        { "__End__", NULL }                                     // This array must end with this line
      }      
3.) Write new pointer of 1.) to CommandGroupTypeDef* CommandGroupArr[] (Commands.cpp)

      CommandGroupTypeDef* CommandGroupArr[] = 
      {
        &PWM,
        &BRAKE,
        &DIR,
        &<name>,
        NULL
      };
4.) Declare function callbacks of commands [ 2.) functionCallbackPointer ] in Commands.h:

      void yourFunction( String someString ); // Function needs to follow exact declaration
5.) Implement yourFunction() in CommandCallbacks.cpp

# Useful commands
      - clear –> clears output terminal
      - back  –> jumps out of sellected command group
      - help  –> print out all available commands [in progress]
