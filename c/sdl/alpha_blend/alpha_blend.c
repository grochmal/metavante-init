/*
 * Example of alpha blending with SDL.
 */

/*---------------------------------Includes----------------------------------*/
/* Standard C library includes. */
#include <stdio.h>          /* for printf */
#include <stdlib.h>         /* for atexit */

/* Useful libraries includes. */
#include <SDL/SDL.h>        /* for SDL_... functions */
#include <SDL/SDL_image.h>  /* for IMG_Load */

/*---------------------------------Macros------------------------------------*/
#define SCREEN_WIDTH        640     /* Number of pixels in each row. */
#define SCREEN_HEIGHT       400     /* Number of rows in the screen. */
#define SCREEN_COLOR_MODE   16      /* Color scheme used, 16 bits per pixel. */


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
int main(void)
{
    SDL_Surface *screen;
    SDL_Surface *background;
    SDL_Surface *ripper_tux;
    SDL_Surface *viking_tux;
    SDL_Rect src;
    SDL_Rect dest;


    /* Initialize SDL's video system and check for errors. */
    if (0 != SDL_Init(SDL_INIT_VIDEO))
      {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
      }

    /* Make sure SDL_Quit gets called when the program exits! */
    atexit(SDL_Quit);

    /* Attempt to set a 640x400 hicolor (16 bit) video mode. */
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT,
                              SCREEN_COLOR_MODE, 0);
    if (NULL == screen)
      {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return 1;
      }

    /*
     * Load the bitmap files.  The first file was created with an
     * alpha channel, and the second was not.  Notice that we are
     * now using IMG_Load instead of SDL_LoadBMP.
     */
    background = IMG_Load("background.png");
    if (NULL == background)
      {
        printf("Unable to load bitmap\n");
        return 1;
      }

    ripper_tux = IMG_Load("ripper_tux.jpg");
    if (NULL == ripper_tux)
      {
        printf("Unable to load bitmap\n");
        return 1;
      }

    viking_tux = IMG_Load("viking_tux.png");
    if (NULL == viking_tux)\
      {
        printf("Unable to load bitmap\n");
        return 1;
      }

    /* Draw the background. */
    src.x = 0;
    src.y = 0;
    src.w = background->w;
    src.h = background->h;
    dest.x = 0;
    dest.y = 0;
    dest.w = background->w;
    dest.h = background->h;
    SDL_BlitSurface(background, &src, screen, &dest);

    /*
     * Draw the image, which has an alpha channel.  We must
     * specifically enable alpha blending.
     */
    SDL_SetAlpha(viking_tux, SDL_SRCALPHA | SDL_RLEACCEL, 0);
    src.x = 0;
    src.y = 0;
    src.w = viking_tux->w;
    src.h = viking_tux->h;
    dest.x = 80;
    dest.y = 100;
    dest.w = viking_tux->w;
    dest.h = viking_tux->h;
    SDL_BlitSurface(viking_tux, &src, screen, &dest);

    /*
     * Draw the second image, which has no alpha channel.  Instead,
     * we will set a 50% transparency factor for the entire surface.
     * SDL_MapRGB function to obtain the correct pixel value for
     * pure blue.
     */
    SDL_SetAlpha(ripper_tux, SDL_SRCALPHA, 64);
    src.x = 0;
    src.y = 0;
    src.w = ripper_tux->w;
    src.h = ripper_tux->h;
    dest.x = 360;
    dest.y = 100;
    dest.w = ripper_tux->w;
    dest.h = ripper_tux->h;
    SDL_BlitSurface(ripper_tux, &src, screen, &dest);

    /* Ask SDL to update the entire screen. */
    SDL_UpdateRect(screen, 0, 0, 0, 0);

    /* Pause for a few seconds as the viewer gaps in awe. */
    SDL_Delay(6000);

    /* Free the memory that was allocated to the bitmaps. */
    SDL_FreeSurface(background);
    SDL_FreeSurface(ripper_tux);
    SDL_FreeSurface(viking_tux);

    return 0;
}

