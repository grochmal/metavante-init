/******************************************************************************
 * File: threads.c
 *
 * Author(s): Michal Grochmal
 * Copyright (C): This program is free software under GNU GPL.
 *
 * Purpose: Example of SDL's portable threading API.
 * Comments:
 *****************************************************************************/

/*** Includes ***/
/* third party libraries */
#include <SDL/SDL.h>         /* for SDL_... functions */
#include <SDL/SDL_thread.h>  /* for Thread and Mutex functions */

/* Standard C */
#include <stdio.h>           /* for printf */
#include <stdlib.h>          /* for atexit and rand */

/*** Macros ***/
#define SCREEN_WIDTH        640     /* Number of pixels in each row. */
#define SCREEN_HEIGHT       400     /* Number of rows in the screen. */
#define SCREEN_COLOR_MODE   16      /* Color scheme used, 16 bits per pixel. */

/*** Statics ***/
static int _counter = 0;
static SDL_mutex *_p_counter_mutex;
/* Three threads will run until this flag is set. */
static int _exit_flag = 0;

/*** Prototypes **/
static int ThreadEntryPoint(void *data);


/******************************************************************************
 * Function: main
 *
 * Purpose: Run the program
 * Returns: 0 on success.
 *          1 on failure.
 *
 * Comments:
 *****************************************************************************/
int main(void)
{
    SDL_Thread *thread1;
    SDL_Thread *thread2;
    SDL_Thread *thread3;


    /* Create a mutex to protect the counter. */
    _p_counter_mutex = SDL_CreateMutex();

    printf("Pres Ctrl-C to exit the program.\n");

    /* Create three threads. Give each thread a name as it's data. */
    thread1 = SDL_CreateThread(ThreadEntryPoint, "Thread 1");
    thread2 = SDL_CreateThread(ThreadEntryPoint, "Thread 2");
    thread3 = SDL_CreateThread(ThreadEntryPoint, "Thread 3");

    /* Let the threads run until the counter reaches 20.*/
    while (_counter < 20)
        SDL_Delay(1000);

    /* Signal the threads to exit. */
    _exit_flag = 1;
    printf("_exit_flag has been set by main\n");

    /* Give them time to notice the flag and exit. */
    SDL_Delay(3500);

    /* Destroy the counter mutex. */
    SDL_DestroyMutex(_p_counter_mutex);

    return 0;
}


/******************************************************************************
 * Function: ThreadEntryPoint
 *
 * Purpose: This function is a thread entry point.
 * Returns: 0 for success (always).
 *
 * Comments:
 *****************************************************************************/
static int ThreadEntryPoint(void *data)
{
    char *threadname;


    /*
     * Anything can be passed as thread data, we
     * will use it a thread name.
     */
    threadname = (char *)data;

    /* Loop until main sets the exit flag. */
    while (0 == _exit_flag)
      {
        printf("This is %s! ", threadname);

        /* Get a lock on the counter variable. */
        SDL_mutexP(_p_counter_mutex);

        /* We can now safely modify the counter. */
        printf("The countet is currently %d\n", _counter);
        _counter++;

        /* Release the lock on the counter variable. */
        SDL_mutexV(_p_counter_mutex);

        /* Delay for a random amount of time. */
        SDL_Delay(rand() % 3000);
      }

    printf("%s is now exiting.\n", threadname);

    return 0;
}

