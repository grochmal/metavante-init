#ifndef __PORTABLE_H
#define __PORTABLE_H

/*---------------------------------Includes----------------------------------*/
/*#include <currentlabels.h>*/

/*---------------------------------Standard Types----------------------------*/
typedef int bool;                  /* >= 16 bits used as boolean. */
typedef char flag;                 /* >= 8 bits used as boolean. */

typedef unsigned short word;       /* >= 16 bits unsigned type. */

typedef int rchar;                 /* I/O functions return values. */
typedef char *string;              /* For readability. */

/* If void is not supported, uncomment the following line. */
/* typedef int void; */

/*
 * Use this length and type for filename variables, use 256 on
 * BSD4.2 since it is defined as such in dir.h
 * on AIX 4.1.4 it gives a fatal error.
 * Let start using MAXPATHLEN defined in the sys/param.h.
 * #if !defined MAXPATHLEN && !defined AIX
 * #define MAXPATHLEN 64
 * #endif
 */

/* Not so bright, this screws up sys/types! */
/* typedef char path[MAXPATHLEN]; */

/*
 * Define byte and BYTE to portably support an unsigned 8 bit data type
 * changed from char to unsigned char. AIX default char is unsigned
 * but HP-UX have a signed char.
 */
typedef unsigned char byte;        /* 8 bit unsigned type. */

/*---------------------------------Standard Macros---------------------------*/
/* Truncates data, i.e. takes the first byte of data. */
#define BYTE(x) ((x) & 0xff)

#define HIBYTE(x) (((x) >> 8) & 0xff)       /* Hi byte of short. */
#define LOBYTE(x) ((x) & 0xff)              /* Low byte of short. */
#define HIWORD(x) (((x) >> 16) & 0xffffL)   /* Hi word of long. */
#define LOWORD(x) ((x) & 0xffff)            /* Low byte of word. */
#define CHAR(x)   ((x) & 0x7f)              /* Truncate to 7 bits. */
#define DECODE(x) (int)((x) - '0')          /* Int value of a digit. */

/*
 * Long unsigned right shift,
 * right shift a signed long as if it where a unsigned long
 * independently of architecture and machine type.
 */
#define LURSHIFT(n, b) (((long)(n) >> (b)) & (0x7fffffffL >> ((b) - 1)))

/* Number of elements in array. */
#define DIM(a) (sizeof(a) / sizeof(*(a)))


/* Scope-control pseudo-keywords. */
#define public                     /* public is C default scope. */
#define private static             /* static really means private. */

/*
 * Variable allocation macros,
 * protect from multiple definition of the same global variable.
 * You define the global variable in the header file like::
 *     CLASS G_errno I( = SUCCEED);
 * These macros will change this for::
 *     extern G_errno;
 * if you are building a library, or to::
 *     G_errno = SUCCEED;
 * if you are building a binary with a main function.  Notice that
 * creating a binary with a main function means for us defining
 * ALLOC, TESTTEST or MAIN.
 */
#if defined(CLASS) || defined(I)
# undef CLASS
# undef I
#endif

#if (defined(ALLOC) || defined(TESTTEST) || defined(MAIN))
# define CLASS                      /* Allocate and initialise. */
# define I(X) X
#else
# define CLASS extern               /* Just reference. */
# define I(X)
#endif


/* Structure element size. */
#define ELEM_SIZE(s, e) (sizeof(((s *)0)->e))

#ifdef HP_UX
/*
 * Ensure HP-UX builds common_5.0 or higher use Big Message Queues
 * (see /usr/include/sys/ipc.h on HPUX).
 */
# define __BIGMSGQUEUE_ENABLED 1

/* Offset of a structure element. */
# ifdef D64
#  define OFFSET(s,e)   ((long) &(((s *)0)->e))
# else
#  define OFFSET(s,e)   ((int) &(((s *)0)->e))
# endif

#else  /* not HP_UX */

# ifdef D64
#  define OFFSET(s, e)   ((long) &(((s *)0)->e))
# else
#  define OFFSET(s, e)   ((const int) &(((s *)0)->e))
# endif

#endif  /* HP_UX */

/* 'Safe' string copy. */
#define strscpy(x, y) {strncpy(x, y, sizeof(x)); \
                       x[sizeof(x) - 1] = 0;}

/* 'Safe' string character copy. */
#define strnscpy(x, y, z) {strncpy(x, y, (z < sizeof(x) ? z : sizeof(x))); \
                           x[sizeof(x) - 1] = 0;}

/* Padded string copy. */
#define strpcpy(x, y) {strncpy(x, y, sizeof(x)); \
                       x[sizeof(x) - 1] = 0; \
                       if (!(x[0])) \
                         { \
                           x[0] = ' '; \
                           x[1] = 0; \
                         }}

/* Get absolute difference in two numbers. */
#define ABSDIFF(a, b) ( ((a) > (b)) ? ((a) - (b)) : ((b) - (a)) )

/* Absolute value. */
#define ABSVAL(a) ( ((a) > 0) ? (a) : (-(a)) )

/* MIN and MAX between two numbers. */
#define CTX_MIN(a, b) ( (a) < (b) ? (a) : (b) )
#define CTX_MAX(a, b) ( (a) > (b) ? (a) : (b) )

/* Absolute MIN and absolute MAX. */
#define CTX_ABSMIN(a, b) ( ABSVAL(a) < ABSVAL(b) ? ABSVAL(a) : ABSVAL(b) )
#define CTX_ABSMAX(a, b) ( ABSVAL(a) > ABSVAL(b) ? ABSVAL(a) : ABSVAL(b) )


/*---------------------------------Standard Constants------------------------*/
/* For use with booleans. */
#define TRUE  1
#define FALSE 0

#define SUCCEED   0                /* For use in exit(). */
#define FAIL    (-1)               /* For exit() and error returns. */

/* Generic exit code status. */
#define EXTSTAT_CMPLT        0     /* Completed with no errors. */
#define EXTSTAT_FAILED       1     /* Failed. */
#define EXTSTAT_NOOP         2     /* Not operational. */
#define EXTSTAT_ERRCMPLT     3     /* Completed with errors. */
#define EXTSTAT_CNTNBL       4     /* Continuable, in progress. */
#define EXTSTAT_UNKWN        5     /* Unknown error. */
#define EXTSTAT_PENDING      6     /* Pending. */

#define EOL '\n'                   /* End of line character. */
#define EOS '\0'                   /* End of string character. */
#define EOP '\14'                  /* End of page (FF) character. */

#ifndef INFTIM
# define INFTIM (-1)               /* Added for AIX 29.08.1993. */
#endif

#ifdef FILENAME_MAX
# undef FILENAME_MAX
# define FILENAME_MAX 512          /* Added for HP 05/11/1995. */
#endif

#define CTX_FILENAME_MAX 512       /* Added because HP use 14 by default. */

/*
 * BLOB_BUFSIZE needs to be large enough (due to Cortex DB queue and FDS)
 * to contain the largest FB sent to FDS.
 */
#define BLOB_BUFSIZE 16384

#endif  /* __PORTABLE_H */

