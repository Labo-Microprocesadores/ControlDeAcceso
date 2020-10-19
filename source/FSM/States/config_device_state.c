/***************************************************************************/ /**
  @file     config_device.c
  @brief    config device state functions
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdbool.h>
#include "config_device_state.h"
#include "queue.h"
#include "seven_seg_display.h"
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
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
/**
 * @brief Shows the current option of the welcome in the display.
 */
static void showCurrentOption(void);
/*******************************************************************************
 * FUNCTIONS WITH GLOBAL SCOPE
 ******************************************************************************/
void initConfigDevice(void)
{
    currentOptionIndex = 0;
    
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_SetPos(0);
    SevenSegDisplay_ChangeCharacter(0 ,8);
    SevenSegDisplay_ChangeCharacter(1,8);
    SevenSegDisplay_ChangeCharacter(2,8);
    SevenSegDisplay_ChangeCharacter(3,8);
    
    showCurrentOption();
}

void configDev_nextOption(void)
{
   
        if (currentOptionIndex == OPTIONS_ARRAY_SIZE - 1)
            currentOptionIndex = 0;
        else
            currentOptionIndex++;
        showCurrentOption();
    
}

void configDev_previousOption(void)
{
    if (currentOptionIndex == 0)
        currentOptionIndex = OPTIONS_ARRAY_SIZE - 1;
    else
        currentOptionIndex--;
    showCurrentOption();
}

void configDev_selectOption(void)
{
    SevenSegDisplay_EraseScreen();
    emitEvent(CONFIG_DEVICE_FINISHED_EV);
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void showCurrentOption(void)
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
            SevenSegDisplay_SetBright(MIN);
            break;
    }
}
