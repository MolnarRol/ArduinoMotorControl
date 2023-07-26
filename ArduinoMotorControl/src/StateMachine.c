#include "../inc/StateMachine.h"

void (*volatile p_prevState)(void) = 0;         // NULL
void (*volatile p_currentState)(void) = StateIDLE;

void StateHANLDER( void(*volatile p_newState)(void) )
{
    if( p_newState != 0 )
    {
        
        p_currentState = p_newState;
        p_newState();
    }
    else
    {
        p_prevState = p_currentState;
        p_currentState();
    }
}

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