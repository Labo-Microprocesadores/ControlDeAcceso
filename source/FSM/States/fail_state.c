/***************************************************************************/ /**
  @file     fail_state.c
  @brief    fail state functions
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdbool.h>
#include "timer.h"
#include "id_state.h"
#include "queue.h"
#include "data_base.h"

/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static int errorIndicationTimerID;
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define TITLE_TIME  2000

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 **********************************************************************

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void initFailState(void)
{
    errorIndicationTimerID = -1;
    SevenSegDisplay_EraseScreen();
    if (isUserBlocked())
    {
        SevenSegDisplay_WriteBufferAndMove("BLOCKED USER.", 13, 0, SHIFT_R);
    }
    else
    {
        SevenSegDisplay_WriteBufferAndMove("TRY AGAIN.", 9, 0, SHIFT_R);
    }
    errorIndicationTimerID = Timer_AddCallback(&finishFail, TITLE_TIME, true);
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static void finishFail(void)
{
    Timer_Delete(errorIndicationTimerID);
    if (isUserBlocked())
        emitEvent(USR_BLOCKED_EV);
    else
        emitEvent(RETRY_PIN_EV);
}
/*******************************************************************************
 ******************************************************************************/
