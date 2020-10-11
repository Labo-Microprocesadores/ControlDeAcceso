/***************************************************************************//**
  @file     Button.c
  @brief    Button configurations
  @author   Grupo 2
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "button.h"
#include "SysTick.h"


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef  struct
	{
		pin_t pin;
		enum type typefunction;
		bool lastState;
		int currentCount;
		int lkpTime;
		int typeTime;
		bool wasLkp;
		bool wasPressed;
		bool wasReleased;
	}Button_t;

/*******************************************************************************
 * PRIVATE VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static Button_t buttons[BUTTON_NUM];

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void systick_callback(void);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void buttonsInit(void)
{
	//agregar botones del punto h
	SysTick_AddCallback(&systick_callback, 50); //50 ms
}

bool wasPressed(pin_t button)
{
	int count;
	for(count=0;count<BUTTON_NUM;count++)
	{
		if(buttons[count].pin == button )
		{
			bool aux =buttons[count].wasPressed;
			if(aux)
				buttons[count].wasPressed = false;

			return aux ;
		}
	}
	return false;
}

bool wasReleased(pin_t button)
{
	int count;
	for(count=0;count<BUTTON_NUM;count++)
	{
		if(buttons[count].pin == button )
		{
			bool aux =buttons[count].wasReleased;
			if(aux)
				buttons[count].wasReleased = false;

			return aux ;
		}
	}
	return false;
}

bool wasLkp(pin_t button)
{
	int count;
	for(count=0;count<BUTTON_NUM;count++)
	{
		if(buttons[count].pin == button )
		{
			bool aux =buttons[count].wasLkp;
			if(aux)
				buttons[count].wasLkp = false;

			return aux ;
		}
	}
	return false;
}

bool buttonConfiguration(pin_t button, int type, int time)
{
	int count;
	//I move through the button arrangement and look for the same pin to reconfigure
	for(count=0;count<BUTTON_NUM;count++)
	{
		if(buttons[count].pin == button)
		{
			buttons[count].typefunction=type;
			if(type == LKP)
				buttons[count].lkpTime = time;
			else
				buttons[count].typeTime = time;
			return true;
		}
	}
	//if the pin was not there use an empty space
	for(count=0;count<BUTTON_NUM;count++)
	{
		if(buttons[count].pin==0)
		{
			buttons[count].pin=button;
			buttons[count].typefunction=type;
			if(type == LKP)
				buttons[count].lkpTime = time;
			else
				buttons[count].typeTime = time;
			return true;
		}
	}
	//if there is no empty space for the value
	return false;
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void systick_callback(void)
{

	int i;

	for( i=0 ; i<BUTTON_NUM ; i++ )
	{
		bool pinState = !gpioRead(buttons[i].pin);
		if( buttons[i].lastState && !pinState )
		{
			buttons[i].wasReleased = true;
			buttons[i].wasPressed = false;
			buttons[i].currentCount = 0;
			buttons[i].lastState = false;
		}
		else if( pinState )
		{
			if( buttons[i].typefunction == LKP && (++buttons[i].currentCount) == buttons[i].lkpTime )
			{
				buttons[i].wasLkp = true;
			}
			else if( buttons[i].typefunction == TYPEMATIC && ++buttons[i].currentCount == buttons[i].typeTime)
			{
				 buttons[i].wasPressed= true;
				 buttons[i].currentCount = 0;
			}
			else if(!buttons[i].lastState)
			{
				buttons[i].wasReleased = false;
				buttons[i].wasPressed = true;
				buttons[i].lastState = true;
			}
		}
	}
}
