#include <stdio.h>
#include "../../fsm.h"
#include "../../../queue.h"
#include "add_user_fsm_table.h"
#include "substates/add_user_main_state.h"
#include "substates/add_user_id_state.h"
#include "substates/add_user_pin_state.h"


/*Foward Declarations*/

extern STATE card[];
extern STATE id[];
extern STATE pin[];

// prototipos
static void do_nothing(void);
static void return_to_last(void);

/*** tablas de estado ***/

/*** Card ***/
STATE card[]=
{
  	{ENCODER_RIGHT_EV, 	card,	return_to_last},
    {ENCODER_LEFT_EV, 	card, 	return_to_last},
    {PRESS_EV, 			card, 	return_to_last},
	{LKP_EV, 			card, 	return_to_last},
	{CARD_SWIPE_EV, 	id, 	cardSwipe},
  	{FIN_TABLA, 		card, 	do_nothing}
};

/*** Id ***/

STATE id[]=
{
	{PRESS_EV, 						id, 	addUserId_acceptNumber},
	{LKP_EV, 						id, 	addUserId_confirmID},
	{ENCODER_RIGHT_EV, 				id, 	addUserId_increaseCurrent},
    {ENCODER_LEFT_EV, 				id, 	addUserId_decreaseCurrent},
	{RETURN_TO_LAST_STATE_EV, 		card, 	addUsr_initState},
	{ID_OK_EV, 						pin, 	addUserPin_initPinInput}, //TODO que updetee el display
	{FIN_TABLA,						id,		do_nothing},
};

/*** Pin ***/

STATE pin[] =
{
	//{,pin,},	    
	{PRESS_EV,						pin, 	addUserPin_acceptNumber},
	{ENCODER_RIGHT_EV,				pin, 	addUserPin_increaseCurrent}, 
    {ENCODER_LEFT_EV,				pin, 	addUserPin_decreaseCurrent},
	{LKP_EV,						pin, 	addUserPin_confirmPin}, 
	{RETURN_TO_LAST_STATE_EV, 		id, 	addUserId_initLogin},
	{FIN_TABLA, 					pin, 	do_nothing}
};



//========interfaz=================


STATE *FSM_GetInitState(void) // cambiar nombre
{
	return(card);
}

///=========Rutinas de accion===============
void FSM_StartInitState() // cambiar nombre
{
	addUsr_initState();
}


/*Dummy function*/
static void do_nothing(void)
{
	//take some time off, relax, and KEEP WORKING ////you lazy ass ALU
}


static void return_to_last(void)
{
	emitEvent(RETURN_TO_LAST_STATE_EV);
}