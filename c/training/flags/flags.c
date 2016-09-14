/*---------------------------Includes-----------------------------------------*/
#include <portable.h>
#include <stdio.h>	/* sprintf, sscanf, etc. */
#include <string.h>	/* strcmp, strcat, etc. */
#include <stdlib.h>	/* Standard Library */

/* Cortex stdlib */
#include <sldbg.h>	/* DBG_PRINTF, etc. */
#include <slclp.h>	/* Parse command line */
#include <slcfp.h>	/* Parse config file */

#include <cortex.h>	/* Cortex #definitions */
#include <cocbfdef.h>	/* Card based #definitions */

/*---------------------------Externs------------------------------------------*/
/*---------------------------Macros-------------------------------------------*/
/*---------------------------Enums--------------------------------------------*/
/*---------------------------Typedefs-----------------------------------------*/
/*---------------------------Globals------------------------------------------*/
/*---------------------------Statics------------------------------------------*/
/*---------------------------Prototypes---------------------------------------*/

#define TAGNAME		"FLAG_SECTION"

private	int	M_dbglev = dbg_proginfo;	/* Debug trace output level */
private	int	M_dbgbuf = 0;			/* Debug buffering level */
private	char	M_dbgfile[CTX_FILENAME_MAX];	/* Debug filename */
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
static	char	boolArg[6];
static	bool	passedBool;
static	flag	flagInFile = FALSE;

static	clp_parm clp[]=
	{
		{'b', parm_string, 6, TRUE, boolArg, 0},
		{0}
	};

static	cfp_parm cfp[] =
        {
		{"ISTRUE", parm_trueflag, 0, FALSE, (void *)&flagInFile, 0},
		{0}
	};

	if(3 != argc)
	{
		fputs("Usage: flags -b <TRUE | FALSE>", stdout);
		return 0;
	}

	if( SUCCEED != (ret = clp_parse(argc, argv, clp)) )
	{
		fprintf(stderr, "Failed to parse command line\n");
	}
	else if( SUCCEED != (ret = cfp_lite(cfp, TAGNAME, NULL /*subsect*/)) )
	{
		fprintf(stderr, "Failed to parse configuration file\n");
	}

	if( SUCCEED == ret )
	{
	/*	DBG_SETFILE(M_dbgfile);*/
		DBG_SETLEV(M_dbglev);
		DBG_SETBUF(M_dbgbuf);
	}

	if(0 == strcmp(boolArg, "TRUE"))
		passedBool = TRUE;
	else
		passedBool = FALSE;
	/* functionality */

	printf("You inserted the boolean: %s\n", TRUE == passedBool ? "True" : "False");
	printf("in the config file the flag is set to: %s\n", TRUE == flagInFile ?
		"True": "False");

	return ret;
}
