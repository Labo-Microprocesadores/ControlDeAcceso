/***************************************************************************/ /**
  @file     add_user.c
  @brief    add user state functions
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "add_user_state.h"
#include <stdbool.h>
#include "data_base.h"
#include "queue.h"
#include "../user_input.h"
/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static STATE *currentState;
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 **********************************************************************/

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void addUser_initFSM(void)
{
    currentState = FSM_GetInitState();
}

void addUser_finishConfiguration(void)
{
    //emitEvent(ADD_USER_FINISHED_EV);
    
}

void addUser_onLKP(void)
{
    currentState = fsm(currentState, LKP_EV);
}
void addUser_onPress(void)
{
    currentState = fsm(currentState, PRESS_EV);
}
void addUser_onEncoderRight(void)
{
    currentState = fsm(currentState, ENCODER_RIGHT_EV);
}
void addUser_onEncoderLeft(void)
{
    currentState = fsm(currentState, ENCODER_LEFT_EV);
}





/*
void id_increaseCurrent(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopErrorIndicationAndRestart();  
    else
        inputIncreaseCurrent(id, currentPos);
}

void id_acceptNumber(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopErrorIndicationAndRestart();
    else
        inputAcceptNumber(id, &currentPos, ID_ARRAY_SIZE);
}

*/







/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/*******************************************************************************
 ******************************************************************************/
