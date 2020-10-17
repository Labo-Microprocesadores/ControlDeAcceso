/***************************************************************************/ /**
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
#include "../../database/data_base.h"
#include "../../../queue.h"

/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static uint8_t pin[PIN_ARRAY_SIZE] = {[0 ... (PIN_ARRAY_SIZE - 1)] = NO_INPUT_CHAR};
static uint8_t currentPos = 0;



/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
//!OJO EN TODAS ESTADS HABRIA QUE RESETEAR EL TIMER DE TIMEOUT Y EN ALGUNAS ACTUALIZAR EL DISPLAY
//TODO AGREGAR ESO

void pin_confirmPin(void)
{
    if (!verifyPIN(pin))
    {
        emitEvent(PIN_FAIL_EV);
    }else if(IsAdmin())
    {
        emitEvent(ADMIN_PIN_OK_EV);
    }else
    {
        emitEvent(USR_PIN_OK_EV);
    }
}

void pin_timerTimeout(void)
{
    inputTimerTimeout(pin, &currentPos, PIN_ARRAY_SIZE);
    //TODO mostrar timeout en display???
}

void pin_acceptNumber(void)
{
    inputAcceptNumber(pin, &currentPos, PIN_ARRAY_SIZE);
}

void pin_increaseCurrent(void)
{
    inputIncreaseCurrent(pin, currentPos);
}

void pin_decreaseCurrent(void)
{
    inputDecreaseCurrent(pin, currentPos);
}

uint8_t *pin_getPinArray(int *sizeOfReturningArray)
{
    int currentArrayLength = getEffectiveArrayLength(pin, PIN_ARRAY_SIZE);
    *sizeOfReturningArray = currentArrayLength;
    return pin;
}

