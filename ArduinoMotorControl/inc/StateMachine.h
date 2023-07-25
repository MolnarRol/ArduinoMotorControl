#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

// #include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************
    Pointer to current state of the state machine.
****************************************************/

extern void (*volatile p_currentState)(void);
extern void (*volatile p_prevState)(void);

void StateHANLDER( void(*volatile p_newState)(void) );
void StateIDLE      ( void );
void StateRUNNING   ( void );
void StateRegulation( void );
void StateBoostStart( void );

#ifdef __cplusplus
}
#endif
#endif