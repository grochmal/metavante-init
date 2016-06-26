#include "binaryTree.h"

// for testing purposes
void printCompleteNodes(TreeNumber *firstNode)
{
   while(firstNode->nextNode != NULL)
   {
      printf("\n");
      printf("previousNode = %d\n", firstNode->previousNode);
      printf("value in node = %d\n", firstNode->dataValue);
      printf("thisNode = %d\n", firstNode);
      printf("nextNode = %d\n", firstNode->nextNode);
      printf("\n");
      
      firstNode = firstNode->nextNode;
   }
   printf("\n");
   printf("previousNode = %d\n", firstNode->previousNode);
   printf("value in node = %d\n", firstNode->dataValue);
   printf("thisNode = %d\n", firstNode);
   printf("nextNode = %d\n", firstNode->nextNode);
   printf("\n");
}
