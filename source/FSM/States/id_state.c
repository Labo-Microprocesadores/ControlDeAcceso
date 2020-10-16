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

void increaseCurrent(void)
{
    inputIncreaseCurrent(id, currentPos);
}

void decreaseCurrent(void)
{
    userDecreaseCurrent(id, currentPos);
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
    inputTimerTimeout(id, &currentPos, ID_ARRAY_SIZE);
    //TODO mostrar timeout en display???
}

void acceptNumber(void)
{
    inputAcceptNumber(id, &currentPos, ID_ARRAY_SIZE);
}
uint8_t *getIdArray(int *sizeOfReturningArray)
{
    int currentArrayLength = getEffectiveArrayLength(id, ID_ARRAY_SIZE);
    *sizeOfReturningArray = currentArrayLength;
    return id;
}

void checkCardID(void)
{
    //TODO Checks if the read ID (from card) is correct and corresponds to a user or an admin in the database. Adds a ID_OK or a ID_FAIL event to the event queue of the FSM.
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
