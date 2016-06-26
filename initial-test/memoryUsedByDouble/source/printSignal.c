#include "../include/memoryUsedByDouble.h"

// print the info text and the first part of representation
void printSignal(boolean isNegative)
{
   fputs("\nThe number representation is:\nsignal = ", stdout);
   fputs((isNegative == TRUE) ? "1" : "0", stdout);
   fputs("\n", stdout);
}
