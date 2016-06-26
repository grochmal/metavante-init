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
