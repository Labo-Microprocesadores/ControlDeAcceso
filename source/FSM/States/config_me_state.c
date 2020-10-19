/***************************************************************************/ /**
  @file     config_me_state.c
  @brief    Config me state functions
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define TITLE_TIME  2000
/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdbool.h>
#include "timer.h"
#include "config_me_state.h"
#include "user_input.h"
#include "data_base.h"
#include "queue.h"
#include "seven_seg_display.h"


/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static int8_t newPin[PIN_ARRAY_SIZE];
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
 * @brief Function executed when the PIN format is not correct.
 */
static void pinFail(void);
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
//!OJO EN TODAS ESTADS HABRIA QUE RESETEAR EL TIMER DE TIMEOUT Y EN ALGUNAS ACTUALIZAR EL DISPLAY
//TODO AGREGAR ESO

void configMe_initState(void)
{
    showingErrorIndication = false;
	inputResetArray(newPin, &currentPos, PIN_ARRAY_SIZE);
    showTitle();
}

void configMe_confirmPin(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopErrorIndicationAndRestart();  
    else
    {
        if (changePin(newPin) == PIN_CHANGED_SUCCESFULLY)
             emitEvent(RETURN_TO_LAST_STATE_EV);
        else
            pinFail();
    }
    
}

void configMe_acceptNumber(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopErrorIndicationAndRestart();  
    else
        inputAcceptNumber(newPin, &currentPos, PIN_ARRAY_SIZE);
}

void configMe_increaseCurrent(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopErrorIndicationAndRestart();  
    else
        inputIncreaseCurrent(newPin, currentPos);
}

void configMe_decreaseCurrent(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopErrorIndicationAndRestart();  
    else
        inputDecreaseCurrent(newPin, currentPos);
}
/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static void showTitle(void)
{
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_WriteBufferAndMove("NEW PIN", 7, 0, BOUNCE);
    SevenSegDisplay_SetPos(0);
    SevenSegDisplay_CursorOff();
    showingTitle = true;
    titleTimerID = Timer_AddCallback(&stopShowingTitle, TITLE_TIME, true);
}

static void stopShowingTitle(void)
{
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_SetPos(0);
    SevenSegDisplay_WriteBuffer(newPin, PIN_ARRAY_SIZE, 0);
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


static void pinFail(void)
{
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_CursorOff();
    SevenSegDisplay_SetPos(0);
    SevenSegDisplay_WriteBufferAndMove("PIN ERROR", 16, 0, BOUNCE);
    showingErrorIndication = true;
    errorIndicationTimerID = Timer_AddCallback(&configMe_initState, TITLE_TIME, true);
}