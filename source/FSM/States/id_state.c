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

/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static uint8_t id[ID_ARRAY_SIZE] = {[0 ... (ID_ARRAY_SIZE - 1)] = NO_INPUT_CHAR};
static uint8_t currentPos = 0;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
/**
 * @brief Checks if the "id" array format matches the format of an id. The array must be complete (length equal to ID_ARRAY_SIZE) and all elements must be numbers from 0 to 9.
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
    if (!checkArrayFormat())
    {
        //TODO Return ID_FAIL
    }

    //TODO faltan muchas cosas
    //si el id es conocido, emito un evento de id_ok (tengo database)
    //si el id no es conocido entonces emito evento de ID_FAIL
}

void id_timerTimeout(void)
{
    inputTimerTimeout(id, &currentPos, ID_ARRAY_SIZE);
}

void id_acceptNumber(void)
{
    inputAcceptNumber(id, &currentPos, ID_ARRAY_SIZE);
}

uint8_t *id_getIdArray(int *sizeOfReturningArray)
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
    
}
/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static bool checkArrayFormat(void)
{
    int currentArrayLength = getEffectiveArrayLength(id, ID_ARRAY_SIZE);

    if (currentArrayLength != ID_ARRAY_SIZE)
        return false;

    return true;
}

/*******************************************************************************
 ******************************************************************************/
