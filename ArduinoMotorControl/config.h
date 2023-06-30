#ifndef _CONFIG_H_
#define _CONFIG_H_

/*
  Software setup
*/
#define VERSION 1.2                   // Software version  
#define REG_MOTOR_AUTOSTART 0         // Enable PWN and regulation at MCU startup

/*
  PID parameters
*/
#define Kp 0.15f                      // Proportial gain
#define Ki 0.005f                     // Integral gain
#define Kd 1.0f                       // Derivative gain
#define ARW_EN 1                      // Enable ARW

#define SETPOINT_DEFAULT 1440.0f      // Default regulation setpoint [RPM]
#define START_BOOST_EN 1              // Start motor with 100% until MOTOR_RPM_REG_START rpm is reached
#define MOTOR_RPM_REG_START 1600.0f   // Start regulation after reaching defined RPM by this macro

/*
  Setpoint interval -> for rpm <new rpm> command
*/
#define RPM_MIN 300.0f                // changeSetPoint() –> min and max values [rpm]           
#define RPM_MAX 5500.0f

/*
  Speeds definitions
*/
#define SPEEDS { 1440, 1596, 2100, 2800 }   // Speeds can be called by "s [index+1]"" => for 1440: s 1

/*
  TimerConfig.h Timing config veriables
*/
#define ENC_N_PULSES 100              // Rotary encoder steps per rotation
#define FIR_TIME 1.0f                 // Filtration time constant
#define TIM_STEP_us ( 1e6f / ( 16e6f * 1 )) // period of timer 0 for pulse measurement -> 1e6 / ( crystal_clock * prescaling )
#define PULSES_MAX 40                 // maximum number of pulses that can be read

/*
  Encoder pulse watchdog
*/
#define ENC_WDG_EN 1                  // Enable encover pulse watchdog functionality
#define ENC_WDG_MS 20                 // Wait for n [ms] for encoder impulse. If no pulse will be detected in this time –> motor stop

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

#endif