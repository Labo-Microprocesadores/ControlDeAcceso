#include <stdio.h>
#include "fsm.h"
#include "fsm_table.h"
#include "states/main_menu_state.h"
#include "states/id_state.h"
#include "states/pin_state.h"
// no existe mas #include "states/usr_state.h"
#include "states/admin_state.h"
#include "states/open_state.h"
#include "queue.h"
#include "states/fail_state.h"
#include "states/config_device_state.h"
#include "States/config_me_state.h"
//#include "states/admin_state.h" para open state



/*Foward Declarations*/

extern STATE menu[];
extern STATE id[];
extern STATE pin[];
extern STATE usr[];
extern STATE admin[];
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

 STATE menu[]=
{
  	{ENCODER_RIGHT_EV, 	id,		initLogin},
    {ENCODER_LEFT_EV, 	id, 	initLogin},
    {PRESS_EV, 			id, 	initLogin},
	{LKP_EV, 			id, 	initLogin},
	{CARD_SWIPE_EV, 	id, 	cardSwipe},
  	{FIN_TABLA, 		menu, 	do_nothing}
};


/*** Id ***/

STATE id[]=
{
	{PRESS_EV, 					id, 	id_acceptNumber},
	{LKP_EV, 					id, 	id_confirmID},
	{ENCODER_RIGHT_EV, 			id, 	id_increaseCurrent},
    {ENCODER_LEFT_EV, 			id, 	id_decreaseCurrent},
	{CARD_SWIPE_EV, 			id, 	id_checkCardID},
	{RETURN_TO_LAST_STATE_EV, 	menu, 	showWelcomeAnimation},
	{ID_OK_EV, 					pin, 	initPinInput}, 
	{TIMEOUT_EV, 				menu, 	showWelcomeAnimation},
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
	{PIN_OK_EV, 				admin, 	admin_initAdminMenu},
	{RETURN_TO_LAST_STATE_EV,	id, 	initLogin},
	{FAIL_PIN_EV, 				fail, 	initFailState},
	{TIMEOUT_EV, 				menu, 	showWelcomeAnimation},
	{FIN_TABLA, 				pin, 	do_nothing}
};

/*** Fail ***/
STATE fail[] =
{
	{PRESS_EV,			fail, 	finishFail},
	{ENCODER_RIGHT_EV,	fail,	finishFail}, 
    {ENCODER_LEFT_EV,	fail, 	finishFail}, 
	{TIMEOUT_EV, 		menu, 	showWelcomeAnimation},
	{USR_BLOCKED_EV,	menu,	showWelcomeAnimation},
	{RETRY_PIN_EV, 		pin, 	initPinInput},
	{FIN_TABLA, 		pin, 	do_nothing}
};
/*** USR ***/

/*STATE usr[] =
{
	{PRESS_EV,						usr, 	usr_selectOption},
	{ENCODER_RIGHT_EV, 				usr, 	usr_nextOption}, 
    {ENCODER_LEFT_EV,				usr, 	usr_previousOption}, 
	{USER_CONFIG_ME_SELECTED_EV,	cfg_me, configMe_initState},
	{OPEN_SELECTED_EV,				open,	openDoor},
	{TIMEOUT_EV, 					menu, 	showWelcomeAnimation},
	{LOG_OUT_EV, 					menu, 	showWelcomeAnimation},
	{FIN_TABLA, 					usr, 	do_nothing}
};*/

/*** ADMIN ***/

STATE admin[] =
{	/* Eventos externos */
	{PRESS_EV,							admin, 		admin_selectOption},
	{ENCODER_RIGHT_EV, 					admin, 		admin_nextOption}, 
    {ENCODER_LEFT_EV,					admin, 		admin_previousOption}, 
	/* Eventos de user y admin */ 
	{OPEN_SELECTED_EV,					open,		openDoor},
	{LOG_OUT_EV, 						menu, 		showWelcomeAnimation},
    {CONFIG_ME_SELECTED_EV,				cfg_me,		configMe_initState},
	/* Eventos exclusivos de amin*/ 
	//{ADD_USER_SELECTED_EV,				add_user,			},
    {CONFIG_USER_SELECTED_EV,			cfg_usr,			},
    {CONFIG_DEVICE_SELECTED_EV,			cfg_device,	initConfigDevice},
	{TIMEOUT_EV, 						menu, 		showWelcomeAnimation},
	{FIN_TABLA, 						admin, 		do_nothing}
};

/*** OPEN ***/
STATE open[] =
{
	{TIMER_ACCESS_EV,	menu,	showWelcomeAnimation},
	{FIN_TABLA, 		open, 	do_nothing}
};

/*User config me*/
STATE cfg_me[] = 
{
	{PRESS_EV,					cfg_me, configMe_acceptNumber},
	{ENCODER_RIGHT_EV,			cfg_me, configMe_increaseCurrent}, 
    {ENCODER_LEFT_EV,			cfg_me, configMe_decreaseCurrent},
	{LKP_EV, 					cfg_me, configMe_confirmPin}, 
	{RETURN_TO_LAST_STATE_EV, 	admin,	admin_initAdminMenu},
	{TIMEOUT_EV, 				menu, 	showWelcomeAnimation},
	{FIN_TABLA, 				cfg_me, do_nothing}
};

/*Config usr*/
STATE cfg_usr[] = 
{
	{CONFIG_USER_FINISHED_EV, 			admin,		admin_initAdminMenu},// ver si esta bien la rutina de accion
	{TIMEOUT_EV,				 		menu, 		showWelcomeAnimation},
	{FIN_TABLA, 						cfg_usr, 	do_nothing}
};
/*Config device*/
STATE cfg_device[] = 
{
	{PRESS_EV,							cfg_device, configDev_selectOption},
	{ENCODER_RIGHT_EV, 					cfg_device, configDev_nextOption}, 
    {ENCODER_LEFT_EV,					cfg_device, configDev_previousOption}, 
	{CONFIG_DEVICE_FINISHED_EV,			admin, 		admin_initAdminMenu}, // ver si esta bien la rutina de accion
	{TIMEOUT_EV, 						menu, 		showWelcomeAnimation},
	{FIN_TABLA, 						cfg_device, do_nothing}
};

//========interfaz=================


STATE *FSM_GetInitState(void)
{
	 return(menu);
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
