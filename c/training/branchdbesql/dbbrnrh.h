#ifndef __DBBRNRH_H
#define __DBBRNRH_H
/*#pragma ident "$Id$;*/
/*---------------------------Includes-----------------------------------*/
#include <portable.h>		/* for BLOB_BUFSIZE */
#include <sqltypes.h>

#include <infidxmap.h>
/*---------------------------Externs------------------------------------*/
/*---------------------------Macros-------------------------------------*/
#define BRANCH_INSTCODE_BUFFSIZE 5
#define BRANCH_BRNCODE_BUFFSIZE 9
#define BRANCH_FECODE_BUFFSIZE 9
#define BRANCH_DESCR_BUFFSIZE 21
#define BRANCH_ADDRL1_BUFFSIZE 36
#define BRANCH_ADDRL2_BUFFSIZE 36
#define BRANCH_CITY_BUFFSIZE 41
#define BRANCH_CONTACTNAME_BUFFSIZE 21
#define BRANCH_CONTACTNO_BUFFSIZE 21
#define BRANCH_REGION_BUFFSIZE 4
#define BRANCH_POSTCODE_BUFFSIZE 11
#define BRANCH_COUNTRYCODE_BUFFSIZE 4
#define BRANCH_SORTCODE_BUFFSIZE 7
#define BRANCH_HASH_PREP2 \
	strpcpy(BRANCH_HASHinstcode, p_BRANCH_HASH->instcode);\
	strpcpy(BRANCH_HASHbrncode, p_BRANCH_HASH->brncode);\

#define BRANCH_HASH_PREP1 \
	branch.instcode = ? \
and	branch.brncode = ? 
/*---------------------------Enums--------------------------------------*/
/*---------------------------Typedefs-----------------------------------*/
#ifndef VDP_STRUCT_DEFINED

#ifndef BLOB_BUFSIZE
#define BLOB_BUFSIZE 4096
#endif

typedef struct
{
	long	curlen;
	char	data[BLOB_BUFSIZE];
} vdp;

#define VDP_STRUCT_DEFINED 1

#endif

typedef struct
{
	char	inst_id[5];
	char	brncode[9];
	char	fecode[9];
	char	descr[21];
	char	addrl1[36];
	char	addrl2[36];
	char	city[41];
	char	contactname[21];
	char	contactno[21];
	char	region[4];
	char	postcode[11];
	char	countrycode[4];
	char	sortcode[7];
} BRANCH_t;

typedef struct
{
	char	instcode[5];
	char	brncode[9];
} BRANCH_HASH_t;

/*---------------------------Globals------------------------------------*/
/*---------------------------Statics------------------------------------*/
/*---------------------------Prototypes---------------------------------*/
extern	long	dbu_date_cvt_to_norm(long inf_date);
extern	long	dbu_date_cvt_to_db(long ctx_date);

extern	int	BRANCHadd(BRANCH_t *p_BRANCH);
extern	int	BRANCHupdate(BRANCH_t *p_BRANCH);
extern	int	BRANCHdelete(BRANCH_t *p_BRANCH);
extern	void	BRANCHdump(BRANCH_t *p_BRANCH);
extern	void	BRANCHdumplev(BRANCH_t *p_BRANCH, int dbglev);

extern	char    *BRANCH_HASHkey2str(char *out, BRANCH_HASH_t *p_BRANCH_HASH);
extern	int	BRANCHgetbyBRANCH_HASH(BRANCH_t *p_BRANCH,
			BRANCH_HASH_t *p_BRANCH_HASH);
extern	int	BRANCHgetbyBRANCH_HASH4upd(BRANCH_t *p_BRANCH,
			BRANCH_HASH_t *p_BRANCH_HASH);
extern	int	BRANCHupdbyBRANCH_HASH(BRANCH_t *p_BRANCH,
			BRANCH_HASH_t *p_BRANCH_HASH);
extern	int	BRANCHupdallbyBRANCH_HASH(BRANCH_t *p_BRANCH,
			BRANCH_HASH_t *p_BRANCH_HASH);
extern	int	BRANCHdelbyBRANCH_HASH( BRANCH_HASH_t *p_BRANCH_HASH);

#endif
