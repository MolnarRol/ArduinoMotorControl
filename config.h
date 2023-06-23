/*
  Software setup
*/
#define VERSION 1                     // Software version
#define PWM_ENABLED_ON_START 1        // Enable PWN at MCU startup
#define REGULATION_ENABLED_ON_START 0 // Enable regulation at MCU startup with RPM = SETPOINT_DEFAULT (macro)
/*
  PID parameters
*/
#define Kp 0.15f                      // Proportial gain
#define Ki 0.005f                     // Integral gain
#define Kd 1.0f                       // Derivative gain

/*
  Setpoint interval and default value
*/
#define SETPOINT_DEFAULT 2800.0f      // Default regulation setpoint [RPM]
#define RPM_MIN 300.0f                // changeSetPoint() –> min and max values [rpm]           
#define RPM_MAX 5500.0f

/*
  TimerConfig.h Timing config veriables
*/
#define ENC_N_PULSES 100              // Rotary encoder steps per rotation
#define FIR_TIME 1.0f                 // Filtration time constant
#define TIM_STEP_us 0.0625f           // period of timer 0 for pulse measurement -> 1e6 / ( crystal_clock * prescaling )
#define PULSES_MAX 40                 // maximum number of pulses that can be read

/*
  Communication.h setup variables
*/
#define COMMAND_MAX_CHAR 16           // Maximum number of characters in a single word
#define MAX_WORDS_IN_PROMPT 2         // Maximum number of words that can be processed

/*
  UART settings
*/
#define UART_BAUD 115200              // UART baud rate
#define UART_TERMINATOR_CHAR '\r'     // Carriage return. For new line - '\n'