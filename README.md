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

# Software manual
Types of commands:
- **Global** – Can be called everywhere.
- **Group** – Can be called just when the correct command group is selected.

After startup of the MCU no command group is sellected. To sellect command group type exact name of
the group. After hitting “enter” the command group will be sellected.

      >> [command group]

After command group sellection you can type desired command with argument (if specified). To exit the
command group use the **back** command.

      >> [command group] >> [command] [argument]

## Global commands
command     | Description
:---------: | -----------------------------------------------------------------------------------------
**clear**   | Clears output terminal.
**back**    | Exits current command group.
**status**  | Prints out sellected mode. Current(real) RPM and PWM duty cycle.
**help**    | Prints out all available commands.

## Command groups

### CONTROL <ct>
command     | argument                    | Description
:---------: | :-------------------------: | -------------------------------------------------------------
mode        | reg / man                   | If second argument is given(optional: mode), then it specifies desired mode.
start       | -                           | Starts the motor from 0 RPM.
stop        | -                           | Stops the motor.
duty        | <new duty>                  | Prints out currently set RPM. If second argument is given(optional: number), then it specifies desired RPM. (reg mode)
s           | <n>                         | Sets speed saved in SPEEDS, where n is array index + 1. (reg mode)
"+"         | -                           | Increases speed from current speed index n. (reg mode)
"-"         | -                           | Decreases speed from current speed index n. (reg mode)

### BRAKE <brake>

command     | argument                    | Description
:---------: | :-------------------------: | -------------------------------------------------------------
on          | -                           | Brake is activated.
off         | -                           | Brake is deactivated.

### Direction <dir>

command     | argument                    | Description
:---------: | :-------------------------: | -------------------------------------------------------------
cw          | -                           | Motor is set to turn clockwise.
ccw         | –                           | Motor is set to turn counter clockwise.
chDir       | –                           | Changes motor turn direction.

## Adding custom functionality

1.) Define new command group in Commands.cpp:

      CommandGroupTypeDef <name> = 
      {
        <identity>,         // string compared
        <descriptor>,       // brief description of command group (help command) [in progress]
        <array>             // pointer to array creted in 2.)
      }      
2.) Define command array in Commands.cpp:
      
      CommandTypeDef array[] =
      {
        { <command>, &functionCallbackPointer, <descriptor> },  // Command creation
        { "__End__", NULL }                                     // This array must end with this line
      }      
3.) Write new pointer of 1.) to CommandGroupTypeDef* CommandGroupArr[] Commands.cpp

      CommandGroupTypeDef* CommandGroupArr[] = 
      {
        &CONTROL,
        &BRAKE,
        &DIR,
        &<name>,
        NULL
      };
4.) Declare function callbacks of commands [ 2.) functionCallbackPointer ] in Commands.h:

      void yourFunction( String someString ); // Function needs to follow exact declaration

5.) Implement `yourFunction()` in CommandCallbacks.cpp
