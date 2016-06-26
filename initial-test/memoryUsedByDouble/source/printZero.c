#include "../include/memoryUsedByDouble.h"

// if our double is zero print the special zero representation
void printZero(void)
{
   fputs("\nThe double format treat this number as zero.\n\
Maybe the number is too small to be represented as a double,\n\
Try long double or quadruple instead for a more precise number.\n\
The representation of zero in a double is special,\n\
but the two different values +0 and -0 are considered as equals.\n\
Also the -0 is not considered a negative number\n\
The binary representation is:\n\
signal = 0 or 1 (for +0 and -0 respectively)\n\
exponent = 0000 0000 000\n\
mantissa = 0000 0000 0000 0000 0000 0000 0000 0000 \
0000 0000 0000 0000 0000\n\n", stdout);
}
