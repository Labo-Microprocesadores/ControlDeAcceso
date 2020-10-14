/***************************************************************************//**
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



/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static uint8_t id[ID_ARRAY_SIZE] = {[ 0 ... (ID_ARRAY_SIZE-1) ] = DEFAULT_ID_CHAR_VALUE};
static uint8_t currentPos = 0;



/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
/**
 * @brief Function executed when a BACKSPACE is selected by the user. It deletes the current position of the id array (sets it to DEFAULT_ID_CHAR_VALUE) and sets the previouss one to DEFAULT_ID_CHAR_VALUE.
 */
static void deleteLastChar(void);
/**
 * @brief Calculates the number of characters introduced by the user in the id array.
 * @return The amount of elements different from DEFAULT_ID_CHAR_VALUE and BACKSPACE in the "id" array (its effective length).
 */
static int getEffectiveIDArrayLength(void);

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
    if(id[currentPos] == BACKSPACE)
        id[currentPos] = 0;
    else if(id[currentPos]==DEFAULT_ID_CHAR_VALUE)
        id[currentPos] = 0;
    else if(id[currentPos] < 9)
        id[currentPos]++; 
    else 
        id[currentPos] = BACKSPACE;
}

void decreaseCurrent(void)
{
    if(id[currentPos] > 0)
        id[currentPos]--;
    else if(id[currentPos] == 0 || id[currentPos]==DEFAULT_ID_CHAR_VALUE)
        id[currentPos] = BACKSPACE;
    else if(id[currentPos] == BACKSPACE)
        id[currentPos] = 9;
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
    int i;
    for( i=0 ; i < ID_ARRAY_SIZE ; i++ )
    {
        id[i] = DEFAULT_ID_CHAR_VALUE;
    }

    currentPos = 0;
    //mostrar timeout en display???
}

void acceptNumber(void)
{
    if (currentPos == ID_ARRAY_SIZE - 1)
        return;

    if ( id[currentPos] >= 0 && id[currentPos] < 9 )
    {
            currentPos++;        
    }
    else if( id[currentPos] == BACKSPACE)
    {
        deleteLastChar();
        currentPos--;
    }       
    id[currentPos] = DEFAULT_ID_CHAR_VALUE;
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static void deleteLastChar(void)
{
    int currentArrayLength = getEffectiveIDArrayLength();
    if (currentArrayLength == 0)
    {
        //!VOLVER AL MENU ANTERIOR
    }else
    {
        id[currentArrayLength - 1] = DEFAULT_ID_CHAR_VALUE;
    }
}

static int getEffectiveIDArrayLength(void)
{
    int length = 0;
    bool foundLast = false;
    while(!foundLast && length < ID_ARRAY_SIZE)
    {
        uint8_t lastChar = id[length];
        if (lastChar == DEFAULT_ID_CHAR_VALUE || lastChar == BACKSPACE)
            foundLast = true;
        else
            length ++;
    }
    return length;
}

static bool checkArrayFormat(void)
{
    int currentArrayLength = getEffectiveIDArrayLength();

    if (currentArrayLength!=ID_ARRAY_SIZE)
        return false;

    return true;
}

/*******************************************************************************
 ******************************************************************************/

