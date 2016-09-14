/*
 * Example of direct pixel access with SDL.
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

/*---------------------------------Prototypes--------------------------------*/
static Uint16 CreateHicolorPixel(SDL_PixelFormat *fmt,
                                 Uint8 red, Uint8 green, Uint8 blue);


/*
 * Function: CreateHicolorPixel.
 *
 * Purpose: Wraps around SDL_PixelFormat to produce the correct pixel
 *          color independent of the hardware used.
 *
 * Parameters: fmt - The pixel format from SDL_Surface->format on which
 *                   the pixel will be displayed.
 *             red - Red component of the pixel (in RGB format).
 *             green - Green component of the pixel (in RGB format).
 *             blue - Blue component of the pixel (in RGB format).
 *
 * Returns: The color of the pixel that can be directly displayed on
 *          the screen, it may be in 565, 655 or 556 format.
 *
 * Comments:
 */
static Uint16 CreateHicolorPixel(SDL_PixelFormat *fmt,
                                 Uint8 red, Uint8 green, Uint8 blue)
{
    Uint16 value;


    /*
     * This series of bit shifts uses the information from the
     * SDL_Format structure to correctly compose a 16 bit pixel value
     * from 8 bit red, green and blue data.
     */
    value = ((red >> fmt->Rloss) << fmt->Rshift) +
            ((green >> fmt->Gloss) << fmt->Gshift) +
            ((blue >> fmt->Bloss) << fmt->Bshift);

    return value;
}


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
    Uint16 *raw_pixels;
    int x;
    int y;


    /* Initialize SDL's video system and check for errors. */
    if (0 != SDL_Init(SDL_INIT_VIDEO))
      {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
      }

    /* Make sure SDL_Quit gets called when the program exits! */
    atexit(SDL_Quit);

    /*
     * Attempt to set a 256x256 hicolor (16 bit) video mode.
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
     * Video memory can be strange, and it's sometimes necessary to
     * *lock* it before it can be modified.  SDL abstracts this with
     * the SDL_LockSurface function.
     */
    SDL_LockSurface(screen);

    /* Get a pointer to the video surface's memory. */
    raw_pixels = (Uint16 *)screen->pixels;

    /*
     * We can now safely write to the video surface.  We'll draw a nice
     * gradient pattern by varying our red and blue components along
     * the X and Y axes.  Notice the formula used to calculate the
     * offset into the framebuffer for each pixel (the pitch is the
     * number of bytes per scanline in memory).
     */
    for (x = 0; x < SCREEN_WIDTH; x++)
      {
        for (y = 0; y < SCREEN_HEIGHT; y++)
          {
            Uint16 pixel_color;
            int offset;


            pixel_color = CreateHicolorPixel(screen->format,
                                             x, 0, y);
            offset = (screen->pitch / 2 * y + x);
            raw_pixels[offset] = pixel_color;
          }
      }

    /* We are finished drawing, so unlock the surface. */
    SDL_UnlockSurface(screen);

    /*
     * Inform SDL that the screen has been changed.  This is necessary
     * because SDL's screen surface is not always the real framebuffer;
     * it is sometimes emulated behind the scenes.
     */
    SDL_UpdateRect(screen, 0, 0, 0, 0);

    /* Some data for a better understanding of the program. */
    printf("screen->pitch is: [%d],\n"
           "Rloss is [%02x] and Rshift is [%02x],\n"
           "Gloss is [%02x] and Gshift is [%02x],\n"
           "Bloss is [%02x] and Bshift is [%02x],\n"
           "Aloss is [%02x] and Ashift is [%02x],\n"
           "The masks are:\n"
           "Red [%04x]\n"
           "Green [%04x]\n"
           "Blue [%04x]\n"
           "Alpha [%04x]\n",
           screen->pitch,
           screen->format->Rloss, screen->format->Rshift,
           screen->format->Gloss, screen->format->Gshift,
           screen->format->Bloss, screen->format->Bshift,
           screen->format->Aloss, screen->format->Ashift,
           screen->format->Rmask,
           screen->format->Gmask,
           screen->format->Bmask,
           screen->format->Amask);

    /* Pause for a few seconds as the viewer gaps in awe. */
    SDL_Delay(3000);

    return 0;
}

