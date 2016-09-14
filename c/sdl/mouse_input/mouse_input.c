/******************************************************************************
 * File: mouse_input.c
 *
 * Author(s): Michal Grochmal
 * Copyright (C): This program is free software under GNU GPL.
 *
 * Purpose: Example of simple mouse input with SDL.
 * Comments:
 *****************************************************************************/

/*** Includes ***/
/* third party libraries */
#include <SDL/SDL.h>        /* for SDL_... functions */

/* Standard C */
#include <stdio.h>          /* for printf */
#include <stdlib.h>         /* for atexit */

/*** Macros ***/
#define SCREEN_WIDTH        640     /* Number of pixels in each row. */
#define SCREEN_HEIGHT       400     /* Number of rows in the screen. */
#define SCREEN_COLOR_MODE   16      /* Color scheme used, 16 bits per pixel. */


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
    SDL_Surface *screen;
    SDL_Event event;


    /* Initialize SDL's video system and check for errors. */
    if (0 != SDL_Init(SDL_INIT_VIDEO))
      {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
      }

    /* Make sure SDL_Quit gets called when the program exits! */
    atexit(SDL_Quit);

    /*
     * Attempt to set a 640x400 hicolor (16 bit) video mode
     * with a double buffer.
     */
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT,
                              SCREEN_COLOR_MODE, SDL_DOUBLEBUF);
    if (NULL == screen)
      {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return 1;
      }

    /*
     * Start the event loop.  Keep reading event until there is an
     * error or the user presses a mouse button.
     */
    while (0 != SDL_WaitEvent(&event))
      {
        /*
         * SDL_WaitEvent has filled our event structure with the next
         * event.  We check it's type field to find out what happened.
         */
        switch (event.type)
          {
            /* The next two event types deal with mouse activity. */
            case SDL_MOUSEMOTION:
                printf("Mouse motion.  ");

                /* SDL provides the current position. */
                printf("New position is (%d, %d).  ",
                       event.motion.x, event.motion.y);

                /* We can also get relative motion. */
                printf("That is a (%d, %d) change.\n",
                       event.motion.xrel, event.motion.yrel);

                break;

            case SDL_MOUSEBUTTONDOWN:
                printf("Mouse button pressed.  ");

                printf("Button %d at (%d, %d)\n",
                       event.button.button,
                       event.button.x, event.button.y);

                break;

            /*
             * The SDL_QUIT event indicates that the windows "Close"
             * button has been pressed.  We can ignore this if we
             * need to, but that tends to make users rather impatient.
             */
            case SDL_QUIT:
                printf("Quit event. Bye.\n");
                exit(0);
          }
      }

    return 0;
}

