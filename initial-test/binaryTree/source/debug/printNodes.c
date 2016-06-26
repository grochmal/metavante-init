#include "../../include/binaryTree.h"
#include "../../include/binaryTreeDebug.h"

// print the dataValue of each node from firstNode to the last node
// in the list
void printNodes(TreeNumber *firstNode)
{
   fputs("The string is: \"", stdout);
   
   while(firstNode->nextNode != NULL) // print until finding last node
   {
      printf("%d ", firstNode->dataValue);
      
      firstNode = firstNode->nextNode;
   }
   
   printf("%d\"\n", firstNode->dataValue); // print last node
}
