/*---------------------------Includes-----------------------------------------*/
#include <portable.h>
#include <stdio.h> /* sprintf, sscanf, etc. */
#include <string.h> /* strcmp, strcat, etc. */
#include <stdlib.h> /* Standard Library */

/* Cortex stdlib */
#include <sldbg.h> /* DBG_PRINTF, etc. */
#include <slclp.h> /* Command Line Parser */

#include <cortex.h> /* Cortex definitions */
#include <cocbfdef.h> /* Card based definitions */

/*---------------------------Externs------------------------------------------*/
/*---------------------------Macros-------------------------------------------*/
#define DBGNAME "CLP"

/*---------------------------Enums--------------------------------------------*/
/*---------------------------Typedefs-----------------------------------------*/
/*---------------------------Globals------------------------------------------*/
/*---------------------------Statics------------------------------------------*/
static int M_dbglev = dbg_progdetail; /* Debug trace output level */
static int M_dbgbuf = 0; /* Debug buffering level */
static char M_dbgfile[CTX_FILENAME_MAX] = "../tmp/clp.log"; /* Debug filename */

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
    static char *sysdate = "This string is not too long";
    static char anotherdate = 'w';
    static int onemoredate = 3;
    static bool booldate = TRUE;

    /* Define the options inside a static struct */
    /* static clp_parm clp[] =
     * {
     *     {'c', parm_type, lenght(only for strings), Mandatory (boolean),
     *         (void *)&variable_to_set, 0},
     *     ...
     *     {0]
     * }; */
    /* The lenght is only for parm_string, also the string doesn't
     * need the (void *)& to find the address of the variable */
    static clp_parm clp[]=
    {
        {'s', parm_string, 30, FALSE, (void *)&sysdate, 0},
        {'a', parm_char, 0, FALSE, (void *)&anotherdate, 0},
        {'b', parm_int, 0, FALSE, (void *)&onemoredate, 0},
        {'c', parm_falsebool, 0, FALSE, (void *)&booldate, 0},
        {0}
    };
    /* The most common possible parameters for parm_type are:
     * parm_true_flag, parm_falseflag, parm_truebool, parm_falsebool,
     * parm_char, parm_int, parm_float, parm_string, parm_hexstring
     * And some more small variations like parm_uint or parm_short */

    if(SUCCEED == ret)
    {
        DBG_SETFILE(M_dbgfile);
        DBG_SETLEV(M_dbglev);
        DBG_SETBUF(M_dbgbuf);
        DBG_SETNAME(DBGNAME);
    }

    /* After setting the static structure you invoke clp_parse
     * and th variables in the before last column of the struct
     * will be updated */
    if(SUCCEED != (ret = clp_parse(argc, argv, clp)))
    {
        DBG_PRINTF(dbg_syserr, "Failed to parse command line\n");
    }
    /* Any functions that return SUCCEED / FAIL should be checked to continue
     * program execution. If at some point the ret gets the value FAIL an error
     * message should be printed and no more commands executed. */
    /* if(SUCCEED != (ret = clp_parse(...)))
     * {
     *     DBG_PRINTF((dbg_syserr, "Error parsing command line"));
     * }
     * ... */

    if(SUCCEED == ret)
    {
        DBG_PRINTF((dbg_progdetail,"output: %s", sysdate));
        DBG_PRINTF((dbg_progdetail,"output: %c", anotherdate));
        DBG_PRINTF((dbg_progdetail,"output: %d", onemoredate));
        DBG_PRINTF((dbg_progdetail,"output: %s", booldate ? "TRUE" : "FALSE"));
    }

    return ret;
}

