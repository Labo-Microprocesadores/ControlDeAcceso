/***************************************************************************/ /**
  @file     fsm.h
  @brief    FSM header.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

#ifndef FSM_H_
#define FSM_H_

#include <stdint.h>

#define FIN_TABLA 0xFF

typedef uint8_t event;
typedef struct state_diagram_edge STATE;


struct state_diagram_edge
{
  event evento;
  STATE *proximo_estado;
  void (*p_rut_accion)(void);
};

// Interfaz
STATE *fsm(STATE *p_tabla_estado, event evento_actual);

#endif /* FSM_H_ */
