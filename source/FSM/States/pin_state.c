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
#include "Timer.h"
#include "pin_state.h"
#include "user_input.h"
#include "data_base.h"
#include "queue.h"
#include "seven_seg_display.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define TITLE_TIME  6000
/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static int8_t pin[PIN_ARRAY_SIZE];
static uint8_t currentPos = 0;
static bool showingTitle, showingErrorIndication, showingAnimation;
static int titleTimerID = -1;
static int errorIndicationTimerID = -1;
static int animationTimerID = -1;

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
 * @brief Function executed when the PIN is not correct. The main reason of creating another function for this is to avoid cancelling a callback (of the timer) inside of it (callback).
 */
static void userInteractionStopsTitle(void);

/**
 * @brief Function executed when the PIN is not correct.
 */
static void pinFail(void);

/**
 * @brief Stops showing the error indication of the state. 
 */
static void stopErrorIndication(void);

/**
 * @brief Stops showing the error indication in the display due to a user's interaction. The main reason of creating another function for this is to avoid cancelling a callback (of the timer) inside of it (callback).
 */
static void userInteractionStopsErrorIndication(void);

/**
 * @brief Shows an animation. 
 */
static void startFailAnimation();

/**
 * @brief Finishes the animation and sends an event to the queue. 
 */
static void finishFailAnimation(void);

/**
 * @brief Finishes the animation due to a user's interaction. The main reason of creating another function for this is to avoid cancelling a callback (of the timer) inside of it (callback).
 */
static void userInteractionFinishesFailAnimation(void);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
//!OJO EN TODAS ESTADS HABRIA QUE RESETEAR EL TIMER DE TIMEOUT Y EN ALGUNAS ACTUALIZAR EL DISPLAY
//TODO AGREGAR ESO

void initPinInput(void)
{
    showingAnimation = false;
    showingErrorIndication = false;
	inputResetArray(pin, &currentPos, PIN_ARRAY_SIZE);
    showTitle();
}

void pin_confirmPin(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if(showingErrorIndication)
        userInteractionStopsErrorIndication();
    else if (showingAnimation)
        userInteractionFinishesFailAnimation();
    else
    {
        if (!verifyPIN(pin))
        {
            pinFail();
            //emitEvent(FAIL_PIN_EV);
        }
        else
        {
            emitEvent(PIN_OK_EV);
        }
    }    
}

void pin_acceptNumber(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if(showingErrorIndication)
        userInteractionStopsErrorIndication();
    else if (showingAnimation)
        userInteractionFinishesFailAnimation();
    else
    {
        int8_t aux[] = {MID_LINE};
        inputAcceptNumber(pin, &currentPos, PIN_ARRAY_SIZE);
        SevenSegDisplay_WriteBuffer(aux, 1, currentPos-1);
    }
        
}

void pin_increaseCurrent(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if(showingErrorIndication)
        userInteractionStopsErrorIndication();
    else if (showingAnimation)
        userInteractionFinishesFailAnimation();
    else
        inputIncreaseCurrent(pin, currentPos);
}

void pin_decreaseCurrent(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if(showingErrorIndication)
        userInteractionStopsErrorIndication();
    else if (showingAnimation)
        userInteractionFinishesFailAnimation();
    else
        inputDecreaseCurrent(pin, currentPos);
}

int8_t *pin_getPinArray(int *sizeOfReturningArray)
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
    SevenSegDisplay_SetPos(0);
    SevenSegDisplay_CursorOff();
    showingTitle = true;
    titleTimerID = Timer_AddCallback(&stopShowingTitle, TITLE_TIME, true);
}

static void stopShowingTitle(void)
{
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_WriteBuffer(pin, PIN_ARRAY_SIZE, 0);
    SevenSegDisplay_CursorOn();
    showingTitle = false;
}

static void userInteractionStopsTitle(void)
{
    Timer_Delete(titleTimerID);
    titleTimerID = -1;
    stopShowingTitle();
}

static void pinFail(void)
{
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_SetPos(0);
    SevenSegDisplay_CursorOff();
    if (isCurrentUserBlocked())
    {
        SevenSegDisplay_WriteBufferAndMove("BLOCKED USER.", 13, 0, SHIFT_L);
    }
    else
    {
        SevenSegDisplay_WriteBufferAndMove("TRY AGAIN.", 9, 0, SHIFT_L);
    }
   // errorIndicationTimerID = Timer_AddCallback(&finishFail, TITLE_TIME, true);
    errorIndicationTimerID = Timer_AddCallback(&stopErrorIndication, TITLE_TIME, true);
}


static void stopErrorIndication(void)
{
    showingErrorIndication = false;
	SevenSegDisplay_EraseScreen();
	SevenSegDisplay_SetPos(0);
	startFailAnimation();
}

static void userInteractionStopsErrorIndication(void)
{
    Timer_Delete(errorIndicationTimerID);
    errorIndicationTimerID = -1;
    stopErrorIndication();
}

static void startFailAnimation(void)
{
    SevenSegDisplay_AnimationCircles();
	animationTimerID = Timer_AddCallback(&finishFailAnimation, 600, true);
}

static void finishFailAnimation(void)
{
    showingAnimation = false;
    SevenSegDisplay_StopAnimation();
    if (isCurrentUserBlocked())
        emitEvent(USR_BLOCKED_EV);
    else
        initPinInput();
}


static void userInteractionFinishesFailAnimation(void)
{
    Timer_Delete(animationTimerID);
    animationTimerID = -1;
    finishFailAnimation();
}


