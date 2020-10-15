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
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define OPTIONS_ARRAY_SIZE 2
/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief Shows the previous option
 */
void nextOption(void);
/**
 * @brief Shows the next option.
 */
void previousOption(void);

/**
 * @brief Selects the current option. Adds an event to the event queue of the FSM.
 */
void selectOption(void);

#endif /* USER_STATE_H */