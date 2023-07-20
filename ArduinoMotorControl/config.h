#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdint.h>

#define DEBUG

/**
  \defgroup config Configuration macros
  Configuration is done by modifying config.h file macros.
  Inside the config.h are defined all the relevant - project specific constants.
  @{
*/

/// Software version  
#define VERSION 1.2                

/**
  \defgroup outpins Output pin definitions
  Pin deffinitions
  @{
*/
/// Pin for guick debugging (D2)
#define   DEBUG_PIN   2           
/// Pin for direction setup (D5)    
#define   DIR_PIN     5          
/// Pin for brake activation (D7)     
#define   BRK_PIN     7               
/// @}

#define PWM_OUTPUT_HiZ 0

/**
  \defgroup pid_default PID default parameters
  \ingroup regulation
  Default parameters for PID struct.
  @{
*/

/// Proportial gain
#define KP 0.15f        
/// Integral gain              
#define KI 0.005f              
/// Derivative gain       
#define KD 1.0f              
/// Enable anti reset windup         
#define ARW_EN 1                      

/// Default regulation setpoint [RPM]
#define SETPOINT_DEFAULT 1440.0f      
/// Start motor with 100% until MOTOR_RPM_REG_START rpm is reached
#define START_BOOST_EN 1             
/// Start regulation after reaching defined RPM by this macro 
#define MOTOR_RPM_REG_START 1000.0f   
/** 
  Period of PID regulation output calculation
*/
#define REG_PERIOD_MS 2              

/*
  Setpoint interval -> for rpm <new rpm> command
*/

/// changeSetPoint() maximum value [rpm] 
#define RPM_MIN 300.0f                 
/// changeSetPoint() minimum value [rpm]          
#define RPM_MAX 6000.0f

/*
  Speeds definitions
*/
/// Speeds can be called by "s [index+1]"" => for 1440: s 1
#define SPEEDS { 1440, 1596, 2100, 2800 }   
/// @}

/**
  \defgroup timer_config Timing related macros
  TimerConfig.h Timing config macros
  @{
*/

/// Rotary encoder steps per rotation
#define ENC_N_PULSES 100    

/*
  Digital filtration for speed reading
*/

/**
 * Enable FIR filter in function getRPMfromPulses() in TimingUtils.cpp
*/
#define SPEED_FILTER_EN 1

/**
  Filtration time constant     
  Sets time constant for FIR filter filter_1stOrder_r32().
*/      
#define FIR_TIME 0.5f              



/// period of timer 0 for pulse measurement -> 1e6 / ( crystal_clock * prescaling )   
#define TIM_STEP_us ( 1e6f / ( 16e6f * 1 )) 
/// maximum number of pulses that can be read
#define PULSES_MAX 40    
/// number of us in one minute             
#define US_IN_MIN 60e6f              
/*
  Encoder pulse watchdog
*/
/**
  \defgroup enc_watchdog  Watchdog for missing encoder signal
  @{
*/

/// Enable encover pulse watchdog functionality
#define ENC_WDG_EN 0          
/** Wait for n [ms] for encoder impulse. If no pulse will be detected in this time –> motor stop        
  ISR( TIMER2_COMPA_vect )
*/
#define ENC_WDG_MS 20   

/// @}

/**
  \defgroup enc_pulse_detection Encoder pulse detection - edge sellection
  @{
*/
#define EDGE_RISING 0
#define EDGE_FALLING 1
#define EDGE_BOTH 2

/// Sellected edge detection mode
#define PULSE_DELTA_READ EDGE_RISING
/// @}
/// @}

/**
  \defgroup uart_settings UART/Communication settings
  Serial communication macro settings
  @{
*/
/// UART baud rate
#define UART_BAUD 115200       
/// Carriage return. For new line - '\n'       
#define UART_TERMINATOR_CHAR '\r'   

/// Maximum number of characters in a single word
#define COMMAND_MAX_CHAR 16        
/// Maximum number of words that can be processed   
#define MAX_WORDS_IN_PROMPT 2   
/// @}
/// @}
#endif