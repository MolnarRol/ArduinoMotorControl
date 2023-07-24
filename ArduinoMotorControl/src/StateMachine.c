#include "../inc/StateMachine.h"
void (*volatile p_currentState)(void) = StateIDLE;

void StateIDLE( void )
{

}

void StateRUNNING( void )
{

}

void StateRegulation( void )
{

    
};

void StateBoostStart( void )
{

    p_currentState = StateRegulation;
};