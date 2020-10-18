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
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief Initializes the menu
 */
void admin_initAdminMenu(void);
/**
 * @brief Changes the current position of the ID array to the next character following CHAR ORDER.
 */
void admin_nextOption(void);
/**
 * @brief Shows the next menu option.
 */
void admin_previousOption(void);

/**
 * @brief Selects the current option. Adds an event to the event queue of the FSM.
 */
void admin_selectOption(void);

#endif /* ADMIN_STATE_H */