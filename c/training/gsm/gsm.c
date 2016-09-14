/*---------------------------Includes-----------------------------------------*/
#include <portable.h>
#include <stdio.h>	/* sprintf, sscanf, etc. */
#include <string.h>	/* strcmp, strcat, etc. */
#include <stdlib.h>	/* Standard Library */

/* Cortex stdlib */
#include <sldbg.h>	/* DBG_PRINTF, etc. */
#include <slgsm.h>	/* date/time functions */
#include <slcfp.h>	/* Parse config file */

/*---------------------------Externs------------------------------------------*/
/*---------------------------Macros-------------------------------------------*/
#define	DBGTAG	"DEBUG"
#define DBGNAME	"SmSmall"

#define CMD_LINE_SIZE	80
#define MAX_CMDL_ITEMS	3
#define MIN_CMDL_ITEMS	1

/*---------------------------Enums--------------------------------------------*/
enum states
{
	st_read,
	st_parse,
	st_error,
	st_sum,
	st_dif,
	st_exit
};

enum events
{
	ev_ok,
	ev_error,
	ev_sum,
	ev_dif,
	ev_exit
};

/*---------------------------Typedefs-----------------------------------------*/
/*---------------------------Globals------------------------------------------*/
/*---------------------------Statics------------------------------------------*/
private void	*M_p_mc = NULL;
private	int	M_dbglev = dbg_progdetail;	/* Debug trace output level */
private	int	M_dbgbuf = 0;			/* Debug buffering level */
private	char	M_dbgfile[CTX_FILENAME_MAX];	/* Debug filename */
private char	M_dbgname[CTX_FILENAME_MAX] = "gsm_debug";

static char	cmdLine[CMD_LINE_SIZE];
static int	firstNum;
static int	secondNum;

/*---------------------------Prototypes---------------------------------------*/
private int sm_init(void);
private int sm_initDbg(void);
private void sm_main(void);
private short sm_read(void);
private short sm_parse(void);
private short sm_error(void);
private short sm_sum(void);
private short sm_dif(void);
private short sm_exit(void);

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
 * Comments	:  Simple as possible.
 *
 *----------------------------------------------------------------------------*/
public int main(int argc, char **argv)
{
	int ret;

	ret = sm_initDbg();

	if(FAIL != ret)
		ret = sm_init();

	if(FAIL != ret)
		sm_main();

	return SUCCEED == ret ? 0 : 1;
}

/*------------------------------------------------------------------------------
 *
 * Function	: sm_initDbg
 *
 * Purpose	: Initialize the debug options
 *
 * Parameters	: 
 *
 * Returns	: SUCCEED / FAIL
 *
 * Comments	: Makes the main function cleaner without the debug lines
 *
 *----------------------------------------------------------------------------*/
private int sm_initDbg(void)
{
	int ret = SUCCEED;

	private cfp_parm cfp[] =
	{
		{"DEBUG", parm_int, 0, FALSE, &M_dbglev, 0},
		{0}
	};

	if(SUCCEED != (ret = cfp_lite(cfp, DBGTAG, NULL)))
		fputs("Failed debug initialization, cannot continue", stderr);

	if(SUCCEED == ret)
	{
		DBG_SETNAME(DBGNAME);
		DBG_SETLEV(M_dbglev);
	}

	return ret;
}

/*------------------------------------------------------------------------------
 *
 * Function	: sm_init
 *
 * Purpose	: Initialize the state machine
 *
 * Parameters	: 
 *
 * Returns	: SUCCEED / FAIL
 *
 * Comments	: Pass all the tables to the state machine
 *
 *----------------------------------------------------------------------------*/
private int sm_init(void)
{
	int ret = SUCCEED;

	private gsm_states states[] =
	{
		{GST(st_read),	sm_read,	st_parse,	NULL},
		{GST(st_parse),	sm_parse,	st_error,	NULL},
		{GST(st_error),	sm_error,	st_read,	NULL},
		{GST(st_sum),	sm_sum,		st_read,	NULL},
		{GST(st_dif),	sm_dif,		st_read,	NULL},
		{GST(st_exit),	sm_exit,	0,		GSM_RETURN}
	};

	private gsm_trans transfers[] =
	{
		{st_read,	GEV(ev_ok),	NULL,	st_parse},
		{st_parse,	GEV(ev_error),	NULL,	st_error},
		{st_parse,	GEV(ev_sum),	NULL,	st_sum},
		{st_parse,	GEV(ev_dif),	NULL,	st_dif},
		{st_parse,	GEV(ev_exit),	NULL,	st_exit},
		{st_error,	GEV(ev_ok),	NULL,	st_read},
		{st_sum,	GEV(ev_ok),	NULL,	st_read},
		{st_dif,	GEV(ev_ok),	NULL,	st_read},
		{FAIL}
	};
	
	DBG_PRINTF((dbg_proginfo, "Entered sm_init"));

	if(FAIL != ret)
		if(FAIL == (ret = gsm_new(states, DIM(states)-1, transfers,
			&M_p_mc)))
			DBG_PRINTF((dbg_syserr, "Initialization failed"));

	return ret;
}

/*------------------------------------------------------------------------------
 *
 * Function	: sm_main
 *
 * Purpose	: Start state machine
 *
 * Parameters	: 
 *
 * Returns	:
 *
 * Comments	: Also print something about usage of the prog
 *
 *----------------------------------------------------------------------------*/
private void sm_main(void)
{
	DBG_PRINTF((dbg_proginfo, "Entered sm_main"));

	fputs("Usage:\n>> + <num1> <num2>; To sum numbers.\n", stdout);
	fputs(">> - <num1> <num2>; To dif numbers.\n", stdout);
	fputs(">> q ; To exit.\n", stdout);
	
	gsm_enter(M_p_mc, st_read);

	return;
}

/*------------------------------------------------------------------------------
 *
 * Function	: sm_read
 *
 * Purpose	: Read a command line and sets it on cmdLine
 *
 * Parameters	: 
 *
 * Returns	: ev_ok
 *
 * Comments	: Only read does not parse nothing
 *
 *----------------------------------------------------------------------------*/
private short sm_read(void)
{
	short ret = ev_ok;

	gsm_debug(M_p_mc, TRUE, "Trying SM debug");

	DBG_PRINTF((dbg_proginfo, "Before this was called sm debug"));

	printf("\n>> ");

	fgets(cmdLine, CMD_LINE_SIZE, stdin);

	cmdLine[strlen(cmdLine) - 1] = EOS;

	return ret;
}

/*------------------------------------------------------------------------------
 *
 * Function	: sm_parse
 *
 * Purpose	: parse command line read by sm_read
 *
 * Parameters	: 
 *
 * Returns	: ev_error, ev_sum, ev_dif, ev_exit
 *
 * Comments	: Actual choices inside the state machine
 *
 *----------------------------------------------------------------------------*/
private short sm_parse(void)
{
	short ret = ev_error;
	int items;
	char cmd;

	DBG_PRINTF((dbg_proginfo, "Starting Parsing"));

	if(MAX_CMDL_ITEMS == (items =
		sscanf(cmdLine, "%c %d %d", &cmd, &firstNum, &secondNum)))
	{
		DBG_PRINTF((dbg_proginfo, "Read command line with 3 items"));

		if('+' == cmd) /* command is +, a sum */
		{
			DBG_PRINTF((dbg_proginfo, "Make a sum"));

			ret = ev_sum;
		}

		else if('-' == cmd) /* command is -, a dif */
		{
			DBG_PRINTF((dbg_proginfo, "Make a dif"));

			ret = ev_dif;
		}
	}

	else if(MIN_CMDL_ITEMS == items)
	{
		DBG_PRINTF((dbg_proginfo, "Read command line with 1 item"));

		if(MIN_CMDL_ITEMS == strlen(cmdLine) && 'q' == cmd)
		{
			DBG_PRINTF((dbg_proginfo, "The user quits"));

			ret = ev_exit;
		}
	}

	return ret;
}

/*------------------------------------------------------------------------------
 *
 * Function	: sm_error
 *
 * Purpose	: Reprint usage form for the user that failed the cmd line
 *
 * Parameters	: 
 *
 * Returns	: ev_ok
 *
 * Comments	: Anything that isn't recognized by the command line
 *		ends here
 *
 *----------------------------------------------------------------------------*/
private short sm_error(void)
{
	short ret = ev_ok;

	DBG_PRINTF((dbg_proginfo, "Error parsing cmd line, printing usage"));

	fputs("Usage:\n>> + <num1> <num2>; To sum numbers.\n", stdout);
	fputs(">> - <num1> <num2>; To dif numbers.\n", stdout);
	fputs(">> q ; To exit.\n", stdout);
	
	return ret;
}

/*------------------------------------------------------------------------------
 *
 * Function	: sm_sum
 *
 * Purpose	: Sum values in firstNum and secondNum
 *
 * Parameters	: 
 *
 * Returns	: ev_ok
 *
 * Comments	: Also print the result
 *
 *----------------------------------------------------------------------------*/
private short sm_sum(void)
{
	short ret = ev_ok;

	DBG_PRINTF((dbg_proginfo, "Making sum"));

	printf("The sum is: %d\n", firstNum + secondNum);

	return ret;
}

/*------------------------------------------------------------------------------
 *
 * Function	: sm_dif
 *
 * Purpose	: Difference values in firstNum and secondNum
 *
 * Parameters	: 
 *
 * Returns	: ev_ok
 *
 * Comments	: Also print the result
 *
 *----------------------------------------------------------------------------*/
private short sm_dif(void)
{
	short ret = ev_ok;

	DBG_PRINTF((dbg_proginfo, "Making difference"));

	printf("The difference is: %d\n", firstNum - secondNum);

	return ret;
}

/*------------------------------------------------------------------------------
 *
 * Function	: sm_exit
 *
 * Purpose	: Finish program
 *
 * Parameters	: 
 *
 * Returns	: ev_ok
 *
 * Comments	: Simply exits the prog
 *
 *----------------------------------------------------------------------------*/
private short sm_exit(void)
{
	int ret = ev_ok;

	DBG_PRINTF((dbg_proginfo, "Finishing program"));	

	return ret;
}

