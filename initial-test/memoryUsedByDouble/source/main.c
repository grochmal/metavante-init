#include "../include/memoryUsedByDouble.h"

// verifies the syntz and divides into possible cases
int main(int argc, char **argv)
{
   boolean isNegative = FALSE;
   
   double readDouble;
   
   // if syntax incorrect pirnt small help
   if(argc != SYNTAX)
   {
      fputs("syntax: memoryUsedByDouble <number>\n", stdout);
      return 0;
   }
   
   // register the number
   sscanf(argv[1], "%lf", &readDouble);
   
   // we can work only on positive values if we store the signal
   // information on a separate variable
   if(readDouble < 0)
   {
      isNegative = TRUE;
      readDouble = -readDouble;
   }
   
   // to small numbers and zero
   if(readDouble < DBL_MIN)
      printZero();
   
   // too great numbers
   else if(readDouble > DBL_MAX)
      printInfinity(isNegative);
   
   // number within range
   else
      makeBinary(readDouble, isNegative);
   
   return 0;
}
