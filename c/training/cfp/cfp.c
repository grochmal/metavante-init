/*---------------------------Includes-----------------------------------------*/
#include <portable.h>
#include <stdio.h> /* sprintf, sscanf, etc. */
#include <string.h> /* strcmp, strcat, etc. */
#include <stdlib.h> /* Standard Library */

/* Cortex stdlib */
#include <sldbg.h> /* DBG_PRINTF, etc. */
#include <slclp.h> /* Parse command line */
#include <slcfp.h> /* Parse config file */

#include <cortex.h> /* Cortex definitions */
#include <cocbfdef.h> /* Card based definitions */

/*---------------------------Externs------------------------------------------*/
/*---------------------------Macros-------------------------------------------*/
#define SESSION  "TRAINING"
#define DEBUGNAME "CFP"

/*---------------------------Enums--------------------------------------------*/
/*---------------------------Typedefs-----------------------------------------*/
/*---------------------------Globals------------------------------------------*/
/*---------------------------Statics------------------------------------------*/
static int M_dbglev = dbg_fatal; /* Debug trace output level */
static int M_dbgbuf = 0;   /* Debug buffering level */
static char M_dbgfile[CTX_FILENAME_MAX]; /* Debug filename */

/*---------------------------Prototypes---------------------------------------*/

/*------------------------------------------------------------------------------
 *
 * Function : main
 *
 * Purpose : main function
 *
 * Parameters : argc, argv - Usual Suspects
 *
 * Returns : SUCCEED / FAIL
 *
 * Comments :
 *
 *----------------------------------------------------------------------------*/
public int main(int argc, char **argv)
{
    int ret = SUCCEED;
    static short shortparam = 0x1;
    static char charparam = '#';
    static char stringparam[20];
    static double doubleparam;
    static short int otherparam;

    static cfp_parm cfp[] =
    {
        {"DEBUG", parm_int, 0, FALSE, (void *)&M_dbglev, 0},
        {"DEBUGBUF", parm_int, 0, FALSE, (void *)&M_dbgbuf, 0},
        {"DEBUGBUF", parm_string, CTX_FILENAME_MAX, FALSE, M_dbgfile, 0},
        {"SHORTPARAM", parm_short, 0, TRUE, (void *)&shortparam, 0},
        {"PARAM1", parm_char, 0, TRUE, (void *)&charparam, 0},
        {"PARAM2", parm_string, 20, FALSE, stringparam, 0},
        {"PARAM3", parm_double, 0, FALSE, (void *)&doubleparam, 0},
        {"OTHERPARAM", parm_short, 0, FALSE, (void *)&otherparam, 0},
        {0}
    };

    if( SUCCEED != (ret = cfp_lite(cfp, SESSION, NULL /*subsect*/)) )
    {
        fprintf(stderr, "Failed to parse configuration file\n");
    }

    if( SUCCEED == ret )
    {
    /*  DBG_SETFILE(M_dbgfile); */
    DBG_SETLEV(M_dbglev);
    DBG_SETBUF(M_dbgbuf);
    }

    DBG_SETNAME(DEBUGNAME);

    DBG_PRINTF((dbg_progdetail,"Hello there"));

    DBG_PRINTF((dbg_progdetail, "parameter 1: \'%c\' 0x%X",
    charparam,(int)charparam));

    DBG_PRINTF((dbg_progdetail, "shortparam: %hd", shortparam));
    DBG_PRINTF((dbg_progdetail, "parameter 2: %s", stringparam));

    DBG_PRINTF((dbg_progdetail, "parameter 3: %lf", doubleparam));

    DBG_PRINTF((dbg_progdetail, "other parameter : %d", otherparam));

    return ret;
}

