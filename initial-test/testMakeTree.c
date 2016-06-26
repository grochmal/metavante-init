// testMakeTree.c
// tah ok!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NumberNode
{
   struct NumberNode *previousNode;
   
   int dataValue;
   
   struct NumberNode *nextNode;
}TreeNumber;

typedef enum
{
   FALSE,
   TRUE
}boolean;

TreeNumber *makeTree(char *lineArgument);
char *putAfterNextToken(char *stringToMove, char token);
void stringCopyUntil(char *firstString, char *secondString, char token);

int main(void)
{
   TreeNumber *firstNode;
   
   char *str = "23 46 69 112 13 144"; // 6 nodes
   
   printf("\noriginal string = \"%s\"\n", str);
   
   firstNode = makeTree(str);
   
   printf("\n");
   printf("firstNode->previousNode = %d\n", firstNode->previousNode);
   printf("firstNode->dataValue = %d\n", firstNode->dataValue);
   printf("firstNode->nextNode = %d\n", firstNode->nextNode);
   printf("firstNode adress = %d\n", firstNode);
   
   firstNode = firstNode->nextNode; // node 2
   
   printf("\n");
   printf("secondNode->previousNode = %d\n", firstNode->previousNode);
   printf("secondNode->dataValue = %d\n", firstNode->dataValue);
   printf("secondNode->nextNode = %d\n", firstNode->nextNode);
   printf("secondNode adress = %d\n", firstNode);
   
   firstNode = firstNode->nextNode; // node 3
   
   printf("\n");
   printf("thirdNode->previousNode = %d\n", firstNode->previousNode);
   printf("thirdNode->dataValue = %d\n", firstNode->dataValue);
   printf("thirdNode->nextNode = %d\n", firstNode->nextNode);
   printf("thirdNode adress = %d\n", firstNode);
   
   firstNode = firstNode->nextNode; // node 4
   
   printf("\n");
   printf("fourthNode->previousNode = %d\n", firstNode->previousNode);
   printf("fourthNode->dataValue = %d\n", firstNode->dataValue);
   printf("fourthNode->nextNode = %d\n", firstNode->nextNode);
   printf("fourthNode adress = %d\n", firstNode);
   
   firstNode = firstNode->nextNode; // node 5
   
   printf("\n");
   printf("fifthNode->previousNode = %d\n", firstNode->previousNode);
   printf("fifthNode->dataValue = %d\n", firstNode->dataValue);
   printf("fifthNode->nextNode = %d\n", firstNode->nextNode);
   printf("fifthNode adress = %d\n", firstNode);
   
   firstNode = firstNode->nextNode; // node 6
   
   printf("\n");
   printf("sixthNode->previousNode = %d\n", firstNode->previousNode);
   printf("sixthNode->dataValue = %d\n", firstNode->dataValue);
   printf("sixthNode->nextNode = %d\n", firstNode->nextNode);
   printf("sixthNode adress = %d\n", firstNode);
   printf("\n");
   
   return 0;
}

// make the binary tree from the string imput and returns a pointer
// to the first element of the sorted tree
TreeNumber *makeTree(char *stringTree)
{
   // one pointe for return, one for current node and one for
   // the node being read
   TreeNumber *firstNode, *actualNode, *readNode;
   
   // to be certain that atoi() will work lets copy the values
   // from the input to a smaller string
   // smallString <= stringTree so the max lenght should be stringTree
   char smallString[strlen(stringTree)];
   
   // the adress of the first node is maintained for performance
   // purposes (to not have to return all nodes at the end)
   firstNode = (TreeNumber *) malloc(sizeof(TreeNumber));
   actualNode = firstNode;
   
   // copy the first member of the tree, if there is only one member
   // putAfterNextToken will return a null pointer
   stringCopyUntil(smallString, stringTree, ' ');
   stringTree = putAfterNextToken(stringTree, ' ');
   
   // set up the first node
   actualNode->dataValue = atoi(smallString);
   actualNode->previousNode = NULL;
   
   // if there are more than one items make the list the while
   // executes until there are no more items
   while(stringTree != NULL)
   {
      // allocate memory for next item
      readNode = (TreeNumber *) malloc(sizeof(TreeNumber));
      
      // copy for atoi() because it not register preceding spaces
      stringCopyUntil(smallString, stringTree, ' ');
      stringTree = putAfterNextToken(stringTree, ' ');;
      
      // set up next node
      readNode->dataValue = atoi(smallString);
      
      // set the relationship between nodes
      actualNode->nextNode = readNode;
      readNode->previousNode = actualNode;
      
      // now the actual node is the next node
      actualNode = readNode;
   }
   
   // after the while we are at the last node, lets mark it the last
   actualNode->nextNode = NULL;
   
   return firstNode;
}

// return a pointer to the next part of text after a specified token
// if there are no more tokens return a null pointer
char *putAfterNextToken(char *stringToMove, char token)
{
   while(*stringToMove != token && *stringToMove != '\0')
      stringToMove++;
   
   // token found
   if(*stringToMove == token)
      return ++stringToMove; // return next position;
   
   // token not found
   return NULL;
}

// copy string until specific token or until the end of the string
void stringCopyUntil(char *firstString, char *secondString, char token)
{
   while(*secondString != token && *secondString != '\0')
      *(firstString++) = *(secondString++);
   
   *firstString = '\0'; // in any case end string
}
