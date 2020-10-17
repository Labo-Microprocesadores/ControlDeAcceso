/***************************************************************************/ /**
  @file     data_base.h
  @brief    Application functions
  @author   Grupo 2
 ******************************************************************************/

#ifndef DATA_BASE_H_
#define DATA_BASE_H_

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define ID_ARRAY_SIZE 8
#define PIN_ARRAY_SIZE 5
#define MAX_NUM_USERS 20
#define MAX_CARD_NUMBER 19
#define DEFAULT_CARD_CARACTER -1
#define NO_INPUT_CHAR -1
#define BACKSPACE -2

typedef enum
{
    VALIDATE_SUCCESSFULL,
    DATABASE_FULL,
    ID_ALREADY_EXISTS,
    CARD_NUMBER_EXISTS,
    ID_WRONG_FORMAT,
    PIN_WRONG_FORMAT,
    CARD_NUMBER_WRONG_FORMAT,
    ID_NOT_FOUND,
    WRONG_PIN_VERIFICATION,
    PIN_CHANGED_SUCCESFULLY
} Status;
typedef enum
{
    USER,
    ADMIN
} hierarchy_t;

typedef struct
{
    uint8_t userID[ID_ARRAY_SIZE];
    uint8_t userPIN[PIN_ARRAY_SIZE];
    uint8_t cardNumber[MAX_CARD_NUMBER];
    hierarchy_t typeOfUser;
    uint8_t numCharactersCardNumber;
} user_t;

typedef struct
{
    user_t userList[MAX_NUM_USERS];
    uint8_t lastItem;
    uint8_t Attempts;
} dataBase_t;

void initializeDataBase(void);

bool verifyID(uint8_t usersID[]);

bool verifyPIN(uint8_t userPIN[]);

bool IsAdmin(void);

Status checkAddUser(uint8_t userID[], uint8_t userPIN[], uint8_t cardNumber[], uint8_t numCharactersCardNumber, hierarchy_t typeOfUser);

Status validateAll(uint8_t userID[], uint8_t userPIN[], uint8_t cardNumber[], uint8_t numCharactersCardNumber, uint8_t validNumberArray[], hierarchy_t typeOfUser);

Status changePin(uint8_t userOldPin[], uint8_t userNewPin[]);

bool verifyCardNumber(uint8_t validNumberArray[]);

Status removeUser(user_t userToDelete)


#endif /* DATABASE_H_ */