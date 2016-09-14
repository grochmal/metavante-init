/*
 * Animation with SDL, first attempt.
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

#define NUM_TUXES           100     /* Number of penguins on the screen. */
#define MAX_SPEED           6       /* Maximum speed of penguin movement. */
#define FRAME_NUM           300     /* Number of frames to display. */

/*--------------------------------Typedefs-----------------------------------*/
/* This structure stores the information for one on-screen penguin. */
struct str_penguin_t
{
    int x;                         /* Horizontal position on the screen. */
    int y;                         /* Vertical position on the screen. */

    int dx;                        /* Delta x of movement vector. */
    int dy;                        /* Delta y of movement vector. */
};

typedef struct str_penguin_t penguin_t;

/*---------------------------------Statics-----------------------------------*/
static penguin_t penguins[NUM_TUXES];           /* Array of penguins. */

/* These are now static variables, for convenience. */
static SDL_Surface *screen;
static SDL_Surface *viking_tux;


/*
 * This routine loops through the array of penguins and sets each
 * to a random starting position and direction.
 */
static void init_penguins(void)
{
    int i;


    for (i = 0; i < NUM_TUXES; i++)
      {
        penguins[i].x = rand() % screen->w;
        penguins[i].y = rand() % screen->h;
        penguins[i].dx = (rand() % (MAX_SPEED * 2)) - MAX_SPEED;
        penguins[i].dy = (rand() % (MAX_SPEED * 2)) - MAX_SPEED;
      }
}


/*
 * This routine moves each penguin by it's motion vector.
 */
static void move_penguins(void)
{
    int i;


    for (i = 0; i < NUM_TUXES; i++)
      {
        /* Move the penguin by its motion vector. */
        penguins[i].x += penguins[i].dx;
        penguins[i].y += penguins[i].dy;

        /* Turn the penguin around if it hits the edge of the screen. */
        if (0 > penguins[i].x || screen->w - 1 < penguins[i].x)
            penguins[i].dx = -penguins[i].dx;

        if (0 > penguins[i].y || screen->h - 1 < penguins[i].y)
            penguins[i].dy = -penguins[i].dy;
      }
}


/*
 * This routine draws each penguin to the screen surface.
 */
static void draw_penguins(void)
{
    int i;
    SDL_Rect src;
    SDL_Rect dest;


    for (i = 0; i < NUM_TUXES; i++)
      {
        src.x = 0;
        src.y = 0;
        src.w = viking_tux->w;
        src.h = viking_tux->h;

        /*
         * The penguin's position specifies it's center.  We subtract
         * half of it's width and height to get it's upper corner.
         */
        dest.x = penguins[i].x - viking_tux->w / 2;
        dest.y = penguins[i].y - viking_tux->h / 2;
        dest.w = viking_tux->w;
        dest.h = viking_tux->h;

        SDL_BlitSurface(viking_tux, &src, screen, &dest);
      }
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
    SDL_Surface *background;
    SDL_Rect src;
    SDL_Rect dest;
    int frames;


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

    /* Load the bitmap files. */
    background = IMG_Load("background.png");
    if (NULL == background)
      {
        printf("Unable to load bitmap\n");
        return 1;
      }

    viking_tux = IMG_Load("viking_tux.png");
    if (NULL == viking_tux)
      {
        printf("Unable to load bitmap\n");
        return 1;
      }

    /* Set penguin's alpha channel. */
    SDL_SetAlpha(viking_tux, SDL_SRCALPHA | SDL_RLEACCEL, 0);

    /* Initialize the penguin position data. */
    init_penguins();

    /* Animate FRAME_NUM frames (aproximately FRAME_NUM / 30 seconds). */
    for (frames = 0; frames < FRAME_NUM; frames++)
      {
        /* Draw the background. */
        src.x = 0;
        src.y = 0;
        src.w = background->w;
        src.h = background->h;
        dest = src;

        SDL_BlitSurface(background, &src, screen, &dest);

        /* Put the penguins on the screen. */
        draw_penguins();

        /* Ask SDL to update the entire screen. */
        SDL_UpdateRect(screen, 0, 0, 0, 0);

        /* Move the penguins for the next frame. */
        move_penguins();
      }

    /* Free the memory that was allocated to the bitmaps. */
    SDL_FreeSurface(background);
    SDL_FreeSurface(viking_tux);

    return 0;
}

