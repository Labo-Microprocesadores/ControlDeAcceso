#include <stdio.h>
#include "fsm.h"
#include "fsm_table.h"
#include "states/main_menu_state.h"
#include "states/id_state.h"
#include "states/pin_state.h"
#include "states/fail_state.h"
#include "states/usr_state.h"
#include "states/admin_state.h"
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
  	{FIN_TABLA,menu,do_nothing}
};


/*** Id ***/

STATE id[]=
{
	{PRESS_EV, id, id_acceptNumber},
	{LKP_EV, id, confirmID},
	{ENCODER_RIGHT_EV, id, id_increaseCurrent},
    {ENCODER_LEFT_EV, id, id_decreaseCurrent},
	{CARD_SWIPE_EV, id, checkCardID},
	{FIN_TABLA,id,do_nothing},
	{ID_OK_EV, pin, id_updateDispPin} //TODO que updetee el display
	{ID_FAIL_EV, id, } //TODO ver si tieneque ir directo a menu o no
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
	{,cfg_me,},
	{,open,},
	{FIN_TABLA, usr, do_nothing}
};

/*** ADMIN ***/

STATE admin[] =
{
	{,cfg_me,},
	{,open,},
    {,add_user,},
    {,cfg_usr,},
    {,cfg_device,},
	{FIN_TABLA, admin, do_nothing}
};


/*** OPEN ***/

STATE open[] =
{
	{,menu,},
	{FIN_TABLA, open, do_nothing}
};



//========interfaz=================


STATE *FSM_GetInitState(void)
{
 	return (ledAzul);



///=========Rutinas de accion===============



/*Dummy function*/
static void do_nothing(void)
{
	//take some time off, relax, and KEEP WORKING you lazy ass ALU
}