/***************************************************************************/ /**
  @file     pin_state.c
  @brief    Pin state functions
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
#include "pin_state.h"
#include "user_input.h"
#include "data_base.h"
#include "queue.h"
#include "seven_seg_display.h"

/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static uint8_t pin[PIN_ARRAY_SIZE];
static uint8_t currentPos = 0;
static bool showingTitle;
static bool showingErrorIndication;
static int titleTimerID = -1;

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


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
//!OJO EN TODAS ESTADS HABRIA QUE RESETEAR EL TIMER DE TIMEOUT Y EN ALGUNAS ACTUALIZAR EL DISPLAY
//TODO AGREGAR ESO

void initPinInput(void)
{
    showingErrorIndication = false;
    inputResetArray(pin, &currentPos, PIN_ARRAY_SIZE);
    showTitle();
}

void pin_confirmPin(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopErrorIndicationAndRestart();  
    else
    {
        if (!verifyPIN(pin))
        {
            emitEvent(FAIL_PIN_EV);
        }
        else if (IsAdmin())
        {
            emitEvent(ADMIN_PIN_OK_EV);
        }
        else
        {
            emitEvent(USR_PIN_OK_EV);
        }
    }
    
}

void pin_acceptNumber(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopErrorIndicationAndRestart();  
    else
        inputAcceptNumber(pin, &currentPos, PIN_ARRAY_SIZE);
}

void pin_increaseCurrent(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopErrorIndicationAndRestart();  
    else
        inputIncreaseCurrent(pin, currentPos);
}

void pin_decreaseCurrent(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopErrorIndicationAndRestart();  
    else
        inputDecreaseCurrent(pin, currentPos);
}

uint8_t *pin_getPinArray(int *sizeOfReturningArray)
{
    int currentArrayLength = getEffectiveArrayLength(pin, PIN_ARRAY_SIZE);
    *sizeOfReturningArray = currentArrayLength;
    return pin;
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static void showTitle(void)
{
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_WriteBuffer("PIN ", 4, 0);
    showingTitle = true;
    titleTimerID = Timer_AddCallback(&stopShowingTitle, TITLE_TIME, true);
}

static void stopShowingTitle(void)
{
    SevenSegDisplay_EraseScreen();
    showingTitle = false;
    //TODO: SHOW INPUT
}

static void userInteractionStopsTitle(void)
{
    Timer_Delete(titleTimerID);
    titleTimerID = -1;
    stopShowingTitle();
}