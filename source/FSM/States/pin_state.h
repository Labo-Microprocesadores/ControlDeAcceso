/***************************************************************************//**
  @file     pin_state.h
  @brief    Pin state header
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/
#ifndef PIN_H_
#define PIN_H_
/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define PIN_ARRAY_SIZE   5
//CHAR ORDER: 0 1 2 3 4 5 6 7 8 9 BACKSPACE

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief Changes the current position of the PIN array to the next character following CHAR ORDER.
 */
void increaseCurrent(void);
/**
 * @brief Changes the current position of the PIN array to the previous character following CHAR ORDER.
 */
void decreaseCurrent(void);
/**
 * @brief Set the current position of the PIN array with the introduced character and moves to the next position (unless the character is equal to BACKSPACE).
 *        If the introduced character is equal to BACKSPACE, it deletes the character of the current position and moves to the previous one.
 */
void acceptNumber(void);
/**
 * @brief Checks if the entered PIN is correct and corresponds to an user or an admin in the database.
 *        Adds a PIN_OK or a PIN_FAIL event to the event queue of the FSM.
 */
void confirmPin(void);
/**
 * @brief Function executed when a timeout event is received.
 */
void timerTimeout(void);


#endif //ID_H_*******************************************************/
/**
 * @brief Changes the current position of the PIN array to the next character following CHAR ORDER.
 */
void increaseCurrent(void);
/**
 * @brief Changes the current position of the PIN array to the previous character following CHAR ORDER.
 */
void decreaseCurrent(void);
/**
 * @brief Set the current position of the PIN array with the introduced character and moves to the next position (unless the character is equal to BACKSPACE).
 *        If the introduced character is equal to BACKSPACE, it deletes the character of the current position and moves to the previous one.
 */
void acceptNumber(void);
/**
 * @brief Checks if the entered PIN is correct and corresponds to an user or an admin in the database.
 *        Adds a PIN_OK or a PIN_FAIL event to the event queue of the FSM.
 */
void confirmID(void);
/**
 * @brief Function executed when a timeout event is received.
 */
void timerTimeout(void);


#endif //ID_H_