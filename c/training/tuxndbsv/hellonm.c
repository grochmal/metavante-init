/*---------------------------Includes-----------------------------------*/
#include <portable.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sldbg.h>
#include <slfdbg.h>
#include <slclp.h>
#include <slcfp.h>
#include <slnfb.h>
#include <slntp.h>

#include <cortex.h>
#include <coint.fd.h>

/*---------------------------Externs------------------------------------*/
/*---------------------------Macros-------------------------------------*/
/*---------------------------Enums--------------------------------------*/
/*---------------------------Typedefs-----------------------------------*/
/*---------------------------Globals------------------------------------*/
/*---------------------------Prototypes---------------------------------*/
/*---------------------------Statics------------------------------------*/
/*---------------------------Prototypes---------------------------------*/
public int hellonm(FBFR *p_fb);

/*--------------------------------------------------------------------------
 *
 * Function	: hellonm
 *
 * Purpose	: print "Hello $user" using tuxedo
 *
 * Parameters	: ptp_fb - pointer to fielded buffer
 *
 * Returns	: SUCCEED / FAIL
 *
 * Comments	: 
 *
 *------------------------------------------------------------------------*/
public int hellonm(FBFR *p_fb)
{
	int ret = SUCCEED;
	char name[10], msg[15];

	if (SUCCEED != (ret = Fget32(p_fb, I_USR, 0, name, 0)))
		DBG_PRINTF((dbg_syserr, "F_get I_USR failed %s",
			Fstrerror32(Ferror32)));
	else
	{
		DBG_PRINTF((dbg_proginfo, "Reading message"));

		strcat(msg, name);

		DBG_PRINTF((dbg_proginfo, "Trying to F_chg"));

		if(SUCCEED != (ret = Fchg32(p_fb, I_MSGSTR, 0, msg, 0)))
			DBG_PRINTF((dbg_syserr, "F_chg I_MSGSTR failed %s",
				Fstrerror32(Ferror32)));
		else
			DBG_PRINTF((dbg_proginfo, "All went well"));
	}

	return ret;
}

