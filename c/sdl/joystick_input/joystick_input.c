/******************************************************************************
 * File: joystick_input.c
 *
 * Author(s): Michal Grochmal
 * Copyright (C): This program is free software under GNU GPL.
 *
 * Purpose: Example of simple joystick input with SDL.
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
int
main(void)
{
    SDL_Event event;
    SDL_Joystick *js;
    int num_js;
    int quit_flag;
    int i;


    /* Initialize SDL's video system and check for errors. */
    if (0 != SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_VIDEO))
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
    if (NULL == SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT,
                                 SCREEN_COLOR_MODE, SDL_DOUBLEBUF))
      {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return 1;
      }

    /* Find out how many joysticks are available. */
    num_js = SDL_NumJoysticks();
    printf("SDL recognizes %d joystick(s) on this system.\n", num_js);
    if (0 == num_js)
      {
        printf("No joysticks where detected.\n");
        return 0;
      }

    /* Print out information about each joystick. */
    for (i = 0; i < num_js; i++)
      {
        /* Open the joystick. */
        js = SDL_JoystickOpen(i);

        if (NULL == js)
          {
            printf("unable to open joystick %d.\n", i);
          }
        else
          {
            printf("Joystick %d\n", i);
            printf("\tName:       %s\n", SDL_JoystickName(i));
            printf("\tAxes:       %d\n", SDL_JoystickNumAxes(js));
            printf("\tTrackballs: %d\n", SDL_JoystickNumBalls(js));
            printf("\tButtons:    %d\n", SDL_JoystickNumButtons(js));

            /* Close joystick. */
            SDL_JoystickClose(js);
          }
      }

    /* We will use the first joystick for the demostration. */
    js = SDL_JoystickOpen(0);
    if (NULL == js)
      {
        printf("Unable to open joystick: %s\n", SDL_GetError());
      }

    /* Loop until the user presses Q. */
    quit_flag = 0;
    while (0 != SDL_WaitEvent(&event) && 0 == quit_flag)
      {
        switch (event.type)
          {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_q)
                  {
                    printf("'Q' pressed, exiting.");
                    quit_flag = 1;
                  }

                break;

            /*
             * This event is generated when an axis on an open
             * joystick is moved.  Most joysticks have two axes,
             * X and Y (which will be reported as axes 0 and 1).
             */
            case SDL_JOYAXISMOTION:
                printf("Joystick %d, axis %d movement to %d\n",
                       event.jaxis.which,
                       event.jaxis.axis,
                       event.jaxis.value);

                break;

            case SDL_JOYBUTTONUP:
                /* Fall through to SDL_JOYBUTTONDOWN. */

            case SDL_JOYBUTTONDOWN:
                printf("Joystick %d, button %d: %d\n",
                       event.jbutton.which,
                       event.jbutton.button,
                       event.jbutton.state);

                break;
          }
      }

    /* Close joystick. */
    SDL_JoystickClose(js);

    return 0;
}

