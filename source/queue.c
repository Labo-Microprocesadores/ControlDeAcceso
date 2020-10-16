#include "queue.h"


/*****************************************************************************************************************
 * FUNCION initQueue
 * Recibe un puntero a un arreglo de tamaño QUEUE_SIZE (se asume correcto)
 * Devuelve una estructura que en su interior tiene lo necesario para controlar la cola de eventos,
 * un puntero para leer y otro para escribir, el usuario no deberá utilizar esos punteros y se debera acceder a
 * la cola solo a traves de las funciones provistas en este libreria. En caso de error devolvera una estructura cola de eventos que tendra un NULL en
 * el puntero de la cola. IMPORTANTE VERIFICAR ESO
 * ES MUY IMPORTANTE QUE SE DESTRUYAN LAS COLAS CREADAS
 *****************************************************************************************************************/

event_queue_t initQueue ( event_queue_t* queue )     
{
  int i;
  if(queue == NULL)
  {
    event_queue_t error = {.queue = NULL};// en caso de error con el
    return error;
  }
  event_t *tempaux = queue;
  
  for(i=0; i < QUEUE_SIZE; i++)
  {
    tempaux++ -> ack = true;//debo hacer esto para asegurarme de que todas las celdas de la cola esten habilitadas para ser escritas
  }
  
  queue->queue = queue; //la cola de eventos
  queue->p2get = queue;//los punteros para leer y escribir estan en el mismo lugar (cola vacia)
  queue->p2write = queue;
}


/*****************************************************************************************************************
 * FUNCION emitEvent
 * recibe un puntero a la cola de eventos en la que se quiera escribir y un ID que identifique el evento que se desee crear
 * Devuelve un bool que sera un 1 si no hubo ningun error y un 0 en caso de que haya habido algun error en la ejecución
 * de la función
 *****************************************************************************************************************/
bool emitEvent( event_queue_t* queue , uint16_t type )
{
  event_t *temp = queue -> p2write;

  if(queue == NULL)
  {
    return false;  // verificacion si el usuario no lo hizo antes
  }


  if(queue -> p2write -> ack == false)  // si en la cola de eventos no hay mas lugar -> error
  {
    return false;
  }
  else
  {

    queue -> p2write -> type = type; // guardo el ID del evento


    if ((queue -> p2write) == ((queue -> queue) + (QUEUE_SIZE-1))) // movimiento del puntero de write
    {
      queue -> p2write = queue -> queue; // si estoy al final de la cola debo moverlo al principio

    }
    else
    {
      (queue -> p2write) ++; // si no avanza una posicion
    }
    temp -> p2NextEv = (struct EVENT*) queue -> p2write;// guardo en el evento anterior un puntero al evento actual para no tener que problems con el movimiento en get_event
    temp -> ack = false;   // marco el lugar como ocupado
    return true;
  }
}

/*****************************************************************************************************************
 * FUNCION getEvent
 * Recibe un puntero a la cola de eventos en la que se quiera leer, 
 * Devuelve el ID del proximo evento que se encuentra en la cola
 *****************************************************************************************************************/
uint16_t getEvent ( event_queue_t* queue  )
{
  uint16_t retval;
  if(queueIsEmpty(queue))
  {
    return 0; // si la cola esta vacia -> error
  }
  retval = queue -> p2get->type; // guardo el ID y muevo el puntero
  queue -> p2get -> ack = true;
  queue -> p2get =(event_t*) queue -> p2get ->p2NextEv;
  return retval;
}

/*****************************************************************************************************************
 * FUNCION queueIsEmpty
 * Recibe un puntero a la cola de eventos en la que se quiera chequear 
 * Devuelve un bool que sera un 0 en caso de que no este vacia y un 1 en caso de que si lo este
 *****************************************************************************************************************/
bool queueIsEmpty( event_queue_t* queue )
{
  return (queue -> p2get == queue -> p2write && queue -> p2get -> ack == true ); // si ambos punteros estan en la misma posicion y el evento al que apunta read ya ha sido leido entonces la cola esta vacia
}