#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>


typedef struct EVENT
{
  uint16_t type;
  bool ack; 
  struct EVENT *p2NextEv;
}event_t;

typedef struct
{
  event_t *queue;       
  event_t *p2get;
  event_t *p2write;
}event_queue_t;


#define QUEUE_SIZE 100 //cambiar este define por la cantidad de posiciones deseadas en la cola, recomiendo entre 100 y 200 para este programa


/*****************************************************************************************************************
 * FUNCION create_queue
 * Recibe un puntero a un arreglo de tamaño QUEUE_SIZE (se asume correcto)
 * Devuelve una estructura que en su interior tiene lo necesario para controlar la cola de eventos,
 * un puntero para leer y otro para escribir, el usuario no deberá utilizar esos punteros y se debera acceder a
 * la cola solo a traves de las funciones provistas en este libreria. En caso de error devolvera una estructura cola de eventos que tendra un NULL en
 * el puntero de la cola. IMPORTANTE VERIFICAR ESO
 * ES MUY IMPORTANTE QUE SE DESTRUYAN LAS COLAS CREADAS
 *****************************************************************************************************************/
event_queue_t initQueue ( event_queue_t* queue );




/*****************************************************************************************************************
 * FUNCION emitEvent
 * recibe un puntero a la cola de eventos en la que se quiera escribir y un ID que identifique el evento que se desee crear
 * Devuelve un bool que sera un 1 si no hubo ningun error y un 0 en caso de que haya habido algun error en la ejecución
 * de la función
 *****************************************************************************************************************/
bool emitEvent( event_queue_t* queue , uint16_t type );







/*****************************************************************************************************************
 * FUNCION getEvent
 * Recibe un puntero a la cola de eventos en la que se quiera leer, 
 * Devuelve el ID del proximo evento que se encuentra en la cola
 *****************************************************************************************************************/
uint16_t getEvent ( event_queue_t* queue  );





/*****************************************************************************************************************
 * FUNCION queueIsEmpty
 * Recibe un puntero a la cola de eventos en la que se quiera chequear 
 * Devuelve un bool que sera un 0 en caso de que no este vacia y un 0 en caso de que si lo este
 *****************************************************************************************************************/
bool queueIsEmpty( event_queue_t* queue );

#endif