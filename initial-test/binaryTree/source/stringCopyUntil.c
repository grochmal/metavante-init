#include "../include/binaryTree.h"

// copy string until specific token or until the end of the string
void stringCopyUntil(char *copyHereString, char *copyFromString,
   char token)
{
   while(*copyFromString != token && *copyFromString != '\0')
      *(copyHereString++) = *(copyFromString++);
   
   *copyHereString = '\0'; // in any case end string
}
