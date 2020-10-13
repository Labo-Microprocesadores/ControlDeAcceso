/* 
 *
 *  Created on: 28/07/2014
 *      Author: El charlo y el mati
 */

#ifndef FSM_H_
#define FSM_H_

#include <stdint.h>

#define FIN_TABLA 0xFF

typedef	uint8_t event;
typedef struct state_diagram_edge STATE;

//EVENTS
typedef enum {NONE, LKP_EV, PRESS_EV, ENCODER_LEFT_EV, ENCODER_RIGHT_EV, CARD_SWIPE_EV, TIMER_EV, ID_OK_EV, ID_FAIL_EV, ADMIN_PIN_OK_EV, USR_PIN_OK_EV, PIN_FAIL_EV }Events_t; //VER SI ESTO ES LO MEJOR, O SI ES MEJOR UNA ESTRUCTURA EVENTO MAS COMPLEJA, ADEMAS FALTA DIFERENCIAR LOS DISTINTOS EVENTOS DE TIMER

struct state_diagram_edge
{
	event  evento;
	STATE *proximo_estado;
	void (*p_rut_accion)(void);
};

// Interfaz
STATE* fsm(STATE *p_tabla_estado,event evento_actual);



#endif /* FSM_H_ */
 