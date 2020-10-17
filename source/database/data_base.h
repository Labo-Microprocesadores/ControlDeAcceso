/***************************************************************************//**
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
#define MAX_NUM_USERS	20
#define MAX_CARD_NUMBER 19
#define DEFAULT_CARD_CARACTER -1

typedef enum {SUCCESSFULL,DATABASE_FULL,ID_ALREADY_EXISTS,ID_NOT_FOUND}status;
typedef enum {USER, ADMIN}hierarchy;

typedef struct{
	uint8_t userID[ID_ARRAY_SIZE];
	uint8_t userPIN[PIN_ARRAY_SIZE];
    uint8_t cardNumber[MAX_CARD_NUMBER];
	hierarchy typeOfUser;
}user_t;

typedef struct{
	user_t userList[MAX_NUM_USERS];
    uint8_t lastItem;
    uint8_t Attempts;
}dataBase_t;

void initializeDataBase(void);

status addUser(user_t newUser);

status removeUser(user_t userToDelete);

status removeUserID(char usersID[ID_LENGTH]);

bool verifyID(char usersID[ID_LENGTH]);

bool verifyPIN(char usersID[ID_LENGTH], char usersPIN[PIN_MAX_LENGTH]);

category_name verifyCategory(char usersID[ID_LENGTH]);

void changePIN(char usersID[ID_LENGTH], char usersNewPIN[PIN_MAX_LENGTH]);

#endif /* DATABASE_H_ */