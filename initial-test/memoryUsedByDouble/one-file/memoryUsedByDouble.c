#include <stdio.h>
#include <float.h>

#define BIAS 1023

#define CLEAR_OUTPUT 4

#define EXPONENT_LENGTH 11
#define MANTISSA_LENGTH 52

#define SYNTAX 2

typedef enum
{
   FALSE,
   TRUE
}boolean;

void makeBinary(double toWrite, boolean isNegative);
void printExponent(int theExponent);
void printInfinity(boolean isNegative);
void printMantissa(double toWrite, boolean isDenormalized);
void printSignal(boolean isNegative);
void printZero(void);

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

// print the info text and the first part of representation
void printSignal(boolean isNegative)
{
   fputs("\nThe number representation is:\nsignal = ", stdout);
   fputs((isNegative == TRUE) ? "1" : "0", stdout);
   fputs("\n", stdout);
}

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
