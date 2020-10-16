/***************************************************************************//**
  @file     data_base.c
  @brief    Application functions
  @author   Grupo 2
 ******************************************************************************/

#include "data_base.h"
#include <stdbool.h>

static dataBase_t dataBase;

void initializeDataBase(void)
{
	user_t newUser1 = {{1,2,3,4,5,6,7,8},{9,8,7,6,5},ADMIN};
	user_t newUser2 = {{5,2,4,6,9,5,3,5},{1,2,3,4,5},BASIC};
	user_t newUser3 = {{8,4,6,2,3,1,9,7},{1,1,1,1,-1},ADMIN};
	addUser(newUser1);
	addUser(newUser2);
	addUser(newUser3);
}

void changePIN(char usersID[ID_LENGTH], char usersNewPIN[PIN_MAX_LENGTH])
{
	
}

status addUser(user_t newUser)
{
	
}

status removeUser(user_t userToDelete)
{
		
}

status removeUserID(char usersID[ID_LENGTH])
{
	
}

bool verifyID(char usersID[ID_LENGTH])
{
	
}

bool verifyPIN(char usersID[ID_LENGTH], char usersPIN[PIN_MAX_LENGTH])
{
	
}

category_name verifyCategory(char usersID[ID_LENGTH])
{
	
}
