/***************************************************************************/ /**
  @file     App.c
  @brief    Application functions
  @author   Grupo 2
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
  #include "queue.h"
  #include "fms.h"
  #include "data_base.h"
  #include "Led.h"
  #include "timer.h"
  #include "seven_seg_display.h"
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define TIMER_TIMEOUT 10000 //10 SEGS
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
/**
 * @brief function that fills the event queue with events from hardware.
 */
static void fillQueue(void);
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
  static STATE * currentState;
  static int userTimeOutTimerID;
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
  userTimeOutTimerID = Timer_AddCallback(&userTimeOutTimerID,TIMER_TIMEOUT, false);
}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run(void)
{
  while(true)
  {
    fillQueue();
    EventType event = getEvent();
    if (event != NONE)
    {
      currenteState = fms(currentState, event);
    }
  }
}

void fillQueue(void)
{
  
  if(Lector_Event())
  {
    Timer_Reset(userTimeOutTimerID);
    emitEvent(CARD_SWIPE_EV);
  }
  uint8_t move = Encoder_GetMove();
  if(move)
  {
    move == 1 ? emitEvent(ENCODER_RIGHT_EV) : emitEvent(ENCODER_LEFT_EV);
  }
  if(wasTap())//TODO poner el nuevo driver de button y ver si hacer uno generico o preguntar con el boton
  {
    emitEvent(PRESS_EV);
  }
  else if(wasLkp())
  {

/*******************************************************************************
 *******************************************************************************
