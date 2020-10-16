/***************************************************************************/ /**
  @file     admin_state.c
  @brief    Admin state functions.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "admin_state.h"

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
    //{"OPEN", "CnFG DEVICE", "ADD USER", "CnFG USER", "CnFG ME"};
    switch (currentOptionIndex) //TODO: Add events to the queue.
    {
    case OPEN:
        break;
    case CONFIG_DEVICE:
        break;
    case ADD_USER:
        break;
    case CONFIG_USER:
        break;
    case CONFIG_ME:
        break;
    }
}