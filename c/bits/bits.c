/******************************************************************************
 * File: template.c
 *
 * Author(s): Michal Grochmal
 * Copyright (C): This program is free software under GNU GPL.
 *
 * Purpose:
 * Comments:
 *****************************************************************************/

/*** Includes ***/
/* local */
/* program libraries */
/* third party libraries */
/* POSIX */
/* Standard C */
#include <stdio.h>                 /* for printf and fprintf */
#include <stdlib.h>                /* for atexit */

/*** Macros ***/
/*** Enums ***/
/*** Typedefs ***/
struct str_byte_t
{
    unsigned int b1 : 1;
    unsigned int b234 : 3;
    unsigned int b5 : 1;
    unsigned int pad : 3;
    unsigned int flag : 1;
    unsigned int a : 7;
    unsigned int b : 7;
    unsigned int c : 7;
    unsigned int d : 7;
    unsigned int e : 7;
    unsigned int f : 7;
    unsigned int g : 7;
    unsigned int h : 7;
};

typedef struct str_byte_t byte_t;

/*** Globals ***/
/*** Statics ***/
/*** Prototypes ***/


/******************************************************************************
 * Function: main
 *
 * Purpose: Run the program
 * Input: argc and argv, usual suspects.
 * Output:
 * Returns: 0 on success.
 *          -1 on failure.
 *
 * Comments:
 *****************************************************************************/
int main(void)
{
    int ret = 0;
    byte_t bits = {1, 8, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


    printf("Bit 1 is [%d]\n", bits.b1 & 0xff);
    printf("Bits 234 are [%d]\n", bits.b234 & 0xff);
    printf("Bit 5 is [%d]\n", bits.b5 & 0xff);
    printf("size is [%d]\n", sizeof(bits));
    printf("size of int is [%d]\n", sizeof(int));

    return ret;
}

