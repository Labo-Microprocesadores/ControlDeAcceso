/***************************************************************************/ /**
  @file     data_base.c
  @brief    Application functions
  @author   Grupo 2
 ******************************************************************************/

#include "data_base.h"

static dataBase_t dataBase;
static uint8_t currentIdIndex = -1;

/**
 * @brief Checks if the "id" array format matches the format of an id. The array must be complete (length equal to ID_ARRAY_SIZE) and all elements must be numbers from 0 to 9.
 * @param userID, The id array.
 * @return A bool indicating if the format is valid or not.
 */
static bool checkIdArrayFormat(uint8_t userID[ID_ARRAY_SIZE]);
/**
 * @brief Checks if the "pin" array format matches the format of a pin. The array must be complete (length equal to PIN_ARRAY_SIZE) and all elements must be numbers from 0 to 9.4
 * @param userPIN, The pin array.
 * @return A bool indicating if the format is valid or not.
 */
static bool checkPinArrayFormat(uint8_t userPIN[PIN_ARRAY_SIZE]);

static int getEffectiveArrayLength(uint8_t *inputArray, int totalArraySize);

static bool checkIdAvailability(uint8_t userID[ID_ARRAY_SIZE]);

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
    checkAddUser(newUser1.userID, newUser1.userPIN, newUser1.cardNumber, newUser1.typeOfUser);
    checkAddUser(newUser2.userID, newUser2.userPIN, newUser2.cardNumber, newUser2.typeOfUser);
    checkAddUser(newUser3.userID, newUser3.userPIN, newUser3.cardNumber, newUser3.typeOfUser);
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

bool IsAdmin(void)
{
    if (dataBase.userList[currentIdIndex].typeOfUser == ADMIN)
        return true;
    else
        return false;
}

status checkAddUser(uint8_t userID[ID_ARRAY_SIZE], uint8_t userPIN[PIN_ARRAY_SIZE], uint8_t cardNumber[MAX_CARD_NUMBER], hierarchy typeOfUser)
{
    status howWas = validateAll(userID, userPIN, cardNumber, typeOfUser);
    if (howWas == VALIDATE_SUCCESSFULL)
    {

        user_t newUser = {userID, userPIN, cardNumber, typeOfUser};
        
        lastItem++;
        return;
    }
    else
        return howWas;
}

status validateAll(uint8_t userID[ID_ARRAY_SIZE], uint8_t userPIN[PIN_ARRAY_SIZE], uint8_t cardNumber[MAX_CARD_NUMBER], hierarchy typeOfUser)
{
    /***************************************************************************/
    //                             ValidateUserID
    /***************************************************************************/
    if(!checkIdArrayFormat(userID))
        return ID_WRONG_FORMAT;
    if(!checkIdAvailability(userID))
        return ID_ALREADY_EXISTS;
















    //Split the validation on each variable
    if (validateUserID(userID) && validateUserPIN(userPIN) && validateCardNumber(cardNumber) && validateTypeOfUser(typeOfUser))
        return true;
    else
        return false;
}

static bool checkIdAvailability(uint8_t userID[ID_ARRAY_SIZE])
{

}

static bool checkIdArrayFormat(uint8_t userID[ID_ARRAY_SIZE])
{
    int currentArrayLength = getEffectiveArrayLength(userID, ID_ARRAY_SIZE);

    if (currentArrayLength != ID_ARRAY_SIZE)
        return false;

    return true;
}


static bool checkPinArrayFormat(uint8_t userPIN[PIN_ARRAY_SIZE])
{
    int currentArrayLength = getEffectiveArrayLength(userPIN, PIN_ARRAY_SIZE);

    if (currentArrayLength != PIN_ARRAY_SIZE && currentArrayLength != PIN_ARRAY_SIZE - 1) //4 or 5 chars
        return false;

    return true;
}


static int getEffectiveArrayLength(uint8_t *inputArray, int totalArraySize)
{
    int length = 0;
    bool foundLast = false;
    while (!foundLast && length < totalArraySize)
    {
        uint8_t lastChar = inputArray[length];
        if (lastChar == NO_INPUT_CHAR || lastChar == BACKSPACE)
            foundLast = true;
        else
            length++;
    }
    return length;
}




















status removeUser(user_t userToDelete)
{
}

status removeUserID(char usersID[ID_LENGTH])
{
}

void changePIN(char usersID[ID_LENGTH], char usersNewPIN[PIN_MAX_LENGTH])
{
}