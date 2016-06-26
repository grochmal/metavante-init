#include "../include/memoryUsedByDouble.h"

// if double is too great print the special infinity representation
void printInfinity(boolean isNegative)
{
   fputs("\nThe number is too ", stdout);
   fputs((isNegative == TRUE) ? "negative" : "big", stdout);
   fputs(" to be inserted in a double.\n\
It is treated as infinity, and is represented in a special manner.\n\
Try long double or quadruple instead for a more precise number.\n\
The representation (", stdout);
   fputs((isNegative == TRUE) ? "-" : "", stdout);
   fputs("infinity) is:\nsignal = ", stdout);
   fputs((isNegative == TRUE) ? "1" : "0", stdout);
   fputs("\nexponent = 1111 1111 111\n\
mantissa = 0000 0000 0000 0000 0000 0000 0000 0000 \
0000 0000 0000 0000 0000\n\n", stdout);
}
