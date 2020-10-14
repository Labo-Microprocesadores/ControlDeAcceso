/***************************************************************************//**
  @file     pin_state.c
  @brief    Pin state functions
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdbool.h>
#include "timer.h"
#include "pin_state.h"



/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static uint8_t pin[PIN_ARRAY_SIZE] = {[ 0 ... (PIN_ARRAY_SIZE-1) ] = DEFAULT_PIN_CHAR_VALUE};
static uint8_t currentPos = 0;



/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
/**
 * @brief Function executed when a BACKSPACE is selected by the user. It deletes the current position of the pin array (sets it to DEFAULT_PIN_CHAR_VALUE) and sets the previouss one to DEFAULT_PIN_CHAR_VALUE.
 */
static void deleteLastChar(void);
/**
 * @brief Calculates the number of characters introduced by the user in the pin array.
 * @return The amount of elements different from DEFAULT_PIN_CHAR_VALUE and BACKSPACE in the "pin" array (its effective length).
 */
static int getEffectivePinArrayLength(void);

/**
 * @brief Checks if the "pin" array format matches the format of an pin. The array must be complete (length equal to PIN_ARRAY_SIZE) and all elements must be numbers from 0 to 9.
 * @return A bool indicating if the format is valid or not.
 */
static bool checkArrayFormat(void);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
//!OJO EN TODAS ESTA HABRIA QUE RESETEAR EL TIMER DE TIMEOUT Y EN ALGUNAS ACTUALIZAR EL DISPLAY
//TODO AGREGAR ESO

void increaseCurrent(void)
{
    if(pin[currentPos] == BACKSPACE)
        pin[currentPos] = 0;
    else if(pin[currentPos]==DEFAULT_PIN_CHAR_VALUE)
        pin[currentPos] = 0;
    else if(pin[currentPos] < 9)
        pin[currentPos]++; 
    else 
        pin[currentPos] = BACKSPACE;
}

void decreaseCurrent(void)
{
    if(pin[currentPos] > 0)
        pin[currentPos]--;
    else if(pin[currentPos] == 0 || pin[currentPos]==DEFAULT_PIN_CHAR_VALUE)
        pin[currentPos] = BACKSPACE;
    else if(pin[currentPos] == BACKSPACE)
        pin[currentPos] = 9;
}


void confirmPin(void)
{
    if (!checkArrayFormat())
    {
        //TODO Return PIN_FAIL
    }

    //TODO faltan muchas cosas
    //si el pin es conocido, emito un evento de pin_ok (tengo database)
    //si el pin no es conocido entonces emito evento de PIN_FAIL
}

void timerTimeout(void)
{
    int i;
    for( i=0 ; i < PIN_ARRAY_SIZE ; i++ )
    {
        pin[i] = DEFAULT_PIN_CHAR_VALUE;
    }

    currentPos = 0;
    //mostrar timeout en display???
}

void acceptNumber(void)
{
    if (currentPos == PIN_ARRAY_SIZE - 1)
        return;

    if ( pin[currentPos] >= 0 && pin[currentPos] < 9 )
    {
            currentPos++;        
    }
    else if( pin[currentPos] == BACKSPACE)
    {
        deleteLastChar();
        currentPos--;
    }       
    pin[currentPos] = DEFAULT_PIN_CHAR_VALUE;
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static void deleteLastChar(void)
{
    int currentArrayLength = getEffectivePinArrayLength();
    if (currentArrayLength == 0)
    {
        //!VOLVER AL MENU ANTERIOR
    }else
    {
        pin[currentArrayLength - 1] = DEFAULT_PIN_CHAR_VALUE;
    }
}

static int getEffectivePinArrayLength(void)
{
    int length = 0;
    bool foundLast = false;
    while(!foundLast && length < PIN_ARRAY_SIZE)
    {
        uint8_t lastChar = pin[length];
        if (lastChar == DEFAULT_PIN_CHAR_VALUE || lastChar == BACKSPACE)
            foundLast = true;
        else
            length ++;
    }
    return length;
}

static bool checkArrayFormat(void)
{
    int currentArrayLength = getEffectivePinArrayLength();

    if (currentArrayLength!=PIN_ARRAY_SIZE &&  currentArrayLength!=PIN_ARRAY_SIZE-1)   //4 or 5 chars
        return false;

    return true;
}

/*******************************************************************************
 ******************************************************************************/
