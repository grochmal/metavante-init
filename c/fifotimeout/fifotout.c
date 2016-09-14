/*
 * fifotout.c
 * Named pipe timeout.
 * Author: Michal Grochmal
 */

/*---------------------------------Includes----------------------------------*/
/* Standard C includes */
#include <stdio.h>                 /* for printf and fprintf */
#include <string.h>                /* for strncpy */

/* Standard POSIX includes */
#include <sys/stat.h>              /* for mkfifo */
#include <sys/types.h>             /* for mkfifo */
#include <signal.h>                /* for signal */
#include <fcntl.h>                 /* for open */
#include <unistd.h>                /* for alarm, read, close and unlink */

/*---------------------------------Macros------------------------------------*/
#define MEM_BUFLEN 12              /* Size of memory to write each time. */
#define FIFO_PATHLEN 12            /* Size of path for FIFO name. */

/*---------------------------------Statics-----------------------------------*/
static char M_fifonm[FIFO_PATHLEN] = "";
static char M_fd = -1;

/*---------------------------------Prototypes--------------------------------*/
static void alarm_handler(int signal);
static int process(void);
static void uninit(void);


/*
 * Function: alarm_handler
 *
 * Purpose: Handles SIGALRM to timeout the FIFO.
 *
 * Parameters: signal - The signal received by the process,
 *                      can be any POSIX signal.
 *
 * Returns:
 *
 * Comments:
 */
static void alarm_handler(int signal)
{
    if (SIGALRM == signal)
      {
        fprintf(stderr, "Received SIGALARM\n");
        uninit();
      }
}


/*
 * Function: process
 *
 * Purpose: Set an alarm and a FIFO, expects to read something
 *          from the FIFO before the alarm triggers.
 *
 * Parameters:
 *
 * Returns: 0 - Was able to read from the FIFO.
 *          -1 - FIFO timeout or internal error.
 *
 * Comments: Notice the disabling of the alarm after successful
 *           reading by passing zero to the alarm function.
 */
static int process(void)
{
    int ret = 0;
    char mem[FIFO_PATHLEN + 1];



    alarm(3);
    M_fd = open(M_fifonm, O_RDONLY);
    printf("FIFO already tried\n");
    alarm(0);

    if (-1 != M_fd)
      {
        ret = read(M_fd, mem, FIFO_PATHLEN );
        mem[sizeof(mem) - 1] = '\0';
        if (-1 == ret)
            printf("Got nothing from FIFO\n");
        else
            printf("Got [%s] from FIFO\n", mem);
      }
    else
      {
        printf("FIFO returned -1\n");
      }

    return ret;
}


/*
 * Function: uninit
 *
 * Purpose: Cleans any left opened resources.
 *
 * Parameters:
 *
 * Returns:
 *
 * Comments: Notice that this is also called when SIGALRM is received
 *           to unlink the FIFO and inform us that we timed out.
 */
static void uninit(void)
{
    if(-1 != M_fd)
      {
        close(M_fd);
        M_fd = -1;
      }

    if(M_fifonm[0])
      {
        unlink(M_fifonm);
        M_fifonm[0] = '\0';
      }
}


/*
 * Function: main
 *
 * Purpose: Runs the application.
 *
 * Parameters: argc, argv - Usual suspects.
 *
 * Returns: 0 - Everything worked as expected.
 *          1 - An initialization error happened.
 *
 * Comments: Notice that this is also called when SIGALRM is received
 *           to unlink the FIFO and inform us that we timed out.
 */
int main(int argc, char **argv)
{
    int ret = 0;


    if (2 > argc)
      {
        printf("Usage: %s fifoname\n", argv[0]);
        return -1;
      }

    signal(SIGALRM, alarm_handler);
    strncpy(M_fifonm, argv[1], sizeof(M_fifonm) - 1);
    mkfifo(M_fifonm, 0660);

    ret = process();

    uninit();

    printf("Returning normally from main, success!\n");
    return ret;
}

