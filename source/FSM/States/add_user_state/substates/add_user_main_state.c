/***************************************************************************/ /**
  @file     add_user_main_menu_state.c
  @brief    Main welcome state functions.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "add_user_main_state.h"
#include "lector.h"
#include "data_base.h"//:-)
#include "queue.h"
#include "seven_seg_display.h"

/*******************************************************************************
*       VARIABLE WITH LOCAL SCOPE
*******************************************************************************/
static int8_t cardNumber[MAX_CARD_NUMBER_LEN];
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
 * @brief Function executed when the card is already used.
 */
static void cardIsUsed(void);
/**
 * @brief Function executed when the lector fails to read the card.
 */
static void addCardFail(void);
/*******************************************************************************
 * FUNCTIONS WITH GLOBAL SCOPE
 ******************************************************************************/
void addUsr_initState(void)
{
    showingErrorIndication = false;
    showTitle();
    uint8_t i;
    for (i = 0; i< MAX_CARD_NUMBER_LEN; i++)
    {
        cardNumber[i] = -1;
    }  
}


void addUsr_cardSwipe(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopErrorIndicationAndRestart();    
    else
    {
        card_t myCard;
        bool ok = Lector_GetData(&myCard);
        if(ok)
        {
            uint8_t i,length = myCard.number_len;
            for(i = 0; i<length; i++)
            {
                cardNumber[i] = myCard.card_number[i];
            }
            
            if(!verifyCardNumber(cardNumber, length))
            {
                emitEvent(ID_OK_EV);
            }
            else
            {
                cardIsUsed();
                for (i = 0; i< MAX_CARD_NUMBER_LEN; i++)
                    cardNumber[i] = -1;
            }
        }
        else
        {
            addCardFail();
        }
    }
    
}

short * addUsr_getCardNumber(void)
{
    return cardNumber;
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
    SevenSegDisplay_WriteBufferAndMove("SWIPE CARD", 10, 0, BOUNCE);
    showingTitle = true;
    titleTimerID = Timer_AddCallback(&stopShowingTitle, TITLE_TIME, true);
}

static void stopShowingTitle(void)
{
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_SetPos(0);
    showingTitle = false;
}

static void userInteractionStopsTitle(void)
{
    Timer_Delete(titleTimerID);
    titleTimerID = -1;
    stopShowingTitle();
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


static void addCardFail(void)
{
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_CursorOff();
    SevenSegDisplay_SetPos(0);
    SevenSegDisplay_WriteBufferAndMove("CARD FAILED", 11, 0, SHIFT_L);
    showingErrorIndication = true;
    errorIndicationTimerID = Timer_AddCallback(&addUserId_initLogin, TITLE_TIME, true);
}

static void cardIsUsed(void)
{
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_CursorOff();
    SevenSegDisplay_SetPos(0);
    SevenSegDisplay_WriteBufferAndMove("CARD IS USED", 12, 0, SHIFT_L);
    showingErrorIndication = true;
    errorIndicationTimerID = Timer_AddCallback(&addUserId_initLogin, TITLE_TIME, true);
}

