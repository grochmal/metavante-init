/*
 * Example of simple blitting with SDL.
 */

/*---------------------------------Includes----------------------------------*/
/* Standard C library includes. */
#include <stdio.h>          /* for printf */
#include <stdlib.h>         /* for atexit */

/* Useful libraries includes. */
#include <SDL/SDL.h>        /* for SDL_... functions */

/*---------------------------------Macros------------------------------------*/
#define SCREEN_WIDTH        512     /* Number of pixels in each row. */
#define SCREEN_HEIGHT       256     /* Number of rows in the screen. */
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
    SDL_Surface *image;
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

    /*
     * Attempt to set a 512x256 hicolor (16 bit) video mode.
     * This will set some type of 16 bit mode, but we won't know which
     * particular pixel format ahead of time.  If the video card can't
     * handle hicolor modes, SDL will emulate it.
     */
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT,
                              SCREEN_COLOR_MODE, 0);
    if (NULL == screen)
      {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return 1;
      }

    /*
     * Load the bitmap file.  SDL_LoadBMP returns a pointer to a new
     * surface containing the loaded image.
     */
    image = SDL_LoadBMP("test_image.bmp");
    if (NULL == image)
      {
        printf("Unable to load bitmap\n");
        return 1;
      }

    /*
     * The SDL blitting function needs to know how much data to copy.
     * We provide this with SDL_Rect structures, which define the
     * source and destination rectangles.  The areas should be the
     * same;  SDL does not currently handle image stretching.
     */
    src.x = 0;
    src.y = 0;
    src.w = image->w;  /* Copy the entire image. */
    src.h = image->h;

    dest.x = 0;
    dest.y = 0;
    dest.w = image->w;
    dest.h = image->h;

    /*
     * Draw the bitmap to the screen.  We are using a hcolor video
     * mode, so we don't have to worry about colormap silliness.
     * It is not necessary to lock surfaces before blitting; SDL
     * will handle that.
     */
    SDL_BlitSurface(image, &src, screen, &dest);

    /* Ask SDL to update the entire screen. */
    SDL_UpdateRect(screen, 0, 0, 0, 0);

    /* Pause for a few seconds as the viewer gaps in awe. */
    SDL_Delay(3000);

    /* Free the memory that was allocated to the bitmap. */
    SDL_FreeSurface(image);

    return 0;
}

