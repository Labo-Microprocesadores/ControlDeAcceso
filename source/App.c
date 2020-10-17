/***************************************************************************/ /**
  @file     App.c
  @brief    Application functions
  @author   Grupo 2
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
  #include "queue.h"
  #include "FMS/fms.h"
  #include "database/data_base.h"
  #include "drivers/Led.h"
  #include "drivers/timer.h"
  #include "drivers/seven_seg_display.h"
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
  static STATE * currentState;
/*******************************************************************************
 *******************************************************************************
                        FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init(void)
{
  initializeDataBase();
  SevenSegDisplay_Init();
  Led_Init();
  Timer_Init();
  initQueue();
  currentState = FSM_GetInitState();
  
}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run(void)
{
  while(true)
  {
    EventType event = getEvent();
    if (event != NONE)
    {
      currenteState = fms(currentState, event);
    }
  }
/*******************************************************************************
 *******************************************************************************
