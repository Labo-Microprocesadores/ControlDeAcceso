/***************************************************************************/ /**
  @file     id_state.c
  @brief    ID state functions
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdbool.h>
#include "Timer.h"
#include "id_state.h"
#include "user_input.h"
#include "lector.h"
#include "seven_seg_display.h"
#include "data_base.h"
#include "queue.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define TITLE_TIME  2000

/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static uint8_t id[ID_ARRAY_SIZE];
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
static void id_fail(void);
/**
 * @brief Function executed when the lector fails to read the card.
 */
static void id_cardFail(void);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
//!OJO EN TODAS ESTA HABRIA QUE RESETEAR EL TIMER DE TIMEOUT Y EN ALGUNAS ACTUALIZAR EL DISPLAY
//TODO AGREGAR ESO

void initLogin(void)
{
    showingErrorIndication = false;
    inputResetArray(id, &currentPos, ID_ARRAY_SIZE);

    showTitle();
}

void id_increaseCurrent(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopErrorIndicationAndRestart();  
    else
        inputIncreaseCurrent(id, currentPos);
}

void id_decreaseCurrent(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopErrorIndicationAndRestart();  
    else
        inputDecreaseCurrent(id, currentPos);
}

void id_confirmID(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopErrorIndicationAndRestart();    
    else
    {
        if (!verifyID(id))
            id_fail();
        else
            emitEvent(ID_OK_EV);
    }
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

uint8_t * id_getIdArray(int *sizeOfReturningArray)
{
    int currentArrayLength = getEffectiveArrayLength(id, ID_ARRAY_SIZE);
    *sizeOfReturningArray = currentArrayLength;
    return id;
}

void id_checkCardID(void)
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
            emitEvent(ID_OK_EV);
        }
        else
        {
            id_fail();
        }
    }
    else
    {
        id_cardFail();
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
    SevenSegDisplay_WriteBuffer("ID  ", 4, 0);
    showingTitle = true;
    titleTimerID = Timer_AddCallback(&stopShowingTitle, TITLE_TIME, true);
}

static void stopShowingTitle(void)
{
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_SetPos(0);
    SevenSegDisplay_WriteBuffer("00000000", 8, 0); //TODO que inicialmente te muestre lineas y despues si giran el encoder empiece apareciendo el cero.
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
    Timer_Delete(errorIndicationTimerID);
    showingErrorIndication = false;
    errorIndicationTimerID = -1;
}

static void id_fail(void)
{
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_CursorOff();
}

static void id_cardFail(void)
{
    SevenSegDisplay_EraseScreen(); //TODO chequear
    SevenSegDisplay_CursorOff();
}
