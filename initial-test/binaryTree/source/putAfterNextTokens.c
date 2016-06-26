#include "../include/binaryTree.h"

// return a pointer to the next part of text after a specified token
// if there are no more tokens return a null pointer
char *putAfterNextTokens(char *stringToMove, char token)
{
   while(*stringToMove != token && *stringToMove != '\0')
      stringToMove++;
   
   // reached end of string and token was not found
   if(*stringToMove == '\0')
      return NULL;
   
   // increment the position of pointer in the string
   // verify if there is no more tokens after the first token found,
   // if there is increment the pointer again
   while(*stringToMove == token)
      stringToMove++;
   // it's important because the user can make a misstype,
   // for example putting two spaces in place of one
   
   // again, in case of tokens on the end of string
   if(*stringToMove == '\0')
      return NULL;
   
   return stringToMove;
}
