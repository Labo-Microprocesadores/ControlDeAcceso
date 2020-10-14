#include <stdio.h>
#include "fsm.h"
#include "fsmtable.h"
#include "states/id_state.h"


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
	{CARD_SWIPE_EV, id, cardRead}
  	{FIN_TABLA,menu,do_nothing}
};


/*** Id ***/

STATE id[]=
{
	{PRESS_EV,id,},
	{ENCODER_RIGHT_EV,id,},
    {ENCODER_LEFT_EV,id,},
	{FIN_TABLA,menu,do_nothing}
};

/*** Pin ***/

STATE pin[] =
{
	{,pin,},
	{,fail,},
    {,usr,},
    {,admin,},
	{FIN_TABLA,main,do_nothing}
};

/*** Fail ***/

STATE fail[] =
{
	{,menu,},
	{,pin,},
	{FIN_TABLA,main,do_nothing}
};


/*** USR ***/

STATE usr[] =
{
	{,cfg_me,},
	{,open,},
	{FIN_TABLA,main,do_nothing}
};

/*** ADMIN ***/

STATE admin[] =
{
	{,cfg_me,},
	{,open,},
    {,add_user,},
    {,cfg_usr,},
    {,cfg_device,},
	{FIN_TABLA,main,do_nothing}
};


/*** OPEN ***/

STATE admin[] =
{
	{,menu,},
	{FIN_TABLA,main,do_nothing}
};



//========interfaz=================


STATE *FSM_GetInitState(void)
{
 	return (ledAzul);



///=========Rutinas de accion===============



/*Dummy function*/
static void do_nothing(void)
{

}