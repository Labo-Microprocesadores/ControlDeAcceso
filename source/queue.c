/***************************************************************************/ /**
  @file     queue.c
  @brief    Event queue functions.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/
/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "queue.h"

/*******************************************************************************
 * PRIVATE VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
event_queue_t queue;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void initQueue(void)
{
  int i;

  event_t *tempaux = &queue;

  for (i = 0; i < QUEUE_SIZE; i++)
  {
    tempaux++->ack = true; //debo hacer esto para asegurarme de que todas las celdas de la cola esten habilitadas para ser escritas
  }

  queue.queue = &queue; //la cola de eventos
  queue.p2get = &queue; //los punteros para leer y escribir estan en el mismo lugar (cola vacia)
  queue.p2write = &queue;
}

bool emitEvent(EventType type)
{
  event_t *temp = queue.p2write;

  if (&queue == NULL)
  {
    return false; // verificacion si el usuario no lo hizo antes
  }

  if (queue.p2write->ack == false) // si en la cola de eventos no hay mas lugar -> error
  {
    return false;
  }

  queue.p2write->type = type; // guardo el ID del evento

  if ((queue.p2write) == ((queue.queue) + (QUEUE_SIZE - 1))) // movimiento del puntero de write
  {
    queue.p2write = queue.queue; // si estoy al final de la cola debo moverlo al principio
  }
  else
  {
    (queue.p2write)++; // sino avanza una posicion
  }
  temp->p2NextEv = (struct EVENT *)queue.p2write; // guardo en el evento anterior un puntero al evento actual para no tener que problems con el movimiento en get_event
  temp->ack = false;                              // marco el lugar como ocupado
  return true;
}

EventType getEvent()
{
  EventType retval;
  if (queueIsEmpty(&queue))
  {
    return 0; // si la cola esta vacia -> error
  }
  retval = queue.p2get->type; // guardo el tipo y muevo el puntero
  queue.p2get->ack = true;
  queue.p2get = (event_t *)queue.p2get->p2NextEv;
  return retval;
}

bool queueIsEmpty(void)
{
  return (queue.p2get == queue.p2write && queue.p2get->ack == true); // si ambos punteros estan en la misma posicion y el evento al que apunta read ya ha sido leido entonces la cola esta vacia
}