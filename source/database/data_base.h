/***************************************************************************/ /**
  @file     data_base.h
  @brief    Application functions
  @author   Grupo 2
 ******************************************************************************/

#ifndef DATA_BASE_H_
#define DATA_BASE_H_

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

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
#define MAX_NUM_ATTEMPTS 3

typedef enum
{
    VALIDATE_SUCCESSFULL,
    DATABASE_FULL,
    ID_ALREADY_EXISTS,
    CARD_NUMBER_EXISTS,
    ID_WRONG_FORMAT,
    PIN_WRONG_FORMAT,
    CARD_NUMBER_WRONG_FORMAT,
    STORE_SUCCESSFULL,
    DELETE_SUCCESSFULL,
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
    int8_t userID[ID_ARRAY_SIZE];
    int8_t userPIN[PIN_ARRAY_SIZE];
    int8_t cardNumber[MAX_CARD_NUMBER];
    hierarchy_t typeOfUser;
    uint8_t Attempts;
} user_t;

typedef struct
{
    user_t userList[MAX_NUM_USERS];
    uint8_t lastItem;
} dataBase_t;

void initializeDataBase(void);

bool verifyID(int8_t usersID[]);

bool verifyPIN(int8_t userPIN[]);

bool isCurrentUserBlocked(void);


bool IsAdmin(void);

Status checkAddUser(int8_t userID[], int8_t userPIN[], int8_t cardNumber[], uint8_t numCharactersCardNumber, hierarchy_t typeOfUser);

Status validateAll(int8_t userID[], int8_t userPIN[], int8_t cardNumber[], uint8_t numCharactersCardNumber, hierarchy_t typeOfUser);

Status validateNewId(int8_t userID[]);

Status changePin(int8_t* userNewPin);

bool verifyCardNumber(int8_t cardNumber[], uint8_t numCharactersCardNumber);

Status removeUser(int8_t userID[]);

void UnblockUser(void);

bool isCurrentUserBlocked(void);

/**
 * @brief Checks if the "pin" array format matches the format of a pin. The array must be complete (length equal to PIN_ARRAY_SIZE) and all elements must be numbers from 0 to 9.4
 * @param userPIN, The pin array.
 * @return A bool indicating if the format is valid or not.
 */
static bool checkPinArrayFormat(int8_t userPIN[]);


#endif /* DATABASE_H_ */
