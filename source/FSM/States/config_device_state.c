/***************************************************************************/ /**
  @file     config_device.c
  @brief    config device state functions
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "config_device_state.h"
#include <stdbool.h>
#include "../../queue.h"
#include "../../drivers/seven_seg_display.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define OPTIONS_ARRAY_SIZE 3
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef enum
{
    MAX_BRIGHT,
    MID_BRIGHT,
    LOW_BRIGHT,
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
    case MAX_BRIGHT:
        SevenSegDisplay_SetBright(MAX);
        break;
    case MID_BRIGHT:
        SevenSegDisplay_SetBright(MID);
        break;
    case LOW_BRIGHT:
        SevenSegDisplay_SetBright(LOW);
        break;
    }
    emitEvent(ADMIN_CONFIG_DEVICE_FINISHED_EV);
}
