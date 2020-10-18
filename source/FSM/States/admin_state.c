/***************************************************************************/ /**
  @file     admin_state.c
  @brief    Admin state functions.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "admin_state.h"
#include "queue.h"
#include "seven_seg_display.h"
#include "Timer.h"
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define OPTIONS_ARRAY_SIZE 5
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef enum
{
    OPEN,
    CONFIG_DEVICE,
    ADD_USER,
    CONFIG_USER,
    CONFIG_ME
} options_t;
/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static uint8_t currentOptionIndex = 0;
static bool showingTitle;
static int titleTimerID = -1;
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define TITLE_TIME  2000

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
 * @brief Shows the current option of the menu in the display.
 */
static void showCurrentOption(void);
/*******************************************************************************
 * FUNCTIONS WITH GLOBAL SCOPE
 ******************************************************************************/

void admin_initAdminMenu(void)
{
    showingTitle = false;
    showTitle();
    currentOptionIndex = 0;
}

void admin_nextOption(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else
    {
        if (currentOptionIndex == OPTIONS_ARRAY_SIZE - 1)
            currentOptionIndex = 0;
        else
            currentOptionIndex++;
        showCurrentOption();
    }
    
}

void admin_previousOption(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else
    {
        if (currentOptionIndex == 0)
            currentOptionIndex = OPTIONS_ARRAY_SIZE - 1;
        else
            currentOptionIndex--;
        showCurrentOption();
    } 
}

void admin_selectOption(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else
    {
        SevenSegDisplay_EraseScreen();
        switch (currentOptionIndex)
        {
            case OPEN:
                emitEvent(OPEN_SELECTED_EV);
                break;
            case CONFIG_DEVICE:
                emitEvent(ADMIN_CONFIG_DEVICE_SELECTED_EV);
                break;
            case ADD_USER:
                emitEvent(ADMIN_ADD_USER_SELECTED_EV);
                break;
            case CONFIG_USER:
                emitEvent(ADMIN_CONFIG_USER_SELECTED_EV);
                break;
            case CONFIG_ME:
                emitEvent(ADMIN_CONFIG_ME_SELECTED_EV);
                break;
        }
    }
    
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static void showTitle(void)
{
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_WriteBufferAndMove("ADMIN MENU", 10, 0, SHIFT_R);
    showingTitle = true;
    titleTimerID = Timer_AddCallback(&stopShowingTitle, TITLE_TIME, true);
}

static void stopShowingTitle(void)
{
    SevenSegDisplay_EraseScreen();
    showingTitle = false;
    showCurrentOption();
}

static void userInteractionStopsTitle(void)
{
    Timer_Delete(titleTimerID);
    titleTimerID = -1;
    stopShowingTitle();
}

static void showCurrentOption(void)
{
    SevenSegDisplay_EraseScreen();
    switch (currentOptionIndex)
    {
    case OPEN:
        SevenSegDisplay_WriteBuffer("OPEN", 4, 0);
        break;
    case CONFIG_DEVICE:
        SevenSegDisplay_WriteBufferAndMove("CONFIG DEVICE", 13, 0, SHIFT_R); 
        break;
    case ADD_USER:
        SevenSegDisplay_WriteBufferAndMove("ADD USER", 8, 0, SHIFT_R);
        break;
    case CONFIG_USER:
        SevenSegDisplay_WriteBufferAndMove("CONFIG USER", 11, 0, SHIFT_R);
        break;
    case CONFIG_ME:
        SevenSegDisplay_WriteBufferAndMove("CONFIG ME", 9, 0, SHIFT_R);
        break;
    }
}
