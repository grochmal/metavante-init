/*---------------------------Includes-----------------------------------------*/
#include <portable.h>
#include <stdio.h>	/* sprintf, sscanf, etc. */
#include <string.h>	/* strcmp, strcat, etc. */
#include <stdlib.h>	/* Standard Library */

/* Cortex stdlib */
#include <sldbg.h>	/* DBG_PRINTF, etc. */
#include <slclp.h>	/* Parse command line */
#include <slcfp.h>	/* Parse config file */

#include "dberr.h"	/* sql_open, etc. */
#include <dbbrnrh.h>
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
private int addToDb(BRANCH_t *p);
private int updateInDb(BRANCH_t *p);
private int deleteFromDb(BRANCH_t *p);

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

	static BRANCH_t dbRecord;

	static clp_parm clp[]=
	{
		{'t', parm_string, CMDL_TASK_SIZE, TRUE, progTask, 0},
		{'i', parm_long, 0, TRUE,(void *)&dbRecord.inst_id, 0},
		{'b', parm_string, BRANCH_BRNCODE_BUFFSIZE, TRUE,
			dbRecord.brncode, 0},
		{'f', parm_string, BRANCH_FECODE_BUFFSIZE, TRUE,
			dbRecord.fecode, 0},
		{'d', parm_string, BRANCH_DESCR_BUFFSIZE, TRUE,
			dbRecord.descr, 0},
		{'1', parm_string, BRANCH_ADDRL1_BUFFSIZE, TRUE,
			dbRecord.addrl1, 0},
		{'2', parm_string, BRANCH_ADDRL2_BUFFSIZE, TRUE,
			dbRecord.addrl2, 0},
		{'c', parm_string, BRANCH_CITY_BUFFSIZE, TRUE,
			dbRecord.city, 0},
		{'m', parm_string, BRANCH_CONTACTNAME_BUFFSIZE, TRUE,
			dbRecord.contactname, 0},
		{'n', parm_string, BRANCH_CONTACTNO_BUFFSIZE, TRUE,
			dbRecord.contactno, 0},
		{'r', parm_string, BRANCH_REGION_BUFFSIZE, TRUE,
			dbRecord.region, 0},
		{'p', parm_string, BRANCH_POSTCODE_BUFFSIZE, TRUE,
			dbRecord.postcode, 0},
		{'y', parm_string, BRANCH_COUNTRYCODE_BUFFSIZE, TRUE,
			dbRecord.countrycode, 0},
		{'s', parm_string, BRANCH_SORTCODE_BUFFSIZE, FALSE,
			dbRecord.sortcode, 0},
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
		printf("Usage: esqldb -tibfd12cmnrpy [-s]\n \
-t <Task to do>\n -i <Instcode>\n -b <Brncode>\n -f <Fecode>\n \
-d <Descriprion>\n -1 <Adress 1>\n -2 <Adress 2>\n -c <City>\n \
-m <Contact name>\n -n <Contact number>\n -r <Region>\n \
-p <Postcode>\n -y <Country code>\n -s <Sortcode>\n\n\
Please insert all the data, the prog isn't a forgiving one.\n");

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
 * Parameters	: BRANCH_t *
 *
 * Returns	: SUCCEED
 *		else error code as from BRANCHadd
 *
 * Comments	: Simply add the record (if sql permits).
 *		There's debug on syswarn level in BRANCHadd.
 *
 *----------------------------------------------------------------------------*/
private int addToDb(BRANCH_t *ptrBranch)
{
	int ret = SUCCEED;

	ret = BRANCHadd(ptrBranch);

	if ( SUCCEED != ret )
	{
		printf("this is the error we want: %s", mysql_sqlmsg());
	}

	return ret;
}

/*------------------------------------------------------------------------------
 *
 * Function	: updateInDb
 *
 * Purpose	: Update a record in table
 *
 * Parameters	: BRANCH_t *
 *
 * Returns	: SUCCEED
 *		else error code as from BRANCHupdate
 *
 * Comments	: Simply update the record (if sql permits).
 *		There's debug on syswarn level in BRANCHupdate.
 *
 *----------------------------------------------------------------------------*/
private int updateInDb(BRANCH_t *ptrBranch)
{
	int ret = SUCCEED;

	ret = BRANCHupdate(ptrBranch);

	return ret;
}

/*------------------------------------------------------------------------------
 *
 * Function	: deleteFromDb
 *
 * Purpose	: Delete a record in table
 *
 * Parameters	: BRANCH_t *
 *
 * Returns	: SUCCEED
 *		else error code from BRANCHdelete
 *
 * Comments	: Simply delete the record (if sql permits).
 *		There's debug on syswarn level in BRANCHdelete.
 *
 *----------------------------------------------------------------------------*/
private int deleteFromDb(BRANCH_t *ptrBranch)
{
	int ret = SUCCEED;

	ret = BRANCHdelete(ptrBranch);

	return ret;
}

