/*---------------------------Includes-----------------------------------*/
#include <portable.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sldbg.h>
#include <slstrip.h>

#include <dberr.h>
#include <dbinst.h>

#include <dbinstrh.h>

exec sql include dbinstes.h;

/*---------------------------Externs------------------------------------*/
/*---------------------------Macros-------------------------------------*/
/*---------------------------Enums--------------------------------------*/
/*---------------------------Typedefs-----------------------------------*/
/*---------------------------Globals------------------------------------*/
/*---------------------------Statics------------------------------------*/
/*---------------------------Prototypes---------------------------------*/

/*------------------------------------------------------------------------
 *
 * Function	:  DBG_ENTRY_TEST
 *
 * Purpose	:  wrapper for the DBG_ENTRY
 *
 * Parameters	:  msg - message to print
 *
 * Returns	:  void
 *
 * Comments	:  used only for tests
 *
 *------------------------------------------------------------------------*/
private void DBG_ENTRY_TEST(char *msg)
{
/*#ifdef TESTTEST*/
	DBG_ENTRY(msg);
/*#endif*/
	return;
}

/*------------------------------------------------------------------------
 *
 * Function	:  dbinst_count
 *
 * Purpose	:  count all the records
 *
 * Parameters	:  p_count : number of records
 *
 * Returns	:  SUCCEED / FAIL
 *
 * Comments	:  the result of this count can be used
 *		   to create an appropriately sized associative array
 *
 *------------------------------------------------------------------------*/
public int dbinst_count( int *p_count )
{
static	int	first = TRUE;
	int	ret = SUCCEED;
	char	*this_function = "dbinst_count";
	EXEC SQL begin declare section;
		int	Hcount;
	EXEC SQL end declare section;

	DBG_ENTRY_TEST(this_function);

	if ( first && SUCCEED == (ret = dbinst_begin_count()) )
		first = FALSE;

	if (SUCCEED == ret)
	{
		EXEC SQL open inst_count_cur;

		if (SUCCEED != (ret = sql_errtyp()))
		{
			DBG_PRINTF((dbg_syserr,
				"Open inst_count_cur failed: %ld %s",
						sql_sqlcode(), sql_sqlmsg()));
			ret = FAIL;
		}
		else
		{
			EXEC SQL fetch inst_count_cur
				into :Hcount;

			if (SUCCEED == (ret = sql_errtyp()))
				*p_count = Hcount;
			else
			{
				DBG_PRINTF((dbg_syserr,
					"Fetch count failed: %ld %s",
						sql_sqlcode(), sql_sqlmsg()));
				ret = FAIL;
			}

			EXEC SQL close inst_count_cur;
		}
	}

	return ret;
}

/*------------------------------------------------------------------------
 *
 * Function	:  dbinst_begin_count
 *
 * Purpose	:  setup cursor for counting records
 *
 * Parameters	:  void
 *
 * Returns	:  SUCCEED / FAIL
 *
 * Comments	:  Automatically generated function to setup count cursor
 *
 *------------------------------------------------------------------------*/
public int dbinst_begin_count( void )
{
	int	ret = SUCCEED;
	char	*this_function = "dbinst_begin_count";
	EXEC SQL begin declare section;
		char	sql_statement[256];
	EXEC SQL end declare section;

	DBG_ENTRY_TEST(this_function);

	sprintf( sql_statement,
		"SELECT COUNT(*) "
		"FROM   inst "
	/* USER OPTIONAL WHERE CLAUSE */
	/*	"WHERE	..." */ );

	DBG_PRINTF(( dbg_progdetail, "Preparing:\n%s", sql_statement ));

	EXEC SQL prepare inst_count from :sql_statement;

	if( SUCCEED != (ret = sql_errtyp()) )
	{
		DBG_PRINTF((dbg_syserr,
			"Prepare count statement failed: %ld %s",
					sql_sqlcode(), sql_sqlmsg()));
		ret = FAIL;
	}
	else
	{
		EXEC SQL declare inst_count_cur cursor for inst_count;

		if( SUCCEED != (ret = sql_errtyp()) )
		{
			DBG_PRINTF((dbg_syserr,
				"Declare count cursor failed: %ld %s",
					sql_sqlcode(), sql_sqlmsg()));
			ret = FAIL;
		}
	}

	return ret;
}

/*------------------------------------------------------------------------
 *
 * Function	:  dbinst_scan
 *
 * Purpose	:  begin the scan on first run, and then open the scan
 *
 * Parameters	:  void
 *
 * Returns	:  SUCCEED / FAIL
 *
 * Comments	:  automatically generated function
 *
 *------------------------------------------------------------------------*/
public int dbinst_scan( void )
{
static	int	first = TRUE;
	int	ret = SUCCEED;
	char	*this_function = "dbinst_init_scan";

	DBG_ENTRY_TEST(this_function);
	
	if (first && SUCCEED == (ret = dbinst_begin_scan()) )
		first = FALSE;

	if (SUCCEED == ret)
		ret = dbinst_open_scan();

	return ret;
}

/*------------------------------------------------------------------------
 *
 * Function	:  dbinst_begin_scan
 *
 * Purpose	:  initialise scan
 *
 * Parameters	:  void
 *
 * Returns	:  SUCCEED / FAIL
 *
 * Comments	:  automatically generated function sets up the cursor.
 *		   It can be customised to select what is required
 *		   by the user
 *
 *------------------------------------------------------------------------*/
public int dbinst_begin_scan( void )
{
	int	ret = SUCCEED;
	char	*this_function = "dbinst_begin_scan";
	EXEC SQL begin declare section;
		char	sql_statement[256];
	EXEC SQL end declare section;

	DBG_ENTRY_TEST(this_function);

	sprintf( sql_statement,
		"SELECT	inst.instcode, "
		"	inst.diid, "
		"	inst.descr "
		"FROM	inst "
	/* USER OPTIONAL WHERE CLAUSE */
	/*	"WHERE	..." */ );

	DBG_PRINTF(( dbg_progdetail, "Preparing:\n%s", sql_statement ));

	EXEC SQL prepare inst_all from :sql_statement;

	if( SUCCEED != (ret = sql_errtyp()) )
	{
		DBG_PRINTF((dbg_syserr,
			"prepare inst_all failed: %ld %s",
				sql_sqlcode(), sql_sqlmsg()));
		ret = FAIL;
	}
	else
	{
		EXEC SQL declare inst_all_cur cursor for inst_all;

		if( SUCCEED != (ret = sql_errtyp()) )
		{
			DBG_PRINTF((dbg_syserr,
				"Declare inst_all_cur failed: %ld %s",
					sql_sqlcode(), sql_sqlmsg()));
			ret = FAIL;
		}
	}

	return ret;
}

/*------------------------------------------------------------------------
 *
 * Function	:  dbinst_open_scan
 *
 * Purpose	:  open cursor for the scan
 *
 * Parameters	:  void
 *
 * Returns	:  SUCCEED/FAIL
 *
 * Comments	:  automatically generated function opens the cursor.
 *		   It should be customised by the user
 *
 *------------------------------------------------------------------------*/
public int dbinst_open_scan( void )
{
	int	ret = SUCCEED;
	char	*this_function = "dbinst_open_scan";

	DBG_ENTRY_TEST(this_function);

	EXEC SQL open inst_all_cur
		/* USER OPTIONAL CLAUSE: using ... */ ;

	if( SUCCEED != (ret = sql_errtyp()) )
	{
		DBG_PRINTF((dbg_syserr,"open inst_all_cur failed %ld %s",
			    sql_sqlcode(), sql_sqlmsg() ));
		ret = FAIL;
	}

	return ret;
}

/*------------------------------------------------------------------------
 *
 * Function	:  dbinst_get_next
 *
 * Purpose	:  fetch next record from the cursor
 *
 * Parameters	:  void
 *
 * Returns	:  SUCCEED / FAIL
 *		   or SQE_EOFERR on reaching end of table
 *
 * Comments	:  automatically generated function to fetch next.
 *
 *------------------------------------------------------------------------*/
public int dbinst_get_next( inst_t *p_inst )
{
	int	ret = SUCCEED;
	char	*this_function = "dbinst_get_next";

	DBG_ENTRY_TEST(this_function);

	EXEC SQL
		fetch	inst_all_cur
		into	
			:INSTinstcode,
			:INSTdiid,
			:INSTdescr;

	if( SUCCEED == (ret = sql_errtyp()) )
	{
		strncpy(p_inst->inst_instcode, stp_right(INSTinstcode), strlen(INSTinstcode));
		strncpy(p_inst->inst_diid, stp_right(INSTdiid), strlen(INSTdiid));
		strncpy(p_inst->inst_descr, stp_right(INSTdescr), strlen(INSTdescr));

	}
	else if( SQE_EOFERR != ret )
	{
		DBG_PRINTF((dbg_syserr,"fetch: %ld %s",
			    sql_sqlcode(), sql_sqlmsg() ));
		ret = FAIL;
	}

	return ret;
}

/*------------------------------------------------------------------------
 *
 * Function	:  dbinst_close_scan
 *
 * Purpose	:  close the cursor
 *
 * Parameters	:  void
 *
 * Returns	:  SUCCEED / FAIL
 *
 * Comments	:  Automatically generated to close the cursor
 *
 *------------------------------------------------------------------------*/
public int dbinst_close_scan( void )
{
	int	ret = SUCCEED;
	char	*this_function = "dbinst_close_scan";

	DBG_ENTRY_TEST(this_function);

	EXEC SQL
		close inst_all_cur;

	if( SUCCEED != (ret = sql_errtyp()) )
	{
		DBG_PRINTF((dbg_syserr,"close inst_all_cur failed: %ld %s",
				    sql_sqlcode(), sql_sqlmsg() ));
		ret = FAIL;
	}

	return ret;
}

/*#ifdef TESTTEST*/
/*---------------------------Includes-----------------------------------*/
#include <slclp.h>
/*---------------------------Prototypes---------------------------------*/
int main(int argc, char **argv);

/*------------------------------------------------------------------------
 *
 * Function     : main
 *
 * Purpose      : Test harness
 *
 * Parameters   :
 *
 * Returns      :
 *
 * Comments     : Automatically generated to test auto functions
 *
 *----------------------------------------------------------------------*/
int main(int argc, char **argv)
{
        int     ret=SUCCEED;
        private int     function = FAIL;
        private int	runs = 1;
        private clp_parm        clp[] =
        {
                {'f', parm_int, 1, TRUE, (void *)&function, 0},
                {'r', parm_int, 1, FALSE, (void *)&runs, 0},
               {0}
        };

        if (SUCCEED!=(ret=clp_parse(argc, argv, clp)))
        {
                printf("Usage:\t%s -f function [-r run_x_times\n"
			"where\tr defines how many times the function should be executed\n"
			"\tf defines the test to conduct. Can be one of:\n"
			"\t\t1 - Count,\n"
			"\t\t2 - Scan\n",

			argv[0]);
                return FAIL;
        }

        DBG_SETNAME("TESTTEST");
        DBG_SETLEV(5);

        if (SUCCEED!=sql_open(getenv("DBNAME")) || SUCCEED!=sql_begin())
                return FAIL;


	DBG_PRINTF((dbg_progdetail, "Test dbinst database access functions"));

	DBG_PRINTF((dbg_progdetail, "-- INPUT --------------"));
	DBG_PRINTF((dbg_progdetail, " function: %d  runs: %d",
			function, runs));
	DBG_PRINTF((dbg_progdetail, "-----------------------"));

	if ( 1 == function )
	{
		int cnt = 0;
		int i = 0;

		for ( i = 0; i < runs; i++ )
		{
			cnt = 0;
			DBG_PRINTF((dbg_progdetail, "\t\t\t\ttesting: dbinst_count"));
			ret = dbinst_count(&cnt);
			DBG_PRINTF((dbg_progdetail,"-- RESULTS ------------"));
			DBG_PRINTF((dbg_progdetail,"ret: %d  run: %d  count: %d",
				ret, i, cnt));
			DBG_PRINTF((dbg_progdetail,"-----------------------"));
		}
	}
	if ( 2 == function )
	{
		int i = 0;
		int endOfScan = 0;

		inst_t	inst;

		for ( i = 0; SUCCEED == ret && i < runs; i++ )
		{
			DBG_PRINTF((dbg_progdetail, "\t\t\t\ttesting: dbinst scan"));
			endOfScan = 0;
			ret = dbinst_scan();
			if ( SUCCEED == ret )
			{
				while ( SUCCEED == ret && !endOfScan )
				{
					ret = dbinst_get_next( &inst );
					if ( SUCCEED == ret )
					{
						DBG_PRINTF((dbg_progdetail,
							"Returned: " /* USER PRINT RETURNED
									VALUES TO DEBUG */ ));
					}
					if ( SQE_EOFERR == ret )
					{
						endOfScan = 1;
						ret = SUCCEED;
					}
				}
			}

			if ( SUCCEED == ret )
				ret = dbinst_close_scan();

			DBG_PRINTF((dbg_progdetail,"-- RESULTS ------------"));
			DBG_PRINTF((dbg_progdetail,"ret: %d  run: %d", ret, i));
			DBG_PRINTF((dbg_progdetail,"-----------------------"));
		}
	}

        if (SUCCEED==ret)
                sql_commit();
        else
                sql_abort();
        sql_close();

	return ret;
}

/*#endif*/

