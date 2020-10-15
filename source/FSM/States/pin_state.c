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
#include "user_input.h"


/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static uint8_t pin[PIN_ARRAY_SIZE] = {[ 0 ... (PIN_ARRAY_SIZE-1) ] = DEFAULT_PIN_CHAR_VALUE};
static uint8_t currentPos = 0;


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
/**
 * @brief Checks if the "pin" array format matches the format of a pin. The array must be complete (length equal to PIN_ARRAY_SIZE) and all elements must be numbers from 0 to 9.
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
    userDecreaseCurrent(pin, currentPos);
}

void confirmID(void)
{
    if (!checkArrayFormat())
    {
        //TODO Return ID_FAIL
    }

    //TODO faltan muchas cosas
    //si el id es conocido, emito un evento de id_ok (tengo database)
    //si el id no es conocido entonces emito evento de ID_FAIL
}

void timerTimeout(void)
{
    inputTimerTimeout(pin, &currentPos, PIN_ARRAY_SIZE);
    //mostrar timeout en display???
}

void acceptNumber(void)
{
    inputAcceptNumber(pin, &currentPos, PIN_ARRAY_SIZE);
}

uint8_t * getPinArray(int * sizeOfReturningArray)
{
    int currentArrayLength = getEffectiveArrayLength(pin, PIN_ARRAY_SIZE);
    *sizeOfReturningArray = currentArrayLength;
    return pin;
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static bool checkArrayFormat(void)
{
    int currentArrayLength = getEffectiveArrayLength(pin, PIN_ARRAY_SIZE);

    if (currentArrayLength!=PIN_ARRAY_SIZE &&  currentArrayLength!=PIN_ARRAY_SIZE-1)   //4 or 5 chars
        return false;

    return true;
}
