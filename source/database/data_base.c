/***************************************************************************/ /**
  @file     data_base.c
  @brief    Application functions
  @author   Grupo 2
 ******************************************************************************/

#include "data_base.h"

static dataBase_t dataBase;
static uint8_t currentIdIndex = -1;

void initializeDataBase(void)
{
    //I define the database and the default value of lastItem
    dataBase_t database;
    dataBase.lastItem = -1;
    //I create 3 dummy users
    user_t newUser1 = {{1, 2, 3, 4, 5, 6, 7, 8}, {9, 8, 7, 6, 5}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, ADMIN};
    user_t newUser2 = {{5, 2, 4, 6, 9, 5, 3, 5}, {1, 2, 3, 4, 5}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, DEFAULT_CARD_CARACTER, DEFAULT_CARD_CARACTER, DEFAULT_CARD_CARACTER, DEFAULT_CARD_CARACTER, DEFAULT_CARD_CARACTER}, USER};
    user_t newUser3 = {{8, 4, 6, 2, 3, 1, 9, 7}, {1, 1, 1, 1, -1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, DEFAULT_CARD_CARACTER, DEFAULT_CARD_CARACTER, DEFAULT_CARD_CARACTER, DEFAULT_CARD_CARACTER, DEFAULT_CARD_CARACTER}, ADMIN};
    //Add the dummy users to the database
    checkAddUser(newUser1);
    checkAddUser(newUser2);
    checkAddUser(newUser3);
}

bool verifyID(uint8_t usersID[ID_ARRAY_SIZE])
{
    uint8_t count, user;
    //I go through the array of users
    for (user = 0; user < MAX_NUM_USERS; user++)
    {
        //if there is a user to check
        if (user <= dataBase.lastItem)
        {
            //I go through the id array checking values
            for (count = 0; count < ID_ARRAY_SIZE; count++)
            {
                if (dataBase.userList[user].userID[count] == usersID[count])
                    continue;
                else
                    count = ID_ARRAY_SIZE; //? No seria mejor poner ahi un break y listo? porque eso es un pseudo break
                //if the counter reached the end it indicates that there were no problems then the vectors are equal
                if (count == ID_ARRAY_SIZE - 1)
                {
                    currentIdIndex = user;
                    return true;
                }
            }
        }
        else
        {
            return false;
        }
    }
}

bool verifyPIN(uint8_t userPIN[PIN_ARRAY_SIZE])
{
    uint8_t count;
    //I go through the id array checking values
    for (count = 0; count < PIN_ARRAY_SIZE; count++)
    {
        if (dataBase.userList[currentIdIndex].userPIN[count] != userPIN[count])
            return false;
    }
    //if no one was diferent then all of them were equals
    return true;
}

status addUser(uint8_t userID[ID_ARRAY_SIZE], uint8_t userPIN[PIN_ARRAY_SIZE], uint8_t cardNumber[MAX_CARD_NUMBER], hierarchy typeOfUser)
{
    user_t newUser= {userID,userPIN,cardNumber,typeOfUser};
    return checkAddUser(newUser);
}


status checkAddUser(user_t newUser)
{

    dataBase.userList[] dataBase.lastItem++;
}

status removeUser(user_t userToDelete)
{
}

status removeUserID(char usersID[ID_LENGTH])
{
}



category_name verifyCategory(char usersID[ID_LENGTH])
{
}


void changePIN(char usersID[ID_LENGTH], char usersNewPIN[PIN_MAX_LENGTH])
{

}