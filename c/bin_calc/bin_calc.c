#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Long unsigned right shift,
 * right shift a signed long as if it where a unsigned long
 * independently of architecture and machine type.
 */
#define LURSHIFT(n, b) (((long)(n) >> (b)) & (0x7fffffffL >> ((b) - 1)))


int main(int argc, char **argv)
{
    unsigned int i = 1;


    if (1 < argc)
        i = atoi(argv[1]);

    printf("i = [%x]\n", i);
    printf("0x7fffffffL >> i = [%lx]\n", 0x7fffffffL >> i);
    printf("0x7fffffffL >> (i - 1) = [%lx]\n", 0x7fffffffL >> (i - 1));

    printf("LURSHIFT(0x88ff, i) = [%lx]\n", LURSHIFT(0x88FF, i));
    printf("LURSHIFT(0xeeee, i) = [%lx]\n", LURSHIFT(0xeeee, i));
    printf("LURSHIFT(-0xeeee, i) = [%lx]\n", LURSHIFT(-0xeeee, i));
    printf("LURSHIFT(0x000000ee, i) = [%lx]\n", LURSHIFT(0x000000ee, i));
    printf("LURSHIFT(-0x11000000, i) = [%lx]\n", LURSHIFT(-0x11000000, i));

    printf("~0 ^ 0 = -1 [%d]\n", ~0 ^ 0);
    printf("~0 ^ -1 = 0 [%d]\n", ~0 ^ -1);
    printf("~0 ^ 1 = -2 [%d]\n", ~0 ^ 1);
    printf("~0 ^ -2 = 1 [%d]\n", ~0 ^ -2);
    printf("~0 << 1 = [%x]\n", ~0 << 1);
    printf("0 >> 1 = [%x]\n", 0 >> 1);
    printf("0x80000000 = [%x] [%u]\n", 0x80000000, 0x80000000);
    printf("0x80000001 = [%x] [%u]\n", 0x80000001, 0x80000001);
    printf("0x80000002 = [%x] [%u]\n", 0x80000002, 0x80000002);

    return 0;
}

