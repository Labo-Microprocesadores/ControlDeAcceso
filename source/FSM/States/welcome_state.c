/***************************************************************************/ /**
  @file     main_menu_state.c
  @brief    Main menu state functions.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <States/welcome_state.h>
#include "lector.h"
#include "data_base.h"
#include "queue.h"
#include "seven_seg_display.h"
/*******************************************************************************
 * FUNCTIONS WITH GLOBAL SCOPE
 ******************************************************************************/
void showWelcomeAnimation(void)
{
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_CursorOff();
    SevenSegDisplay_SetPos(0);
    SevenSegDisplay_WriteBufferAndMove("HELLO", 5, 0, BOUNCE);
    //TODO: Show animation indicating "Welcome, swipe your id card or click the button to enter it manually" or similar.
}



void cardSwipe(void)
{
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
            emitEvent(ID_FAIL_EV);
        }
    }
    else
    {
        emitEvent(CARD_FAIL_EV);
    }
    //TODO: Show animation indicating "YOUR id is 1123123" or similar, recover id from card (no se si esta se hace aca pero bueno), and compare with database. Define wether this event switches to id state or pin state.
}
