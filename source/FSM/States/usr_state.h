/***************************************************************************/ /**
  @file     usr_state.h
  @brief    User state header
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/
#ifndef USER_STATE_H
#define USER_STATE_H
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
void initUserMenu(void);
/**
 * @brief Shows the previous option
 */
void usr_nextOption(void);
/**
 * @brief Shows the next option.
 */
void usr_previousOption(void);

/**
 * @brief Selects the current option. Adds an event to the event queue of the FSM.
 */
void usr_selectOption(void);

#endif /* USER_STATE_H */