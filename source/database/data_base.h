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
    ID_WRONG_FORMAT,
    ID_NOT_FOUND
} status;
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

bool verifyPIN(uint8_t userPIN[PIN_ARRAY_SIZE]);

bool verifyID(uint8_t usersID[ID_ARRAY_SIZE]);

bool IsAdmin(void);

void initializeDataBase(void);

status addUser(user_t newUser);

status removeUser(user_t userToDelete);

status removeUserID(char usersID[ID_LENGTH]);

category_name verifyCategory(char usersID[ID_LENGTH]);

void changePIN(char usersID[ID_LENGTH], char usersNewPIN[PIN_MAX_LENGTH]);

#endif /* DATABASE_H_ */