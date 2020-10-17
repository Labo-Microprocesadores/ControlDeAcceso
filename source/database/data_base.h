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
} hierarchy;

typedef struct
{
    uint8_t userID[ID_ARRAY_SIZE];
    uint8_t userPIN[PIN_ARRAY_SIZE];
    uint8_t cardNumber[MAX_CARD_NUMBER];
    hierarchy typeOfUser;
} user_t;

typedef struct
{
    user_t userList[MAX_NUM_USERS];
    uint8_t lastItem;
    uint8_t Attempts;
} dataBase_t;

bool verifyPIN(uint8_t userPIN[]);

bool verifyID(uint8_t usersID[]);

bool IsAdmin(void);

void initializeDataBase(void);

Status addUser(user_t newUser);

Status removeUser(user_t userToDelete);

Status changePin(uint8_t userOldPin[], uint8_t userNewPin[]);

Status removeUserID(uint8_t usersID[]);

category_name verifyCategory(char usersID[]);



typedef struct
{
    user_t userList[MAX_NUM_USERS];
    uint8_t lastItem;
    uint8_t Attempts;
} dataBase_t;

bool verifyPIN(uint8_t userPIN[]);

bool verifyID(uint8_t usersID[]);

bool IsAdmin(void);

void initializeDataBase(void);

Status addUser(user_t newUser);

Status removeUser(user_t userToDelete);

Status changePin(uint8_t userOldPin[], uint8_t userNewPin[]);

Status removeUserID(uint8_t usersID[]);

category_name verifyCategory(char usersID[]);



#endif /* DATABASE_H_ */