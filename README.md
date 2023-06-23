# Configuration and manual
  Configuration is done by modifying the config.h file.
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
