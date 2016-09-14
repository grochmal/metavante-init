/*---------------------------Includes-----------------------------------*/
#include <portable.h>
#include <stdio.h>
#include <stdlib.h>

#include <sldbg.h>

#include <cortex.h>
#include <condbsvi.h>

/*---------------------------Externs------------------------------------*/
/*---------------------------Macros-------------------------------------*/
/*---------------------------Enums--------------------------------------*/
/*---------------------------Typedefs-----------------------------------*/
/*---------------------------Globals------------------------------------*/
/*---------------------------Statics------------------------------------*/
/*---------------------------Prototypes---------------------------------*/
public int hellonm_init(FILE *fp, char *subsect);
public void hellonm_uninit(void);

/*------------------------------------------------------------------------
 *
 * Functions    : srv_module, srv_name
 *
 * Purpose      : Tuxedo
 *
 * Parameters   :
 *
 * Returns      : As you see
 *
 * Comments     : 
 *
 *----------------------------------------------------------------------*/
public char *srv_module(void) { return "only"; }
public char *srv_name(void) { return "HELLONM"; }

/*------------------------------------------------------------------------
 *
 * Function     : svr_init
 *
 * Purpose      : Tuxedo initialize server by this function
 *
 * Parameters   : FILE *, char *
 *
 * Returns      : SUCCESS / FAIL
 *
 * Comments     : I hope tuxedo do something with this type of return
 *
 *----------------------------------------------------------------------*/
public int srv_init(FILE *fp, char *subsect)
{
	int ret = SUCCEED;

	srv_ndb_dummy();	/* mention this to pull in cosvinit	*/

	ret = hellonm_init(fp, subsect);

	return ret;
}

/*------------------------------------------------------------------------
 *
 * Function     : srv_uninit
 *
 * Purpose      : Tuxedo finish the server
 *
 * Parameters   :
 *
 * Returns      :
 *
 * Comments     : Maybe tuxedo should look for some return from here
 *
 *----------------------------------------------------------------------*/
public void srv_uninit(void)
{
	DBG_PRINTF((dbg_proginfo, "Enter srv_uninit"));

	hellonm_uninit();

	DBG_PRINTF((dbg_proginfo, "Exit srv_uninit"));
}

