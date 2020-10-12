/***************************************************************************//**
  @file     id.h
  @brief    id state
  @author   Grupo 2
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
#define ID_ARRAY_SIZE   8
#define DEFAULT_ID_CHAR_VALUE   -1
#define BACKSPACE -2


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
void increaseCurrent(void);
void decreaseCurrent(void);
void acceptNumber(void);
void confirmID(void);
void timerTimeout(void);

#endif //ID_H_