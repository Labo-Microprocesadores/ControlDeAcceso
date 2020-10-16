/***************************************************************************/ /**
  @file     id_state.h
  @brief    ID state header
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/
#ifndef ID_H_
#define ID_H_
/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define ID_ARRAY_SIZE 8
//CHAR ORDER: 0 1 2 3 4 5 6 7 8 9 BACKSPACE

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief Changes the current position of the ID array to the next character following CHAR ORDER.
 */
void id_increaseCurrent(void);
/**
 * @brief Changes the current position of the ID array to the previous character following CHAR ORDER.
 */
void id_decreaseCurrent(void);
/**
 * @brief Set the current position of the ID array with the introduced character and moves to the next position (unless the character is equal to BACKSPACE).
 *        If the introduced character is equal to BACKSPACE, it deletes the character of the current position and moves to the previous one.
 */
void id_acceptNumber(void);
/**
 * @brief Checks if the entered ID is correct and corresponds to an user or an admin in the database.
 *        Adds a ID_OK or a ID_FAIL event to the event queue of the FSM.
 */
void id_confirmID(void);
/**
 * @brief Checks if the read ID (from card) is correct and corresponds to an user or an admin in the database.
 *        Adds a ID_OK or a ID_FAIL event to the event queue of the FSM.
 */
void id_checkCardID(void);
/**
 * @brief Function executed when a timeout event is received.
 */
void id_timerTimeout(void);
/**
 * @brief Returns the array of the ID.
 * @param sizeOfReturningArray: A pointer to an integer where the size of the ID array gets stored.
 * @return The array of introduced characters.
 */
uint8_t *id_getIDArray(int *sizeOfReturningArray);
/**
 * @brief Function executed when ID is correct and updates display's chars with the word "PIN".
 */
void id_updateDispPin(void);




#endif //ID_H_