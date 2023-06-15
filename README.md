# Adding custom function group

Adding command groups and functions>
1.) Define new command group (communication.cpp):

      CommandGroupTypeDef <name> = 
      {
        <identity>,         // string compared
        <descriptor>,       // brief description of command group (help command) [in progress]
        <array>             // pointer to array creted in 2.)
      }      
2.) Define command array (communication.cpp):
      
      CommandTypeDef array[] =
      {
        { <command>, &functionCallbackPointer, <descriptor> },  // Command creation
        { "__End__", NULL }                                     // This array must end with this line
      }      
3.) Write new pointer of 1.) to CommandGroupTypeDef* CommandGroupArr[] (communication.cpp)

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
5.) Implement yourFunction() in Commands.cpp

# Useful commands
      - clear –> clears output terminal
      - back  –> jumps out of sellected command group
      - help  –> print out all available commands [in progress]
