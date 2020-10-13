/***************************************************************************//**
  @file     id.c
  @brief    id state
  @author   Grupo 2
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdbool.h>
#include "Timer.h"
#include "id.h"



/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static uint8_t id[ID_ARRAY_SIZE] = {[ 0 ... (ID_ARRAY_SIZE-1) ] = DEFAULT_ID_CHAR_VALUE};
static uint8_t currentPos = 0;



/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static void deleteLastChar(void);
static int getEffectiveIDArrayLength(void);
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
    else if(id[currentPos] <= 8)
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
    for( i=0 ; i < sizeof(id)/sizeof(id[0]) ; i++ )
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
    id[currentPos] = 0;
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
        if (id[length] != DEFAULT_ID_CHAR_VALUE)
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
    
    //Checks if the last position is equal to BACKSPACE. Can only happen if confirmID() is called before acceptNumber()
    //Previous positions cannot be equal to BACKSPACE because deleteLastChar() is called in acceptNumber().
    if (id[ID_ARRAY_SIZE-1] == BACKSPACE)   
        return false;

    return true;
}

/*******************************************************************************
 ******************************************************************************/

