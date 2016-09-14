/*
 * Use entire screen for 2 seconds.
 */

/*---------------------------------Includes---------------------------------*/
/* Standard C library includes. */
#include <stdio.h>          /* for printf */
#include <stdlib.h>         /* for atexit */

/* Standard POSIX includes. */
#include <unistd.h>         /* for sleep */

/* Useful libraries includes. */
#include <SDL/SDL.h>        /* for SDL_... functions */


/*
 * Function: main
 *
 * Purpose: Runs the application.
 *
 * Parameters:
 *
 * Returns: 0 - Everything worked as expected.
 *          1 - An initialization error happened.
 *
 * Comments:
 */
int
main(void)
{
    SDL_Surface *screen;


    /* Initialize SDL's video system and check for errors. */
    if (0 != SDL_Init(SDL_INIT_VIDEO))
      {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
      }

    /* Make sure SDL_Quit gets called when the program exits! */
    atexit(SDL_Quit);

    /* Attempt to set a 640x480 hicolor video mode. */
    screen = SDL_SetVideoMode(640, 480, 16, SDL_FULLSCREEN);
    if (NULL == screen)
      {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return 1;
      }

    /* If we got this far, everything worked. */
    printf("Success!\n");

    /* Wait a bit with the screen taken by the program. */
    sleep(2);

    return 0;
}

