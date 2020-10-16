/***************************************************************************//**
  @file     seven_seg_display.c
  @brief    7 Segment Display Header
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

#ifndef SEVENSEGDISPLAY_H_
#define SEVENSEGDISPLAY_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define NONE			(uint8_t)0x00
#define ZERO			(uint8_t)0x3F
#define ONE				(uint8_t)0x06
#define TWO				(uint8_t)0x5B
#define THREE			(uint8_t)0x4F
#define FOUR			(uint8_t)0x66
#define FIVE			(uint8_t)0x6D
#define SIX				(uint8_t)0x7D
#define SEVEN			(uint8_t)0x07
#define EIGHT			(uint8_t)0x7F
#define NINE			(uint8_t)0x6F
#define LINE			(uint8_t)0x08
#define I				(uint8_t)0x30				
#define D				(uint8_t)0x5D
#define P				(uint8_t)0x73
#define N				(uint8_t)0x37
#define C				(uint8_t)0x39
#define F				(uint8_t)0x71
#define G				(uint8_t)0x3D
#define H				(uint8_t)0x76

#define MASK			(uint8_t)0x01

#define CHARS 			{ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, LINE, NONE, I, D, P, N, C, F, G, H}

#define SEG_LEN			8
#define SEL_LEN			2

#define RESET_BLINK 	-1

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef enum {
	MAX = 5,
	MID = 3,
	MIN = 1
}bright_t;


typedef  struct
{
	uint8_t character;
	bool blink;
	bool blinkState;
	uint8_t blinkCounter;
}sevenSeg_t;

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Initialize 7 Segment Display driver
 */
bool SevenSegDisplay_Init(void);

/**
 * @brief Set a character in a display position
 * @param screen_char: screen position, new_char: character to print
 */
void SevenSegDisplay_ChangeCharacter(uint8_t screen_char, uint8_t new_char);

/*
 * @brief Clean screen
 */
void SevenSegDisplay_EraseScreen(void);

/**
 * @brief places all digits on the state passed as a function parameter
 * @param state, true for blink digits
 * @return blink succeed, false if there was an error
 */
bool SevenSegDisplay_BlinkScreen(bool state);

/**
 * @brief select a digit to blink or reset blinks
 * @param digit, the number that corresponds to the 7segments display
 * @return blink succeed, false if there was an error with the digit
 */
bool SevenSegDisplay_BlinkCharacter(uint8_t digit);

/**
 * @brief Change display brightness between MAX, MID, MIN
 * @param new_bright: brightness to set
 */
void SevenSegDisplay_SetBright(bright_t new_bright);


#endif /* SEVENSEGDISPLAY_H_ */
