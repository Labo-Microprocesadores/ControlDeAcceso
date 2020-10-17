/***************************************************************************/ /**
  @file     data_base.c
  @brief    Application functions
  @author   Grupo 2
 ******************************************************************************/

#include "data_base.h"

static dataBase_t dataBase;
static uint8_t currentIdIndex = -1;
static dataBase_t database;
static uint8_t validNumberArray[MAX_CARD_NUMBER];

/**
 * @brief Checks if the "id" array format matches the format of an id. The array must be complete (length equal to ID_ARRAY_SIZE) and all elements must be numbers from 0 to 9.
 * @param userID, The id array.
 * @return A bool indicating if the format is valid or not.
 */
static bool checkIdArrayFormat(uint8_t userID[]);
/**
 * @brief Checks if the "pin" array format matches the format of a pin. The array must be complete (length equal to PIN_ARRAY_SIZE) and all elements must be numbers from 0 to 9.4
 * @param userPIN, The pin array.
 * @return A bool indicating if the format is valid or not.
 */
static bool checkPinArrayFormat(uint8_t userPIN[]);

static bool CreateValidNumberArrayFormat(uint8_t cardNumber[]);

static int getEffectiveArrayLength(uint8_t *inputArray, int totalArraySize);

void initializeDataBase(void)
{
    //I define the database and the default value of lastItem
    dataBase.lastItem = -1;
    //I create 3 dummy users
    user_t newUser1 = {{1, 2, 3, 4, 5, 6, 7, 8}, {9, 8, 7, 6, 5}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 19, ADMIN};
    user_t newUser2 = {{5, 2, 4, 6, 9, 5, 3, 5}, {1, 2, 3, 4, 5}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 14, USER};
    user_t newUser3 = {{8, 4, 6, 2, 3, 1, 9, 7}, {1, 1, 1, 1, -1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,}, 12, ADMIN};
    //Add the dummy users to the database
    checkAddUser(newUser1.userID, newUser1.userPIN, newUser1.cardNumber, newUser1.numCharactersCardNumber, newUser1.typeOfUser);
    checkAddUser(newUser2.userID, newUser2.userPIN, newUser2.cardNumber, newUser1.numCharactersCardNumber, newUser2.typeOfUser);
    checkAddUser(newUser3.userID, newUser3.userPIN, newUser3.cardNumber, newUser1.numCharactersCardNumber, newUser3.typeOfUser);
}

bool verifyID(uint8_t usersID[])
{
    uint8_t  user;
    //I go through the array of users
    for (user = 0; user < MAX_NUM_USERS; user++)
    {
        //if there are no more users to check
        if (user > dataBase.lastItem)
            return false;
        
        bool equalID = true;
        //I go through the id array checking values
        uint8_t count = 0;
        while (count < ID_ARRAY_SIZE && equalID)
        {
            if (dataBase.userList[user].userID[count] != usersID[count])   //If the ID is different
                equalID = false;
            count ++;                
        }
        if (equalID)
        {
            currentIdIndex = user;
            return true;
        }
    }
}

bool verifyPIN(uint8_t userPIN[])
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
    return false;
}

Status checkAddUser(uint8_t userID[], uint8_t userPIN[], uint8_t cardNumber[], uint8_t numCharactersCardNumber, hierarchy typeOfUser)
{
    
    Status howWas = validateAll(userID, userPIN, cardNumber, numCharactersCardNumber, typeOfUser);
    if (howWas != VALIDATE_SUCCESSFULL)
        return howWas;

    user_t newUser = {userID, userPIN, cardNumber, numCharactersCardNumber, typeOfUser};
    //! falta agregar los usuarios
    dataBase.lastItem++;
    return;       
}

Status validateAll(uint8_t userID[], uint8_t userPIN[], uint8_t cardNumber[], uint8_t numCharactersCardNumber, hierarchy typeOfUser)
{
    //check Database space
    if (database.lastItem == MAX_NUM_USERS - 1)
        return DATABASE_FULL;
    /***************************************************************************/
    //                           Validate UserID
    /***************************************************************************/
    //check Id Format
    if (!checkIdArrayFormat(userID))
        return ID_WRONG_FORMAT;
    //check Id Availability
    if (verifyID(userID))
        return ID_ALREADY_EXISTS;
    /***************************************************************************/
    //                           Validate UserPIN
    /***************************************************************************/
    //check Pin Format
    if (!checkPinArrayFormat(userID))
        return PIN_WRONG_FORMAT;
    /***************************************************************************/
    //                           Create Valid Card Number
    /***************************************************************************/
    //check Card Number Format
    CreateValidNumberArrayFormat(cardNumber, numCharactersCardNumber);
    if (verifyCardNumber())
        return CARD_NUMBER_EXISTS;
}

static bool checkIdArrayFormat(uint8_t userID[])
{
    int currentArrayLength = getEffectiveArrayLength(userID, ID_ARRAY_SIZE);

    if (currentArrayLength != ID_ARRAY_SIZE)
        return false;

    return true;
}

static bool checkPinArrayFormat(uint8_t userPIN[])
{
    int currentArrayLength = getEffectiveArrayLength(userPIN, PIN_ARRAY_SIZE);

    if (currentArrayLength != PIN_ARRAY_SIZE && currentArrayLength != PIN_ARRAY_SIZE - 1) //4 or 5 chars
        return false;

    return true;
}

static bool checkCardNumberArrayFormat(uint8_t userID[])
{
    int currentArrayLength = getEffectiveArrayLength(userID, ID_ARRAY_SIZE);

    if (currentArrayLength != ID_ARRAY_SIZE)
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

Status changePin(uint8_t userOldPin[], uint8_t userNewPin[])
{
    if (!verifyPIN(userOldPin))
        return WRONG_PIN_VERIFICATION;
    
    if (!checkPinArrayFormat(userNewPin))
        return PIN_WRONG_FORMAT;

    uint8_t count;
    for (count = 0; count < PIN_ARRAY_SIZE; count++)
    {
        dataBase.userList[currentIdIndex].userPIN[count] = userNewPin[count]; 
    }  
    return PIN_CHANGED_SUCCESFULLY;
}


static bool CreateValidNumberArrayFormat(uint8_t cardNumber[], uint8_t numCharactersCardNumber)
{
    uint8_t count;
    //I put the default character in the uncompleted positions
    for(count=0; count <= MAX_CARD_NUMBER; count++)
    {
        if(count < numCharactersCardNumber)
            validNumberArray[count]=cardNumber[count];
        else         
            validNumberArray[count] = DEFAULT_CARD_CARACTER;
    }
    return true;
}


Status removeUser(user_t userToDelete)
{

}

bool verifyCardNumber()
{
    validNumberArray[MAX_CARD_NUMBER];
    uint8_t  user;
    //I go through the array of users
    for (user = 0; user < MAX_NUM_USERS; user++)
    {
        //if there are no more users to check
        if (user > dataBase.lastItem)
            return false;
        
        bool equalID = true;
        //I go through the id array checking values
        uint8_t count = 0;
        while (count < MAX_CARD_NUMBER && equalID)
        {
            if (dataBase.userList[user].cardNumber[count] != validNumberArray[count])   //If the ID is different
                equalID = false;
            count ++;                
        }
        if (equalID)
            return true;
    }
}


