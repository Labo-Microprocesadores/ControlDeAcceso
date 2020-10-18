#include <stdio.h>
#include "fsm.h"
#include "fsm_table.h"
#include "states/main_menu_state.h"
#include "states/id_state.h"
#include "states/pin_state.h"
#include "states/usr_state.h"
#include "states/admin_state.h"
#include "states/open_state.h"
#include "queue.h"
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
  	{ENCODER_RIGHT_EV, id ,initLogin},
    {ENCODER_LEFT_EV, id, initLogin},
    {PRESS_EV, id, initLogin},
	{LKP_EV, id, initLogin},
	{CARD_SWIPE_EV, id, cardRead},
  	{FIN_TABLA, menu, do_nothing}
};


/*** Id ***/

STATE id[]=
{
	{PRESS_EV, id, id_acceptNumber},
	{LKP_EV, id, id_confirmID},
	{ENCODER_RIGHT_EV, id, id_increaseCurrent},
    {ENCODER_LEFT_EV, id, id_decreaseCurrent},
	{CARD_SWIPE_EV, id, id_checkCardID},
	{RETURN_TO_LAST_STATE_EV, menu, showWelcomeAnimation},
	{ID_OK_EV, pin, initPinInput}, //TODO que updetee el display
	{TIMEOUT_EV, menu, showWelcomeAnimation},
	{FIN_TABLA,id,do_nothing},
};

/*** Pin ***/

STATE pin[] =
{
	//{,pin,},	    
	{PRESS_EV,pin, pin_acceptNumber},
	{ENCODER_RIGHT_EV,pin, pin_increaseCurrent}, 
    {ENCODER_LEFT_EV,pin, pin_decreaseCurrent}, 
	{USR_PIN_OK_EV, usr, initUserMenu},
    {ADMIN_PIN_OK_EV, admin, initAdminMenu},
	{RETURN_TO_LAST_STATE_EV, id, initLogin},
	{FAIL_PIN_EV, fail, initFailState},
	{TIMEOUT_EV, menu, showWelcomeAnimation},
	{FIN_TABLA, pin, do_nothing}
};

/*** Fail ***/
STATE fail[] =
{
	{PRESS_EV,fail, finishFail},
	{ENCODER_RIGHT_EV,fail, finishFail}, 
    {ENCODER_LEFT_EV,fail, finishFail}, 
	{TIMEOUT_EV, menu, showWelcomeAnimation},
	{FIN_TABLA, pin, do_nothing}
};
/*** USR ***/

STATE usr[] =
{
	{USER_CONFIG_ME_SELECTED_EV,cfg_me,},
	{OPEN_SELECTED_EV,open,openDoor},
	{TIMEOUT_EV, menu, showWelcomeAnimation},
	{FIN_TABLA, usr, do_nothing}
};

/*** ADMIN ***/

STATE admin[] =
{
	////{ADMIN_CONFIG_ME_SELECTED_EV,cfg_me,},
	{OPEN_SELECTED_EV,open,openDoor},
    ////{ADMIN_ADD_USER_SELECTED_EV,add_user,},
    ////{ADMIN_CONFIG_USER_SELECTED_EV,cfg_usr,},
    ////{ADMIN_CONFIG_DEVICE_SELECTED_EV,cfg_device,initConfigDevice},
	{TIMEOUT_EV, menu, showWelcomeAnimation},
	{FIN_TABLA, admin, do_nothing}
};

/*** OPEN ***/
STATE open[] =
{
	{TIMER_ACCESS_EV,menu,accessTimeOut},
	{FIN_TABLA, open, do_nothing}
};

/*User config me*/
STATE cfg_me[] = 
{
	////{ADMIN_CONFIG_ME_FINISHED_EV, admin,initAdminMenu},
	{USER_CONFIG_ME_FINISHED_EV, usr,initUserMenu},
	{TIMEOUT_EV, menu, showWelcomeAnimation},
	{FIN_TABLA, cfg_me, do_nothing}
};

/*Config usr*/
STATE cfg_usr[] = 
{
	{ADMIN_CONFIG_USER_FINISHED_EV, usr,initUserMenu},// ver si esta bien la rutina de accion
	{TIMEOUT_EV, menu, showWelcomeAnimation},
	{FIN_TABLA, cfg_usr, do_nothing}
};
/*Config device*/
STATE cfg_device[] = 
{
	/////{ADMIN_CONFIG_DEVICE_FINISHED_EV, admin, initAdminMenu}, // ver si esta bien la rutina de accion
	{TIMEOUT_EV, menu, showWelcomeAnimation},
	{FIN_TABLA, cfg_device, do_nothing}
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
