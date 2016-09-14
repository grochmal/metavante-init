/*---------------------------Includes-----------------------------------------*/
#include <portable.h>
#include <stdio.h>	/* sprintf, sscanf, etc. */
#include <string.h>	/* strcmp, strcat, etc. */
#include <stdlib.h>	/* Standard Library */

/* Cortex stdlib */
#include <sldbg.h>	/* DBG_PRINTF, etc. */
#include <slclp.h>	/* Parse command line */
#include <slcfp.h>	/* Parse config file */

#include <dberr.h>	/* sql_open, etc. */
#include <dbinstrh.h>
/*#include <dbinstes.h> simply don't compile with it ?!?!?!*/

/*---------------------------Externs------------------------------------------*/
/*---------------------------Macros-------------------------------------------*/
#define TAGDBG		"DEBUG"
#define DBGNAME		"ESQLDBG"

#define CMDL_TASK_SIZE	12

/*---------------------------Enums--------------------------------------------*/
/*---------------------------Typedefs-----------------------------------------*/
/*---------------------------Globals------------------------------------------*/
/*---------------------------Statics------------------------------------------*/
private	int	M_dbglev = dbg_progdetail;	/* Debug trace output level */
private	int	M_dbgbuf = 0;			/* Debug buffering level */
private	char	M_dbgfile[CTX_FILENAME_MAX];	/* Debug filename */

/*---------------------------Prototypes---------------------------------------*/
private int addToDb(INST_t *p);
private int updateInDb(INST_t *p);
private int deleteFromDb(INST_t *p);

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
 * Comments	:  Parse command line and file
 *
 *----------------------------------------------------------------------------*/
public int main(int argc, char **argv)
{
	int ret = SUCCEED;
	static char progTask[CMDL_TASK_SIZE];

	static INST_t dbRecord;

	static clp_parm clp[]=
	{
		{'t', parm_string, CMDL_TASK_SIZE, TRUE, progTask, 0},
		{'i', parm_string, INST_INSTCODE_BUFFSIZE, TRUE, dbRecord.instcode, 0},
		{'f', parm_string, 12, TRUE, dbRecord.diid, 0},
		{'d', parm_string, 9, TRUE, dbRecord.dfe, 0},
		{'s', parm_string, 21, TRUE, dbRecord.descr, 0},
		{0}
	};
	private cfp_parm cfp[] =
        {
		{"DEBUG", parm_int, 0, TRUE, (void *)&M_dbglev, 0},
		{"DBGBUF", parm_int, 0, FALSE, (void *)&M_dbgbuf, 0},
		{0}
	};

	if( SUCCEED != (ret = clp_parse(argc, argv, clp)) )
	{
		fprintf(stderr, "Failed to parse command line\n");
	}
	else if( SUCCEED != (ret = cfp_lite(cfp, TAGDBG, NULL /*subsect*/)) )
	{
		fprintf(stderr, "Failed to parse configuration file\n");
	}

	if( SUCCEED == ret )
	{
		DBG_SETLEV(M_dbglev);
		DBG_SETBUF(M_dbgbuf);
		DBG_SETNAME(DBGNAME);

		if( SUCCEED != (ret = sql_open(getenv("DBNAME"))) )
		{
			DBG_PRINTF((dbg_syserr, "Failed to open database"));
		}
		else if(SUCCEED != (ret = sql_begin()) )
		{
			DBG_PRINTF((dbg_syserr, "Failed to begin SQL"));
		}
	}

	/* functionality */

	DBG_PRINTF((dbg_proginfo, "The task is: %s\n", progTask));

	if(!strcmp(progTask, "add"))
	{
		DBG_PRINTF((dbg_proginfo, "user is adding a record"));

		ret = addToDb(&dbRecord);

		if(SUCCEED == ret)
			printf("Record added\n");
		else
			printf("The record already exist\n");
	}
	else if(!strcmp(progTask,"update"))
	{
		
		DBG_PRINTF((dbg_proginfo, "user is updating a record"));

		ret = updateInDb(&dbRecord);

		if(SUCCEED == ret)
			printf("Record updated\n");
		else
			printf("There's no such record\n");
	}
	else if(!strcmp(progTask, "delete"))
	{

		DBG_PRINTF((dbg_proginfo, "user is deleting a record"));

		ret = deleteFromDb(&dbRecord);

		if(SUCCEED == ret)
			printf("Record deleted\n");
		else
			printf("There's no such record\n");
	}
	else
		printf("Usage:\n  esqldb -t <Task to do> -i <instcode>\
-f <fecode> -d <diid> -s <descr>\n\n\
Please insert all data the prog isn't a forgiving one.\n");

	if( SUCCEED == ret )
		ret = sql_commit();
	else
		ret = sql_abort();

	return SUCCEED == ret ? 0 : 1;
}

/*------------------------------------------------------------------------------
 *
 * Function	: addToDb
 *
 * Purpose	: Add a record into table
 *
 * Parameters	: INST_t *
 *
 * Returns	: SUCCEED
 *		else error code as from INSTadd
 *
 * Comments	: Simply add the record (if sql permits).
 *		There's debug on syswarn level in INSTadd.
 *
 *----------------------------------------------------------------------------*/
private int addToDb(INST_t *ptrInst)
{
	int ret = SUCCEED;

	ret = INSTadd(ptrInst);

	return ret;
}

/*------------------------------------------------------------------------------
 *
 * Function	: updateInDb
 *
 * Purpose	: Update a record in table
 *
 * Parameters	: INST_t *
 *
 * Returns	: SUCCEED
 *		else error code as from INSTupdate
 *
 * Comments	: Simply update the record (if sql permits).
 *		There's debug on syswarn level in INSTupdate.
 *
 *----------------------------------------------------------------------------*/
private int updateInDb(INST_t *ptrInst)
{
	int ret = SUCCEED;

	ret = INSTupdate(ptrInst);

	return ret;
}

/*------------------------------------------------------------------------------
 *
 * Function	: deleteFromDb
 *
 * Purpose	: Delete a record in table
 *
 * Parameters	: INST_t *
 *
 * Returns	: SUCCEED
 *		else error code from INSTdelete
 *
 * Comments	: Simply delete the record (if sql permits).
 *		There's debug on syswarn level in INSTdelete.
 *
 *----------------------------------------------------------------------------*/
private int deleteFromDb(INST_t *ptrInst)
{
	int ret = SUCCEED;

	ret = INSTdelete(ptrInst);

	return ret;
}

