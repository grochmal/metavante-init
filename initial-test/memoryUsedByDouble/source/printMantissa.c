#include "../include/memoryUsedByDouble.h"

// print the line of the mantissa contents
void printMantissa(double toWrite, boolean isDenormalized)
{
   char mantissaField[MANTISSA_LENGTH];
   
   int wasOne = 0;
   int count = 0;
   
   toWrite -= 1;
   
   if(isDenormalized == TRUE)
   {
      mantissaField[count] = '1';
      count++;
   }
   
   // the number is 0.something, if the number, radix times, is greater
   // than one print 1 on the field and subtract the value printed from
   // the number. Else print 0 on the field and advance to the next
   // field with the modified number.*/
   for(; count < MANTISSA_LENGTH; count++)
   {
      toWrite = FLT_RADIX * (toWrite - wasOne);
      
      // if the base radix was diferent we shoud test how many times
      // the modified number have the actual value, but with base 2
      // it's only have or not have the value
      if(toWrite >= 1)
      {
         mantissaField[count] = '1';
         wasOne = 1;
      }
      else
      {
         mantissaField[count] = '0';
         wasOne = 0;
      }
   }
   
   fputs("mantissa = ", stdout);
   
   // loop again to print on the screen
   for(count = 0; count < MANTISSA_LENGTH; count++)
   {
      printf("%c", mantissaField[count]);
      
      // for a clearer output
      if(!((count + 1) % CLEAR_OUTPUT))
         fputs(" ", stdout);
   }
   fputs("\n\n", stdout);
}
