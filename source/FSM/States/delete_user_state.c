/***************************************************************************/ /**
  @file     delete_user_state.c
  @brief    Delete user state functions
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdbool.h>
#include "Timer.h"
#include "delete_user_state.h"
#include "user_input.h"
#include "lector.h"
#include "seven_seg_display.h"
#include "data_base.h"
#include "queue.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define TITLE_TIME  6000

/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static int8_t id[ID_ARRAY_SIZE];
static uint8_t currentPos = 0;
static bool showingTitle, showingErrorIndication;
static int titleTimerID = -1;
static int errorIndicationTimerID = -1;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
/**
 * @brief Show the title of the state in the display. If the user interacts with the system, the title will stop showing and the input will start.
 */
static void showTitle(void);
/**
 * @brief Stops showing the title of the state in the display. The input starts.
 */
static void stopShowingTitle(void);

/**
 * @brief Stops showing the title of the state in the display due to a user's interaction. The input starts.
 */
static void userInteractionStopsTitle(void);

/**
 * @brief Stops showing the error indication in the display due to a user's interaction. The state 'restarts'.
 */
static void userInteractionStopErrorIndicationAndRestart(void);

/**
 * @brief Stops showing the error indication in the display due to a user's interaction. The state doesn't 'restart'.
 */
static void userInteractionStopErrorIndication(void);

/**
 * @brief Function executed when the ID is not correct.
 */
static void idFail(void);
/**
 * @brief Function executed when the lector fails to read the card.
 */
static void idCardFail(void);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
//!OJO EN TODAS ESTA HABRIA QUE RESETEAR EL TIMER DE TIMEOUT Y EN ALGUNAS ACTUALIZAR EL DISPLAY
//TODO AGREGAR ESO

void deleteUser_initState(void)
{
    showingErrorIndication = false;
    inputResetArray(id, &currentPos, ID_ARRAY_SIZE);
    showTitle();
}

void deleteUser_increaseCurrent(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopErrorIndicationAndRestart();  
    else
        inputIncreaseCurrent(id, currentPos);
}

void deleteUser_decreaseCurrent(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopErrorIndicationAndRestart();  
    else
        inputDecreaseCurrent(id, currentPos);
}

void deleteUser_confirm(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopErrorIndicationAndRestart();    
    else
    {
        if (removeUser(id) == DELETE_SUCCESSFULL)
            emitEvent(ID_OK_EV);
        else
            idFail();
            
    }
}


void deleteUser_acceptNumber(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopErrorIndicationAndRestart();
    else
        inputAcceptNumber(id, &currentPos, ID_ARRAY_SIZE);
}

int8_t * deleteUser_getIdArray(int *sizeOfReturningArray)
{
    int currentArrayLength = getEffectiveArrayLength(id, ID_ARRAY_SIZE);
    *sizeOfReturningArray = currentArrayLength;
    return id;
}

void deleteUser_checkCardID(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopErrorIndication();
    card_t myCard;
    bool ok = Lector_GetData(&myCard);
    if(ok)
    {
        // agarro numero de tarjeta
        uint8_t numero[19];
        uint8_t i,length = myCard.number_len;
        for(i = 0; i<length; i++)
        {
            numero[i] = myCard.card_number[i];
        }
        
        if(verifyCardNumber(numero, length))
        {
            removeUser(getIdByCardNumber(numero));//?esto esta bien? 
            ////emitEvent(ID_OK_EV);
        }
        else
        {
            idFail();
        }
    }
    else
    {
        idCardFail();
    }

    //TODO Checks if the read ID (from card) is correct and corresponds to a user or an admin in the database. Adds a ID_OK or a ID_FAIL event to the event queue of the FSM.
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static void showTitle(void)
{
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_SetPos(0);
    SevenSegDisplay_CursorOff();
    SevenSegDisplay_WriteBuffer("ENTER ID OR CARD", 16, 0);
    showingTitle = true;
    titleTimerID = Timer_AddCallback(&stopShowingTitle, TITLE_TIME, true);
}

static void stopShowingTitle(void)
{
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_SetPos(0);
    SevenSegDisplay_WriteBuffer(id, ID_ARRAY_SIZE, 0);
    SevenSegDisplay_CursorOn();
    showingTitle = false;
}

static void userInteractionStopsTitle(void)
{
    Timer_Delete(titleTimerID);
    titleTimerID = -1;
    stopShowingTitle();
    SevenSegDisplay_CursorOn();
}

static void userInteractionStopErrorIndicationAndRestart(void)
{
    userInteractionStopErrorIndication();
    initLogin();
}

static void userInteractionStopErrorIndication(void)
{
       SevenSegDisplay_EraseScreen();
    Timer_Delete(errorIndicationTimerID);
    showingErrorIndication = false;
    errorIndicationTimerID = -1;
}

static void idFail(void)
{
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_CursorOff();
    SevenSegDisplay_SetPos(0);
    SevenSegDisplay_WriteBufferAndMove("NO ID FOUND", 11, 0, BOUNCE);
    showingErrorIndication = true;
    errorIndicationTimerID = Timer_AddCallback(&deleteUser_initState, TITLE_TIME, true);
}

static void idCardFail(void)
{
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_CursorOff();
    SevenSegDisplay_SetPos(0);
    SevenSegDisplay_WriteBufferAndMove("CARD FAILED", 11, 0, BOUNCE);
    showingErrorIndication = true;
    errorIndicationTimerID = Timer_AddCallback(&deleteUser_initState, TITLE_TIME, true);
}
