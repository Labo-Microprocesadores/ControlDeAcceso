/***************************************************************************/ /**
  @file     main_menu_state.c
  @brief    Main menu state functions.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "main_menu_state.h"

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
    //TODO: Show animation indicating "YOUR id is 1123123" or similar,recover id from card (no se si esta se hace aca pero bueno), and compare with database. Define wether this event switches to id state or pin state.
}