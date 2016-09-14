/*---------------------------Includes-----------------------------------*/
#include <portable.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <sldbg.h>

#include <dberr.h>

#include <locator.h>

#include <dbbrnrh.h>
exec sql include dbbrnes.h;
#include <dbbrnes.h>
/*---------------------------Externs------------------------------------*/
/*---------------------------Macros-------------------------------------*/
/*---------------------------Enums--------------------------------------*/
/*---------------------------Typedefs-----------------------------------*/
/*---------------------------Globals------------------------------------*/
/*---------------------------Statics------------------------------------*/
static char rcsid[] = "$Id$";
/*---------------------------Prototypes---------------------------------*/

/*------------------------------------------------------------------------
 *
 * Function	: BRANCHupdate
 *
 * Purpose	: Update BRANCH row
 *
 * Parameters	: p_BRANCH - structure to update from
 *
 * Returns	: SUCCEED - ok
 *		  else - error code as from sql_interr
 *
 * Comments	: We don't know which row to update; therefore we use
 *		  the first hash key, and hope it's not been changed !
 *
 *----------------------------------------------------------------------*/
public int myBRANCHupdate(BRANCH_t *p_BRANCH)
{
	int ret;
	static int first_time=TRUE;

	BRANCHcs2hv(p_BRANCH);
	
	if (TRUE==first_time)
	{
		exec sql begin declare section;
			char stmt[5000];
		exec sql end declare section;

		first_time = FALSE;
		strcpy(stmt,"");

		strcat (stmt," update branch ");
                strcat (stmt," set ");	

			strcat(stmt,"branch.fecode= ?, "); 
			strcat(stmt,"branch.descr= ?, "); 
			strcat(stmt,"branch.addrl1= ?, "); 
			strcat(stmt,"branch.addrl2= ?, "); 
			strcat(stmt,"branch.city= ?, "); 
			strcat(stmt,"branch.contactname= ?, "); 
			strcat(stmt,"branch.contactno= ?, "); 
			strcat(stmt,"branch.region= ?, "); 
			strcat(stmt,"branch.postcode= ?, "); 
			strcat(stmt,"branch.countrycode= ?, "); 
			strcat(stmt,"branch.sortcode= ?, "); 
			strcat(stmt,"branch.id= ? "); 
		strcat(stmt," where "); 
		strcat(stmt,"	branch.inst_id = ? "); 
		strcat(stmt,"and	branch.brncode = ? "); ;
	
	 	exec sql prepare  BRANCH_U4 from :stmt;

		ret = sql_errtyp();

		if( SUCCEED != ret )
			DBG_PRINTF((dbg_syswarn,"%supdate prepare statement " 
			" failed: %ld %s", "BRANCH", sql_sqlcode(), 
			sql_sqlmsg() ));

	}

	exec sql execute  BRANCH_U4 using 
			 :BRANCHfecode,
			 :BRANCHdescr,
			 :BRANCHaddrl1,
			 :BRANCHaddrl2,
			 :BRANCHcity,
			 :BRANCHcontactname,
			 :BRANCHcontactno,
			 :BRANCHregion,
			 :BRANCHpostcode,
			 :BRANCHcountrycode,
			 :BRANCHsortcode,
			 :BRANCHid,
			 :BRANCHinst_id,
			 :BRANCHbrncode;
 
        ret = sql_errtyp();
 
        if( SUCCEED != ret )
		 DBG_PRINTF((dbg_syswarn,"%supdate execut stmt. failed: %ld %s",
                            "BRANCH", sql_sqlcode(), sql_sqlmsg() ));
 
        return ret;
}
 
