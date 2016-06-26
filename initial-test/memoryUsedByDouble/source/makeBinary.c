#include "../include/memoryUsedByDouble.h"

// divides the parts to be printed and verify if it's denormalized
void makeBinary(double toWrite, boolean isNegative)
{
   boolean isDenormalized = FALSE;
   
   int theExponent = 0;
   
   // because of precision we do not make the assignement
   // inside the first while
   if(toWrite > 1)
      while((toWrite / FLT_RADIX) >= 1)
      {
         toWrite /= FLT_RADIX;
         theExponent++;
      }
   
   else if(toWrite < 1)
   {
      while(toWrite < 1)
      {
         toWrite *= FLT_RADIX;
         theExponent--;
         printf("toWrite: %lf\n", toWrite);
      }
      
      // an exponent field of zeros denotates a denormalized number
      if(theExponent == -BIAS)
         isDenormalized = TRUE;
   }
   
   // standarizes the exponent field
   theExponent += BIAS;
   
   // print the representation on the screen
   printSignal(isNegative);
   printExponent(theExponent);
   printMantissa(toWrite, isDenormalized);
}
