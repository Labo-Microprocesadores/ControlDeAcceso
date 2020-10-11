/***************************************************************************//**
  @file     7SegDisplay.c
  @brief    Display configurations
  @author   Grupo 2
 ******************************************************************************/


#include "SevenSegDisplay.h"
#include "SysTick.h"
#include "gpio.h"
#include "Timer.h"
#include "board.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define SCREEN_SIZE 4
#define BLINK_TIME 40
#define PERIOD 6

/*************************************************
 *  	LOCAL FUNCTION DECLARATION
 ************************************************/

void SevenSegDisplay_PISR(void);
void SevenSegDisplay_PrintScreen(void);
bool SevenSegDisplay_PrintCharacter(uint8_t character);

/************************************************
 *  	VARIABLES WITH LOCAL SCOPE
 ************************************************/
static uint8_t screen[SCREEN_SIZE] = {NONE, NONE, NONE, NONE};

static pin_t displayPins[SEG_LEN] = {PIN_SEGA, PIN_SEGB, PIN_SEGC, PIN_SEGD,
							 	 	 PIN_SEGE, PIN_SEGF, PIN_SEGG, PIN_SEGDP};
static pin_t selectPins[SEL_LEN] = {PIN_SEL0, PIN_SEL1};

/*
static bool blink[SCREEN_SIZE] = {false, false, fasle};
static bool blinkState[SCREEN_SIZE] = {true, true, true, true};
static uint8_t blinkCounter[SCREEN_SIZE] = {0,0,0,0};
*/
static bool blink = false;
static bool blinkState = true;
static uint8_t blinkCounter = 0;

static uint8_t bright = PERIOD;
static bright_t brightness = MID;
/************************************************
 * 		FUNCTION DEFINITION WITH GLOBAL SCOPE
 ************************************************/
bool SevenSegDisplay_Init(void)
{
	static bool isInit = false;
	if(!isInit)
	{
		SysTick_Init();
		uint8_t count;
		for(count=0; count<SEG_LEN ;count++)
		{
			gpioMode(displayPins[count], OUTPUT);
		}
		for(count=0; count<SEL_LEN ;count++)
		{
			gpioMode(selectPins[count], OUTPUT);
		}
	    //pongo los 2 pin a demultiplexar en 00 para que solo se prenda un 7segmentos
	    gpioWrite (selectPins[0], false);
	    gpioWrite (selectPins[1], false);

		int systickCallbackID = SysTick_AddCallback(&SevenSegDisplay_PISR, 1); //1ms
		if (systickCallbackID < 0 ) // Error
		{
			return false;
		}
	//idCounter = 1;
	}
	return true;
}


bool SevenSegDisplay_ChangeCharacter(uint8_t screen_char, uint8_t new_char)
{
	if (screen_char < SCREEN_SIZE)
	{
		screen[screen_char] = new_char;
	}
	return true;
}

bool SevenSegDisplay_ToggleBlinkScreen(void)
{
	blink = !blink;
	blinkCounter = blink ? BLINK_TIME:0;
	return true;
}

void SevenSegDisplay_SetBright(bright_t new_bright)
{
	brightness = new_bright;
}

void SevenSegDisplay_EraseScreen(void)
{
	for(int i = 1; i<((int)(sizeof(screen)/sizeof(screen[0]))); i++)
	{
		screen[i] = NONE;
	}
}

/**************************************************
 * 			LOCAL FUNCTIONS DEFINITIONS
 **************************************************/

bool SevenSegDisplay_PrintCharacter(uint8_t character)
{
	int count;

	for(count=0; count<SEG_LEN; count++)
	{
		gpioWrite(displayPins[count], (character & (1<<count)) != 0);
	}
	return 0;
}

void SevenSegDisplay_PISR(void)
{
	if(blink)
	{
		if(--blinkCounter == 0)
		{
			blinkState = !blinkState;
			blinkCounter = PERIOD*BLINK_TIME;
		}
	}
	SevenSegDisplay_PrintScreen();
}

void SevenSegDisplay_PrintScreen(void)
{
	static uint8_t displayCounter = 0;
	static int8_t curr = MIN;
	//static uint8_t prev_data = 0;

	uint8_t dataToPrint = (blinkState && (curr > 0)) ? screen[displayCounter]: NONE;

	SevenSegDisplay_PrintCharacter(dataToPrint);

	curr--;
	bright--;
	if (bright == 0)
	{
		curr = brightness;
		bright = PERIOD;
		displayCounter++;

		if(displayCounter == SCREEN_SIZE){displayCounter = 0;}

		gpioWrite(selectPins[0], (displayCounter & (1   )) != 0);
		gpioWrite(selectPins[1], (displayCounter & (1<<1)) != 0);
	}

}


