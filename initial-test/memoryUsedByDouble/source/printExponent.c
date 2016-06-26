#include "../include/memoryUsedByDouble.h"

// print the line of the exponent contents
void printExponent(int theExponent)
{
   char exponentField[EXPONENT_LENGTH];
   
   int count;
   
   // back forth for an easier algorythm
   for(count = EXPONENT_LENGTH - 1; count >= 0; count--)
   {
      exponentField[count] =
         (theExponent % FLT_RADIX) ? '1' : '0';
      theExponent /= 2;
   }
   
   fputs("exponent = ", stdout);
   
   // loop again now for printing
   for(count = 0; count < EXPONENT_LENGTH; count++)
   {
      printf("%c", exponentField[count]);
      
      // for a clearer output
      if(!((count + 1) % CLEAR_OUTPUT))
         fputs(" ", stdout);
   }
   fputs("\n", stdout);
}
