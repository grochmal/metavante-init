#ifndef __DBINST_H
#define __DBINST_H

/*---------------------------Includes-----------------------------------*/
#include <portable.h>

/*---------------------------Externs------------------------------------*/
/*---------------------------Macros-------------------------------------*/
/*---------------------------Enums--------------------------------------*/
/*---------------------------Typedefs-----------------------------------*/
typedef struct
{
	char	inst_instcode[5];
	char	inst_diid[12];
	char	inst_descr[21];
} inst_t;

/*---------------------------Globals------------------------------------*/
/*---------------------------Statics------------------------------------*/
/*---------------------------Prototypes---------------------------------*/

public int dbinst_count( int *p_count );
public int dbinst_begin_count( void );
public int dbinst_scan( void );
public int dbinst_begin_scan( void );
public int dbinst_open_scan( void );
public int dbinst_get_next( inst_t *p_inst );
public int dbinst_close_scan( void );

#endif

