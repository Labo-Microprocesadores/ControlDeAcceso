/***************************************************************************/ /**
  @file     id_state.c
  @brief    ID state functions
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdbool.h>
#include "timer.h"
#include "id_state.h"
#include "user_input.h"
#include "seven_seg_display.h"
#include "../../database/data_base.h"
#include "../../queue.h"


/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static uint8_t id[ID_ARRAY_SIZE] = {[0 ... (ID_ARRAY_SIZE - 1)] = NO_INPUT_CHAR};
static uint8_t currentPos = 0;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
//!OJO EN TODAS ESTA HABRIA QUE RESETEAR EL TIMER DE TIMEOUT Y EN ALGUNAS ACTUALIZAR EL DISPLAY
//TODO AGREGAR ESO

void id_increaseCurrent(void)
{
    inputIncreaseCurrent(id, currentPos);
}

void id_decreaseCurrent(void)
{
    inputDecreaseCurrent(id, currentPos);
}

void id_confirmID(void)
{
    if (!verifyID(id))
        emitEvent(ID_FAIL_EV);
    else
        emitEvent(ID_OK_EV);
}

void id_timerTimeout(void)
{
    inputTimerTimeout(id, &currentPos, ID_ARRAY_SIZE);
}

void id_acceptNumber(void)
{
    inputAcceptNumber(id, &currentPos, ID_ARRAY_SIZE);
}

uint8_t * id_getIdArray(int *sizeOfReturningArray)
{
    int currentArrayLength = getEffectiveArrayLength(id, ID_ARRAY_SIZE);
    *sizeOfReturningArray = currentArrayLength;
    return id;
}

void id_checkCardID(void)
{
    //TODO Checks if the read ID (from card) is correct and corresponds to a user or an admin in the database. Adds a ID_OK or a ID_FAIL event to the event queue of the FSM.
}

void id_updateDispPin(void)
{
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_ChangeCharacter(0, P);
    SevenSegDisplay_ChangeCharacter(1, I);
    SevenSegDisplay_ChangeCharacter(2, N);
}

void id_fail(void)
{
    SevenSegDisplay_EraseScreen(); //TODO ver si imprimir alguna animacion de error.
    SevenSegDisplay_ChangeCharacter(0, I);
    SevenSegDisplay_ChangeCharacter(1, D);
    }

