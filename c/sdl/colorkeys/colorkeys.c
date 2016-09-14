/*
 * Example of simple blitting with colorkeys in SDL.
 */

/*---------------------------------Includes----------------------------------*/
/* Standard C library includes. */
#include <stdio.h>          /* for printf */
#include <stdlib.h>         /* for atexit */

/* Useful libraries includes. */
#include <SDL/SDL.h>        /* for SDL_... functions */

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
    SDL_Surface *che_tux;
    SDL_Surface *ripper_tux;
    SDL_Surface *rock_tux;
    SDL_Surface *viking_tux;
    SDL_Rect src;
    SDL_Rect dest;
    Uint32 colorkey;


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

    /* Load the bitmap files.*/
    background = SDL_LoadBMP("background.bmp");
    if (NULL == background)
      {
        printf("Unable to load bitmap\n");
        return 1;
      }

    che_tux = SDL_LoadBMP("che_tux.bmp");
    if (NULL == che_tux)
      {
        printf("Unable to load bitmap\n");
        return 1;
      }

    ripper_tux = SDL_LoadBMP("ripper_tux.bmp");
    if (NULL == ripper_tux)
      {
        printf("Unable to load bitmap\n");
        return 1;
      }

    rock_tux = SDL_LoadBMP("rock_tux.bmp");
    if (NULL == rock_tux)
      {
        printf("Unable to load bitmap\n");
        return 1;
      }

    viking_tux = SDL_LoadBMP("viking_tux.bmp");
    if (NULL == viking_tux)
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

    /* Draw the penguin without a colorkey. */
    src.x = 0;
    src.y = 0;
    src.w = che_tux->w;
    src.h = che_tux->h;
    dest.x = 30;
    dest.y = 10;
    dest.w = che_tux->w;
    dest.h = che_tux->h;
    SDL_BlitSurface(che_tux, &src, screen, &dest);

    src.x = 0;
    src.y = 0;
    src.w = ripper_tux->w;
    src.h = ripper_tux->h;
    dest.x = 50;
    dest.y = 150;
    dest.w = ripper_tux->w;
    dest.h = ripper_tux->h;
    SDL_BlitSurface(ripper_tux, &src, screen, &dest);

    src.x = 0;
    src.y = 0;
    src.w = viking_tux->w;
    src.h = viking_tux->h;
    dest.x = 140;
    dest.y = 250;
    dest.w = viking_tux->w;
    dest.h = viking_tux->h;
    SDL_BlitSurface(viking_tux, &src, screen, &dest);

    /*
     * The penguin is stored on a blue background.  We can use the
     * SDL_MapRGB function to obtain the correct pixel value for
     * pure blue.
     */
    colorkey = SDL_MapRGB(che_tux->format, 0, 0, 255);

    /*
     * We will now enable this surface's colorkey and draw it again.
     * To turn off the colorkey again, we would replace the
     * SDL_SRCCOLORKEY flag with zero.
     */
    SDL_SetColorKey(che_tux, SDL_SRCCOLORKEY, colorkey);
    src.x = 0;
    src.y = 0;
    src.w = che_tux->w;
    src.h = che_tux->h;
    dest.x = screen->w - che_tux->w - 30;
    dest.y = 10;
    dest.w = che_tux->w;
    dest.h = che_tux->h;
    SDL_BlitSurface(che_tux, &src, screen, &dest);

    /*
     * SDL_RLEACCEL will pack the image for faster display,
     * but be warned that editing this image will become slower.
     */
    SDL_SetColorKey(ripper_tux, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    src.x = 0;
    src.y = 0;
    src.w = ripper_tux->w;
    src.h = ripper_tux->h;
    dest.x = screen->w - ripper_tux->w - 90;
    dest.y = 150;
    dest.w = ripper_tux->w;
    dest.h = ripper_tux->h;
    SDL_BlitSurface(ripper_tux, &src, screen, &dest);

    SDL_SetColorKey(rock_tux, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    src.x = 0;
    src.y = 0;
    src.w = rock_tux->w;
    src.h = rock_tux->h;
    dest.x = 230;
    dest.y = 20;
    dest.w = rock_tux->w;
    dest.h = rock_tux->h;
    SDL_BlitSurface(rock_tux, &src, screen, &dest);

    SDL_SetColorKey(viking_tux, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    src.x = 0;
    src.y = 0;
    src.w = viking_tux->w;
    src.h = viking_tux->h;
    dest.x = screen->w - viking_tux->w - 160;
    dest.y = 210;
    dest.w = viking_tux->w;
    dest.h = viking_tux->h;
    SDL_BlitSurface(viking_tux, &src, screen, &dest);

    /* Ask SDL to update the entire screen. */
    SDL_UpdateRect(screen, 0, 0, 0, 0);

    /* Pause for a few seconds as the viewer gaps in awe. */
    SDL_Delay(10000);

    /* Free the memory that was allocated to the bitmaps. */
    SDL_FreeSurface(background);
    SDL_FreeSurface(che_tux);
    SDL_FreeSurface(ripper_tux);
    SDL_FreeSurface(rock_tux);
    SDL_FreeSurface(viking_tux);

    return 0;
}

