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

private char instcode[] = "6chars";
private char diid[] = "thirteen chrs";
private char dfe[] = "10 charcts";
private char descr[] = "twenty two characteres";

/*---------------------------Prototypes---------------------------------------*/
private int addToDb(void);
private int updateInDb(void);
private int deleteFromDb(void);

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

	static clp_parm clp[]=
	{
		{'t', parm_string, 12, TRUE, progTask, 0},
		{'i', parm_string, 5, TRUE, instcode, 0},
		{'f', parm_string, 12, FALSE, diid, 0},
		{'d', parm_string, 9, FALSE, dfe, 0},
		{'s', parm_string, 21, FALSE, descr, 0},
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

		ret = addToDb();

		if(SUCCEED == ret)
			printf("Record added\n");
		else
			printf("The record already exist\n");
	}
	else if(!strcmp(progTask,"update"))
	{
		
		DBG_PRINTF((dbg_proginfo, "user is updating a record"));

		ret = updateInDb();

		if(SUCCEED == ret)
			printf("Record updated\n");
		else
			printf("There's no such record\n");
	}
	else if(!strcmp(progTask, "delete"))
	{

		DBG_PRINTF((dbg_proginfo, "user is deleting a record"));

		ret = deleteFromDb();

		if(SUCCEED == ret)
			printf("Record deleted\n");
		else
			printf("There's no such record\n");
	}
	else
		printf("Usage:\n  esqldb -t <Task to do> -i <instcode>\
 [-f <fecode>] [-d <diid>] [-s <descr>]\n\n\
If you not iclude -f, -d or -s on update the program will do nothing.\n");

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
 * Parameters	: 
 *
 * Returns	: SUCCEED
 *		else error code as from INSTadd
 *
 * Comments	: If the user does not specify some data defults are set.
 *		There's debug on syswarn level in INSTadd and
 *		INSTgetbyINST_HASH
 *
 *----------------------------------------------------------------------------*/
private int addToDb(void)
{
	int ret = FAIL;
	INTS_t dbRecord;
	INST_HASH_t hashId;

	hashId.instode = instcode;

	if(SUCCEED != INSTgetbyINST_HASH(&dbRecord, &hashId))
	{
		if(12 <= strlen(diid))
			strcpy(dbRecord.diid, "default");
		else
			strcpy(dbRecord.diid, diid);

		if(9 <= strlen(dfe))
			strcpy(dbRecord.dfe, "default");
		else
			strcpy(dbRecord.dfe, dfe);

		if(21 <= strlen(descr))
			strcpy(dbRecord.descr, "default");
		else
			strcpy(dbRecord.descr, descr);

		ret = INSTadd(dbRecord);
	}

	return ret;
}

/*------------------------------------------------------------------------------
 *
 * Function	: getByIndex
 *
 * Purpose	: Select and print a record from the table
 *
 * Parameters	: 
 *
 * Returns	: SUCCEED
 *
 * Comments	: 
 *
 *----------------------------------------------------------------------------*/
int getbyIndex(void)
{
	int ret = SUCCEED;

	

	return ret;
}

/*------------------------------------------------------------------------------
 *
 * Function	: updateInDb
 *
 * Purpose	: Update a record in table
 *
 * Parameters	: 
 *
 * Returns	: SUCCEED
 *		else error code as from INSTupdbyINST_HASH
 *
 * Comments	: The user might specify which parts of the row are updated.
 *		There's debug on syswarn level in INSTgetbyINST_HASH4upd
 *		and INSTupdbyINST_HASH.
 *
 *----------------------------------------------------------------------------*/
private int updateInDb(void)
{
	int ret = SUCCEED;
	INTS_t dbRecord;
	INST_HASH_t hashId;

	hashId.instode = instcode;

	if(SUCCEED == (ret = INSTgetbyINST_HASH4upd(&dbRecord, &hashId)))
	{
		if(12 > strlen(diid))
			strcpy(dbRecord, diid);

		if(9 > strlen(dfe))
			strcpy(dbRecord, def);

		if(21 > strlen(descr))
			strcpy(dbRecord, descr);

		ret = INSTupdbyINST_HASH(&dbRecord, &hashId);
	}

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
private int deleteFromDb(void)
{
	int ret = SUCCEED;

	ret = INSTdelete(ptrInst);

	return ret;
}

