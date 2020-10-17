/***************************************************************************/ /**
  @file     admin_state.c
  @brief    Admin state functions.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "admin_state.h"
#include "../../queue.h"
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

/*******************************************************************************
 * FUNCTIONS WITH GLOBAL SCOPE
 ******************************************************************************/

void nextOption(void)
{
    if (currentOptionIndex == OPTIONS_ARRAY_SIZE - 1)
        currentOptionIndex = 0;
    else
        currentOptionIndex++;
}

void previousOption(void)
{
    if (currentOptionIndex == 0)
        currentOptionIndex = OPTIONS_ARRAY_SIZE - 1;
    else
        currentOptionIndex--;
}

void selectOption(void)
{
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