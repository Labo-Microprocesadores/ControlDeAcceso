/***************************************************************************/ /**
  @file     user_input.c
  @brief    Functions which manage the input of the user.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdbool.h>
#include "timer.h"
#include "user_input.h"
#include "seven_Seg_display.h"
#include "queue.h"

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
/**
 * @brief Function executed when a BACKSPACE is selected by the user. It deletes the current position of the input array (sets it to NO_INPUT_CHAR) and sets the previouss one to NO_INPUT_CHAR.
 * @param inputArray: Te array of characters introduced by the user.
 * @param totalArraySize: The previosly fixed size of the inputArray.
 */
static void deleteLastChar(uint8_t *inputArray, int totalArraySize);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
//!OJO EN TODAS ESTA HABRIA QUE RESETEAR EL TIMER DE TIMEOUT Y EN ALGUNAS ACTUALIZAR EL DISPLAY
//TODO AGREGAR ESO
void inputIncreaseCurrent(uint8_t *inputArray, uint8_t currentPosition)
{
    if (inputArray[currentPosition] == BACKSPACE)
        inputArray[currentPosition] = 0;
    else if (inputArray[currentPosition] == NO_INPUT_CHAR)
        inputArray[currentPosition] = 0;
    else if (inputArray[currentPosition] < 9)
        inputArray[currentPosition]++;
    else
        inputArray[currentPosition] = BACKSPACE;
    SevenSegDisplay_ChangeCharacter(currentPosition, inputArray[currentPosition]);
}

void inputDecreaseCurrent(uint8_t *inputArray, uint8_t currentPosition)
{
    if (inputArray[currentPosition] > 0)
        inputArray[currentPosition]--;
    else if (inputArray[currentPosition] == 0 || inputArray[currentPosition] == NO_INPUT_CHAR)
        inputArray[currentPosition] = BACKSPACE;
    else if (inputArray[currentPosition] == BACKSPACE)
        inputArray[currentPosition] = 9;
    SevenSegDisplay_ChangeCharacter(currentPosition, inputArray[currentPosition]);

}

void inputResetArray(uint8_t *inputArray, uint8_t *currentPosition, int totalArraySize)
{
    int i;
    for (i = 0; i < totalArraySize; i++)
    {
        inputArray[i] = NO_INPUT_CHAR;
    }
    *currentPosition = 0;
    SevenSegDisplay_EraseScreen();
}

void inputAcceptNumber(uint8_t *inputArray, uint8_t *currentPosition, int totalArraySize)
{
    if (*currentPosition == totalArraySize - 1)
        return;

    if (inputArray[*currentPosition] >= 0 && inputArray[*currentPosition] < 9)
    {
        SevenSegDisplay_CursorInc();
        *currentPosition++;
        inputArray[*currentPosition] = NO_INPUT_CHAR;
        SevenSegDisplay_WriteBuffer(&inputArray[*currentPosition], 1, *currentPosition);
    }
    else if (inputArray[*currentPosition] == BACKSPACE)
    {
        SevenSegDisplay_CursorDec();
        deleteLastChar(inputArray, totalArraySize);
        *currentPosition--;
    }
}

static int getEffectiveArrayLength(uint8_t *inputArray, int totalArraySize)
{
    int length = 0;
    bool foundLast = false;
    while (!foundLast && length < totalArraySize)
    {
        uint8_t lastChar = inputArray[length];
        if (lastChar == NO_INPUT_CHAR || lastChar == BACKSPACE)
            foundLast = true;
        else
            length++;
    }
    return length;
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static void deleteLastChar(uint8_t *inputArray, int totalArraySize)
{
    int currentArrayLength = getEffectiveArrayLength(inputArray, totalArraySize);
    if (currentArrayLength == 0)
    {
        SevenSegDisplay_EraseScreen(); 
        emitEvent(RETURN_TO_LAST_STATE_EV);
    }
    else
    {
        inputArray[currentArrayLength - 1] = NO_INPUT_CHAR;
        SevenSegDisplay_WriteBuffer(&inputArray[currentArrayLength - 1], 1, currentArrayLength - 1);
        
    }
}

/*******************************************************************************
 ******************************************************************************/
