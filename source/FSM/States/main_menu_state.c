/***************************************************************************/ /**
  @file     main_menu_state.c
  @brief    Main menu state functions.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "main_menu_state.h"
#include "lector.h"
#include "database.h"
/*******************************************************************************
 * FUNCTIONS WITH GLOBAL SCOPE
 ******************************************************************************/
void showWelcomeAnimation(void)
{
    //TODO: Show animation indicating "Welcome, swipe your id card or click the button to enter it manually" or similar.
}

void initLogin(void)
{
    //TODO: Show animation indicating "Enter ID" or similar, all the neccesary initialization is done by default, switches to id state.
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
        for(i = 0; i<legth; i++)
        {
            numero[i] = myCard.card_number[i];
        }
        CreateValidNumberArrayFormat(numero, length);
        if(verifyCardNumber(numero, length))
        {
            //TODO emit event NOT RECOGNIZED CARD NUMBER
        }
    }
    else
    {
        // error
    }
    //TODO: Show animation indicating "YOUR id is 1123123" or similar,recover id from card (no se si esta se hace aca pero bueno), and compare with database. Define wether this event switches to id state or pin state.
}