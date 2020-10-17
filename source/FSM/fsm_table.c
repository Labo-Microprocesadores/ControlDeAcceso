#include <stdio.h>
#include "fsm.h"
#include "fsm_table.h"
#include "states/main_menu_state.h"
#include "states/id_state.h"
#include "states/pin_state.h"
#include "states/fail_state.h"
#include "states/usr_state.h"
#include "states/admin_state.h"
#include "states/open_state.h"
#include "../queue.h"
//#include "states/admin_state.h" para open state



/*Foward Declarations*/

extern STATE menu[];
extern STATE id[];
extern STATE pin[];
extern STATE fail[];
extern STATE usr[];
extern STATE admin[];
extern STATE cfg_me[];
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
	{ID_OK_EV, pin, onId_Ok}, //TODO que updetee el display
	{ID_FAIL_EV, id, id_fail}, //TODO ver si tieneque ir directo a menu o no
	{FIN_TABLA,id,do_nothing},
};

/*** Pin ***/

STATE pin[] =
{
	//{,pin,},	    
	{PRESS_EV,pin, pin_acceptNumber},
	{ENCODER_RIGHT_EV,pin, pin_increaseCurrent}, 
    {ENCODER_LEFT_EV,pin, pin_decreaseCurrent}, 
	{USR_PIN_OK_EV, usr,},
    {ADMIN_PIN_OK_EV, admin,},
	{PIN_FAIL_EV, fail,},
	{FIN_TABLA, pin, do_nothing}
};

/*** Fail ***/

STATE fail[] =
{
	{NO_ATT_EV, menu, blockUsr},
	{HAS_ATT_EV, pin, hasAttempsLeft},
	{FIN_TABLA, fail, do_nothing}
};


/*** USR ***/

STATE usr[] =
{
	{USER_CONFIG_ME_SELECTED_EV,cfg_me,},
	{OPEN_SELECTED_EV,open,openDoor},
	{FIN_TABLA, usr, do_nothing}
};

/*** ADMIN ***/

STATE admin[] =
{
	{ADMIN_CONFIG_ME_SELECTED_EV,cfg_me,},
	{OPEN_SELECTED_EV,open,openDoor},
    {ADMIN_ADD_USER_SELECTED_EV,add_user,},
    {ADMIN_CONFIG_USER_SELECTED_EV,cfg_usr,},
    {ADMIN_CONFIG_DEVICE_SELECTED_EV,cfg_device,},
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
	{ADMIN_CONFIG_ME_FINISHED_EV, admin,}
	{USER_CONFIG_ME_FINISHED_EV, usr,}
	{FIN_TABLA, cfg_me, do_nothing}
}

/*Config usr*/
STATE cfg_usr[] = 
{
	{ADMIN_CONFIG_USER_FINISHED_EV, admin,}
	{FIN_TABLA, cfg_usr, do_nothing}
}
/*Config device*/
STATE cfg_device[] = 
{
	{ADMIN_CONFIG_DEVICE_FINISHED_EV, admin,}
	{FIN_TABLA, cfg_usr, do_nothing}
}

//========interfaz=================


STATE *FSM_GetInitState(void)
{
	 return(menu);
}

///=========Rutinas de accion===============



/*Dummy function*/
static void do_nothing(void)
{
	//take some time off, relax, and KEEP WORKING you lazy ass ALU
}

static void onId_Ok(void)
{
	//TODO que updetee el display
}