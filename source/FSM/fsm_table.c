#include <stdio.h>
#include <States/menu_state.h>
#include <States/welcome_state.h>
#include "fsm.h"
#include "fsm_table.h"
#include "states/id_state.h"
#include "states/pin_state.h"
// no existe mas #include "states/usr_state.h"
#include "states/open_state.h"
#include "queue.h"
#include "states/fail_state.h"
#include "states/config_device_state.h"
#include "States/config_me_state.h"
//#include "states/admin_state.h" para open state



/*Foward Declarations*/

extern STATE welcome[];
extern STATE id[];
extern STATE pin[];
extern STATE usr[];
extern STATE menu[];
extern STATE cfg_me[];
extern STATE fail[];
extern STATE cfg_usr[];
extern STATE cfg_device[];
extern STATE add_user[];
extern STATE open[];


// prototipos
static void do_nothing(void);

/*** tablas de estado ***/

/*** menu ***/

 STATE welcome[]=
{
  	{ENCODER_RIGHT_EV, 	id,		initLogin},
    {ENCODER_LEFT_EV, 	id, 	initLogin},
    {PRESS_EV, 			id, 	initLogin},
	{LKP_EV, 			id, 	initLogin},
	{CARD_SWIPE_EV, 	id, 	cardSwipe},
  	{FIN_TABLA, 		welcome, 	do_nothing}
};


/*** Id ***/

STATE id[]=
{
	{PRESS_EV, 					id, 	id_acceptNumber},
	{LKP_EV, 					id, 	id_confirmID},
	{ENCODER_RIGHT_EV, 			id, 	id_increaseCurrent},
    {ENCODER_LEFT_EV, 			id, 	id_decreaseCurrent},
	{CARD_SWIPE_EV, 			id, 	id_checkCardID},
	{RETURN_TO_LAST_STATE_EV, 	welcome, 	showWelcomeAnimation},
	{ID_OK_EV, 					pin, 	initPinInput}, 
	{TIMEOUT_EV, 				welcome, 	showWelcomeAnimation},
	{FIN_TABLA,					id,		do_nothing},
};

/*** Pin ***/

STATE pin[] =
{
	//{,pin,},	    
	{PRESS_EV,					pin, 	pin_acceptNumber},
	{ENCODER_RIGHT_EV,			pin, 	pin_increaseCurrent}, 
    {ENCODER_LEFT_EV,			pin, 	pin_decreaseCurrent},
	{LKP_EV, 					pin, 	pin_confirmPin}, 
	{PIN_OK_EV, 				menu, 	menu_initState},
	{RETURN_TO_LAST_STATE_EV,	id, 	initLogin},
	{FAIL_PIN_EV, 				fail, 	initFailState},
	{TIMEOUT_EV, 				welcome, 	showWelcomeAnimation},
	{FIN_TABLA, 				pin, 	do_nothing}
};

/*** Fail ***/
STATE fail[] =
{
	{PRESS_EV,			fail, 	finishFail},
	{ENCODER_RIGHT_EV,	fail,	finishFail}, 
    {ENCODER_LEFT_EV,	fail, 	finishFail}, 
	{TIMEOUT_EV, 		welcome, 	showWelcomeAnimation},
	{USR_BLOCKED_EV,	welcome,	showWelcomeAnimation},
	{RETRY_PIN_EV, 		pin, 	initPinInput},
	{FIN_TABLA, 		pin, 	do_nothing}
};

/*** MENU ***/

STATE menu[] =
{	/* Eventos externos */
	{PRESS_EV,							menu, 		menu_selectOption},
	{ENCODER_RIGHT_EV, 					menu, 		menu_nextOption}, 
    {ENCODER_LEFT_EV,					menu, 		menu_previousOption}, 
	/* Eventos de user y admin */ 
	{OPEN_SELECTED_EV,					open,		openDoor},
	{LOG_OUT_EV, 						welcome, 		showWelcomeAnimation},
    {CONFIG_ME_SELECTED_EV,				cfg_me,		configMe_initState},
	/* Eventos exclusivos de amin*/ 
	//{ADD_USER_SELECTED_EV,				add_user,			},
    {CONFIG_USER_SELECTED_EV,			cfg_usr,			},
    {CONFIG_DEVICE_SELECTED_EV,			cfg_device,	initConfigDevice},
	{TIMEOUT_EV, 						welcome, 		showWelcomeAnimation},
	{FIN_TABLA, 						menu, 		do_nothing}
};

/*** OPEN ***/
STATE open[] =
{
	{TIMER_ACCESS_EV,	welcome,	showWelcomeAnimation},
	{FIN_TABLA, 		open, 	do_nothing}
};

/*User config me*/
STATE cfg_me[] = 
{
	{PRESS_EV,					cfg_me, configMe_acceptNumber},
	{ENCODER_RIGHT_EV,			cfg_me, configMe_increaseCurrent}, 
    {ENCODER_LEFT_EV,			cfg_me, configMe_decreaseCurrent},
	{LKP_EV, 					cfg_me, configMe_confirmPin}, 
	{RETURN_TO_LAST_STATE_EV, 	menu,	menu_initState},
	{TIMEOUT_EV, 				welcome, 	showWelcomeAnimation},
	{FIN_TABLA, 				cfg_me, do_nothing}
};

/*Config usr*/
STATE cfg_usr[] = 
{
	{CONFIG_USER_FINISHED_EV, 			menu,		menu_initState},// ver si esta bien la rutina de accion
	{TIMEOUT_EV,				 		welcome, 		showWelcomeAnimation},
	{FIN_TABLA, 						cfg_usr, 	do_nothing}
};
/*Config device*/
STATE cfg_device[] = 
{
	{PRESS_EV,							cfg_device, configDev_selectOption},
	{ENCODER_RIGHT_EV, 					cfg_device, configDev_nextOption}, 
    {ENCODER_LEFT_EV,					cfg_device, configDev_previousOption}, 
	{CONFIG_DEVICE_FINISHED_EV,			menu, 		menu_initState}, // ver si esta bien la rutina de accion
	{TIMEOUT_EV, 						welcome, 		showWelcomeAnimation},
	{FIN_TABLA, 						cfg_device, do_nothing}
};

//========interfaz=================


STATE *FSM_GetInitState(void)
{
	 return(welcome);
}

///=========Rutinas de accion===============
void FMS_StartInitState()
{
	showWelcomeAnimation();
}


/*Dummy function*/
static void do_nothing(void)
{
	//take some time off, relax, and KEEP WORKING ////you lazy ass ALU
}
