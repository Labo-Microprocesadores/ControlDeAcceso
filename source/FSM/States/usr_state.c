/***************************************************************************/ /**
  @file     usr_state.c
  @brief    User state functions.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "usr_state.h"

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef enum {OPEN, CONFIG} options_t;

/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static options_t options;
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
    switch (currentOptionIndex) //TODO: Add events to the queue.
    {
    case OPEN:
        break;
    case CONFIG:
        break;
    }
}