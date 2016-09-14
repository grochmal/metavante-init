/*---------------------------Includes-----------------------------------*/
#include <portable.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sldbg.h>
#include <slfdbg.h>
#include <slclp.h>
#include <slcfp.h>
#include <slnfb.h>
#include <slntp.h>

#include <cortex.h>
#include <cocrd.fd.h>
#include <coint.fd.h>

#include "hellonm.h"
/*---------------------------Externs------------------------------------*/
/*---------------------------Macros-------------------------------------*/
#define DBGNAME "HELLNM"
#define DBGSECT "HELLONM"

/*---------------------------Enums--------------------------------------*/
/*---------------------------Typedefs-----------------------------------*/
/*---------------------------Globals------------------------------------*/
/*---------------------------Prototypes---------------------------------*/
/*---------------------------Statics------------------------------------*/
private int  M_dbglev = dbg_progdetail;	/* debug level			*/
private int  M_dbgbuf = 1;		/* debug buffering ?		*/
private char M_dbgfile[CTX_FILENAME_MAX] = { 0 };	/* debug output name	*/
private bool    M_dbgshowlev=FALSE;

/*---------------------------Prototypes---------------------------------*/
public void HELLONM(TPSVCINFO *p_svc);
public int hellonm_init(FILE *fp, char *subsect);
public void hellonm_uninit(void);

/*--------------------------------------------------------------------------
 *
 * Function	: HELLONM
 *
 * Purpose	: Sevrice for tuxedo
 *
 * Parameters	: Usual for service
 *
 * Returns	: tpreturn
 *
 * Comments	: 
 *
 *------------------------------------------------------------------------*/
public void HELLONM(TPSVCINFO *p_svc)
{
	int	ret = SUCCEED;
	FBFR	*p_fb = NULL;

	p_fb = MAKEBIG (p_svc->data);

	DBG_SETDUMPMODE(p_fb, DUMP_ATSTART);
	DBG_SETNAMEBYPAN(p_fb);
	DBG_SHOWLEV(M_dbgshowlev);
	DBG_STAR(("HELLONM service"));
	DBG_FBDIFFSTARTL(dbg_progdetail, p_fb);

	DBG_PRINTF((dbg_proginfo, "Service declarations ok"));

	ret = hellonm(p_fb);

	DBG_PRINTF((dbg_proginfo, "Exited hellonm with%s problems",
		SUCCEED == ret ? "out" : ""));

	DBG_FBDIFFENDL(dbg_progdetail,p_fb,DIFF_CLOSE);
	DBG_STAR(("ntp_return from : HELLONM"));
	DBG_CLOSEFILE();

	ntp_return((SUCCEED == ret)
		   ? TPSUCCESS
		   : TPFAIL,
		   0L,
		   (char *)p_fb,
		   0L,
		   0L); 
}

/*------------------------------------------------------------------------
 *
 * Function	: hellonm_init
 *
 * Purpose	: Initialisation routine
 *
 * Parameters	: fp - config file
 *		  subsect - subsection in config file
 *
 * Returns	: SUCCEED / FAIL
 *
 * Comments	: Setting up the debug, nothing else to do here now.
 *
 *------------------------------------------------------------------------*/
public int hellonm_init(FILE *fp, char *subsect)
{
	int ret = SUCCEED;

	private cfp_parm cfp[] =
	{
		{"DEBUG",   parm_int, 0, FALSE, (void *)&M_dbglev, 0},
		{0}
	};

	if(SUCCEED != (ret = cfp_parse(fp, cfp, DBGSECT, NULL)))
	{
		fprintf (stderr, "Failed parsing config file.\n");
	}
	else
	{
		DBG_SETNAME(DBGNAME);
		DBG_SETLEV(M_dbglev);

		DBG_PRINTF((dbg_proginfo, "Debug set up"));
	}

	return ret;
}

/*------------------------------------------------------------------------
 *
 * Function	: hellonm_uninit
 *
 * Purpose	: Uninitialisation routine
 *
 * Parameters	: 
 *
 * Returns	: SUCCEED / FAIL
 *
 * Comments	: Using debug to test when the function is executed
 *
 *------------------------------------------------------------------------*/
public void hellonm_uninit(void)
{
	DBG_PRINTF((dbg_proginfo, "Enter hellonm_uninit"));

	return;
}

