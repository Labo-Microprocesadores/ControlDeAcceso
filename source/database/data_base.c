/***************************************************************************/ /**
  @file     data_base.c
  @brief    Application functions
  @author   Grupo 2
 ******************************************************************************/

#include "data_base.h"
#include "Timer.h"

#define MAX_BLOCKED_USERS   30
#define BLOCK_TIME  10000   //1min
#define NO_USER_INDEX   -1

static dataBase_t dataBase;
static uint8_t currentIdIndex = -1;
static dataBase_t database;
static uint8_t validNumberArray[MAX_CARD_NUMBER];
static uint8_t blockedUsersIndexes[MAX_BLOCKED_USERS];

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


static bool CreateValidNumberArrayFormat(uint8_t cardNumber[], uint8_t numCharactersCardNumber, uint8_t validNumberArray[]);


static int getEffectiveArrayLength(uint8_t *inputArray, int totalArraySize);

static void moveAllUsersOnePlace(void);

void initializeDataBase(void)
{
    //I define the database and the default value of lastItem
    dataBase.lastItem = -1;
    //I create 3 dummy users
    user_t newUser1 = {{1, 2, 3, 4, 5, 6, 7, 8}, {9, 8, 7, 6, 5}, {6,0,3,1,6,7,0,9,1,2,0,2,4,1,0,1,8,4,5}, ADMIN};
    user_t newUser2 = {{5, 2, 4, 6, 9, 5, 3, 5}, {1, 2, 3, 4, 5}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, USER};
    user_t newUser3 = {{8, 4, 6, 2, 3, 1, 9, 7}, {1, 1, 1, 1, -1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,}, ADMIN};
    //Add the dummy users to the database
    checkAddUser(newUser1.userID, newUser1.userPIN, newUser1.cardNumber, 19, newUser1.typeOfUser);
    checkAddUser(newUser2.userID, newUser2.userPIN, newUser2.cardNumber, 14, newUser2.typeOfUser);
    checkAddUser(newUser3.userID, newUser3.userPIN, newUser3.cardNumber, 12, newUser3.typeOfUser);
    //Initialize blocked users' array
    for (uint8_t i = 0; i< MAX_BLOCKED_USERS; i++)
    {
        blockedUsersIndexes[i] = NO_USER_INDEX;
    }
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

        if(!equalID)
            return false;
        
        currentIdIndex = user;
        if (isCurrentUserBlocked())
        {
            currentIdIndex = -1;
            return false;
        }
        return true;
    }
}

bool verifyPIN(uint8_t userPIN[])
{
    uint8_t count;
    //I go through the id array checking values
    for (count = 0; count < PIN_ARRAY_SIZE; count++)
    {
        if (dataBase.userList[currentIdIndex].userPIN[count] != userPIN[count])
        {
            dataBase.userList[currentIdIndex].Attempts++;
            if (isCurrentUserBlocked)
            {
                int blockedArrayLength = getEffectiveArrayLength(blockedUsersIndexes, MAX_BLOCKED_USERS);
                blockedUsersIndexes[blockedArrayLength] = currentIdIndex;
                Timer_AddCallback(&UnblockUser, BLOCK_TIME, true);
            }
            return false;
        }
    }
    //if no one was diferent then all of them were equals
    return true;
}

bool isCurrentUserBlocked(void)
{
    if(dataBase.userList[currentIdIndex].Attempts >= MAX_NUM_ATTEMPTS)
    {
        //true for blocked
        return true;
    }
    return false;
}


void UnblockUser(void)
{
    if (getEffectiveArrayLength(blockedUsersIndexes, MAX_BLOCKED_USERS)<=0)
        return;

    dataBase.userList[blockedUsersIndexes[0]].Attempts = 0; //User unblocked

    //Pops first item
    for(uint8_t i = 0; i < MAX_BLOCKED_USERS - 1; i++) 
        blockedUsersIndexes[i] = blockedUsersIndexes[i + 1];
    blockedUsersIndexes[MAX_BLOCKED_USERS - 1] = NO_USER_INDEX;
}

bool IsAdmin(void)
{
    if (dataBase.userList[currentIdIndex].typeOfUser == ADMIN)
        return true;
    return false;
}

Status checkAddUser(uint8_t userID[], uint8_t userPIN[], uint8_t cardNumber[], uint8_t numCharactersCardNumber, hierarchy_t typeOfUser)
{
	uint8_t validNumberArray[MAX_CARD_NUMBER];
    Status howWas = validateAll(userID, userPIN, cardNumber, numCharactersCardNumber, validNumberArray, typeOfUser);
    if (howWas != VALIDATE_SUCCESSFULL)
        return howWas;
    /***************************************************************************/
    //                    all was fine, store on database
    /***************************************************************************/
    dataBase.lastItem++;
    uint8_t count;
    //store userID
    for(count=0; count < ID_ARRAY_SIZE; count++)
    {
        dataBase.userList[dataBase.lastItem].userID[count] = userID[count];
    }
    //store userPIN
    for(count=0; count < PIN_ARRAY_SIZE; count++)
    {
        dataBase.userList[dataBase.lastItem].userPIN[count] = userPIN[count];
    }
    //store cardNumber
    for(count=0; count < MAX_CARD_NUMBER; count++)
    {
        dataBase.userList[dataBase.lastItem].cardNumber[count] = validNumberArray[count];
    }
    //store typeOfUser
    dataBase.userList[dataBase.lastItem].typeOfUser = typeOfUser;
    //set Attempts
    dataBase.userList[database.lastItem].Attempts = 0;
    return STORE_SUCCESSFULL;       
}

Status validateAll(uint8_t userID[], uint8_t userPIN[], uint8_t cardNumber[], uint8_t numCharactersCardNumber, uint8_t validNumberArray[], hierarchy_t typeOfUser)
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
    if (verifyCardNumber(cardNumber, numCharactersCardNumber))
        return CARD_NUMBER_EXISTS;
    
    return VALIDATE_SUCCESSFULL;
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

static bool checkCardNumberArrayFormat(uint8_t userCardNumber[])
{
    int currentArrayLength = getEffectiveArrayLength(userCardNumber, MAX_CARD_NUMBER);

    if (currentArrayLength != MAX_CARD_NUMBER)
        return false;

    return true;
}

static int getEffectiveArrayLength(uint8_t *inputArray, int totalArraySize)
{
    int length = 0;
    bool foundLast = false;
    while (!foundLast && length < totalArraySize)
    {
        uint8_t lastPosition = inputArray[length];
        if (lastPosition == NO_INPUT_CHAR || lastPosition == BACKSPACE || lastPosition == NO_USER_INDEX)
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


static bool CreateValidNumberArrayFormat(uint8_t cardNumber[], uint8_t numCharactersCardNumber, uint8_t validNumberArray[])
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

bool verifyCardNumber(uint8_t cardNumber[], uint8_t numCharactersCardNumber)
{
    uint8_t validNumberArray[MAX_CARD_NUMBER];
    uint8_t count;
    //I put the default character in the uncompleted positions
    for(count=0; count <= MAX_CARD_NUMBER; count++)
    {
        if(count < numCharactersCardNumber)
            validNumberArray[count]=cardNumber[count];
        else         
            validNumberArray[count] = DEFAULT_CARD_CARACTER;
    }
    
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
        {
            currentIdIndex = count-1;
            return true;
        }
    }
    return false;
}


Status removeUser(uint8_t userID[])
{
    //call to verify ID to know if userID is on the array of users and to know it index with currentIdIndex
    if(verifyID(userID))
    {
        moveAllUsersOnePlace();
        dataBase.lastItem--;
        return DELETE_SUCCESSFULL;
    }
    return ID_NOT_FOUND;
}

static void moveAllUsersOnePlace(void)
{
    uint8_t count;
    //if the element wasn't the last one
    if(currentIdIndex != MAX_NUM_USERS -1)
    {
        for(count = currentIdIndex; count < dataBase.lastItem; count++)
        {
            //move userPIN value
            for(count=0; count < ID_ARRAY_SIZE-1; count++)
            {
                dataBase.userList[currentIdIndex].userID[count] = dataBase.userList[currentIdIndex+1].userID[count];
            }
            //move userPIN value
            for(count=0; count < PIN_ARRAY_SIZE-1; count++)
            {
                dataBase.userList[currentIdIndex].userPIN[count] = dataBase.userList[currentIdIndex+1].userPIN[count];
            }
            //move cardNumber
            for(count=0; count < MAX_CARD_NUMBER-1; count++)
            {
                dataBase.userList[currentIdIndex].cardNumber[count] = dataBase.userList[currentIdIndex+1].cardNumber[count];
            }
            //move typeOfUser
            dataBase.userList[currentIdIndex].typeOfUser = dataBase.userList[currentIdIndex +1].typeOfUser;
            //move attempts
            dataBase.userList[currentIdIndex].Attempts = dataBase.userList[currentIdIndex +1].Attempts;
        }
    }
}
