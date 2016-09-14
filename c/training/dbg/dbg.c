/*---------------------------Includes-----------------------------------------*/
#include <portable.h>
#include <stdio.h>	/* sprintf, sscanf, etc. */
#include <string.h>	/* strcmp, strcat, etc. */
#include <stdlib.h>	/* Standard Library */

/* Cortex stdlib */
#include <sldbg.h>	/* DBG_PRINTF, etc. */

#include <cortex.h>	/* Cortex #definitions */
/*---------------------------Externs------------------------------------------*/
/*---------------------------Macros-------------------------------------------*/
/*---------------------------Enums--------------------------------------------*/
/*---------------------------Typedefs-----------------------------------------*/
/*---------------------------Globals------------------------------------------*/
/*---------------------------Statics------------------------------------------*/
/*---------------------------Prototypes---------------------------------------*/

#define TAGNAME		"DBGTEST"

private	int	M_dbglev = dbg_proginfo;	/* Debug trace output level */
private	int	M_dbgbuf = 0;			/* Debug buffering level */
private	char	M_dbgfile[CTX_FILENAME_MAX] = "logs/dbgDetails.log";	/* Debug filename */
/*------------------------------------------------------------------------------
 *
 * Function	:  main
 *
 * Purpose	:  main function
 *
 * Parameters	:  argc, argv - Usual Suspects
 *
 * Returns	:  SUCCEED / FAIL
 *
 * Comments	:  
 *
 *----------------------------------------------------------------------------*/
public int main(int argc, char **argv)
{
	int	ret = SUCCEED;



	if( SUCCEED == ret )
	{
		DBG_SETFILE(M_dbgfile);
		DBG_SETLEV(M_dbglev);
		DBG_SETBUF(M_dbgbuf);
		DBG_SETNAME(TAGNAME);
	}

	/* functionality */

	DBG_PRINTF((dbg_progdetail,"Hello there"));

	DBG_ENTRY("Entering Some Directory");

	DBG_PRINTF((dbg_proginfo, "The Name:"));

	DBG_PRINTF((dbg_proginfo, DBG_GETNAME()));

	DBG_SETNAME("DBGNAME");

	DBG_PRINTF((dbg_proginfo, "The Name:"));

	DBG_PRINTF((dbg_proginfo, DBG_GETNAME()));

	return ret;
}
