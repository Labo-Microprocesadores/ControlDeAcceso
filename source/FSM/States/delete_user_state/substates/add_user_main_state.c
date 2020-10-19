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

/*******************************************************************************
 * FUNCTIONS WITH GLOBAL SCOPE
 ******************************************************************************/
void addUsr_initState(void)
{
    uint8_t i;
    for (i = 0; i< MAX_CARD_NUMBER_LEN; i++)
    {
        cardNumber[i] = -1;
    }
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_CursorOff();
    SevenSegDisplay_SetPos(0);
    SevenSegDisplay_WriteBufferAndMove("SWIPE CARD", 10, 0, BOUNCE);
    
}


void addUsr_cardSwipe(void)
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
            emitEvent(ID_FAIL_EV);
            for (i = 0; i< MAX_CARD_NUMBER_LEN; i++)
                cardNumber[i] = -1;
        }
    }
    else
    {
        emitEvent(CARD_FAIL_EV);
    }
}

int8_t * addUsr_getCardNumber(void)
{
    return cardNumber;
}