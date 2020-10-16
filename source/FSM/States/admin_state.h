/***************************************************************************/ /**
  @file     admin_state.h
  @brief    Admin state header
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/
#ifndef ADMIN_STATE_H
#define ADMIN_STATE_H

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define OPTIONS_ARRAY_SIZE 5


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief Changes the current position of the ID array to the next character following CHAR ORDER.
 */
void nextOption(void);
/**
 * @brief Shows the next menu option.
 */
void previousOption(void);

/**
 * @brief Selects the current option. Adds an event to the event queue of the FSM.
 */
void selectOption(void);

#endif /* ADMIN_STATE_H */