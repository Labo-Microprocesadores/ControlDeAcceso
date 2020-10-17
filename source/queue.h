#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
//EVENTS
typedef enum
{
  NONE,
  LKP_EV,
  PRESS_EV,
  ENCODER_LEFT_EV,
  ENCODER_RIGHT_EV,
  CARD_SWIPE_EV,
  TIMER_EV,
  ID_OK_EV,
  ID_FAIL_EV,
  ADMIN_PIN_OK_EV,
  USR_PIN_OK_EV,
  PIN_FAIL_EV,
  NO_ATT_EV,
  HAS_ATT_EV,
  ADMIN_CONFIG_DEVICE_SELECTED_EV,
  ADMIN_CONFIG_DEVICE_FINISHED_EV,
  ADMIN_CONFIG_USER_SELECTED_EV,
  ADMIN_CONFIG_USER_FINISHED_EV,
  ADMIN_ADD_USER_SELECTED_EV,
  OPEN_SELECTED_EV,
  ADMIN_CONFIG_ME_SELECTED_EV,
  ADMIN_CONFIG_ME_FINISHED_EV
  USER_CONFIG_ME_SELECTED_EV,
  USER_CONFIG_ME_FINISHED_EV
  TIMER_ACCESS_EV
} EventType; //VER SI ESTO ES LO MEJOR, O SI ES MEJOR UNA ESTRUCTURA EVENTO MAS COMPLEJA, ADEMAS FALTA DIFERENCIAR LOS DISTINTOS EVENTOS DE TIMER

typedef struct EVENT
{
  EventType type;
  bool ack;
  struct EVENT *p2NextEv;
} event_t;

typedef struct
{
  event_t *queue;
  event_t *p2get;
  event_t *p2write;
} event_queue_t;

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define QUEUE_SIZE 100 //cambiar este define por la cantidad de posiciones deseadas en la cola, recomiendo entre 100 y 200 para este programa

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief Initialization of the Event Queue. Must call this function before emitting or getting events.
 */
void initQueue(void);

/**
 * @brief Addition of an event to the event queue.
 * @param EventType identifying the event.
 * @return bool indicating if an error has occured. 1: error. 0: no error.
 */
bool emitEvent(EventType type);

/**
 * @brief Returns the next event present in the event queue.
 * @return EventType identifying the next event in the queue.
 */
EventType getEvent(void);

/**
 * @brief Checks if the event queue is empty.
 * @return bool indicating whether the event queue is empty or not. false: empty. true: empty.
 */
bool queueIsEmpty(void);

#endif