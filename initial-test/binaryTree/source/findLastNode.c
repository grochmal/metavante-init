#include "../include/binaryTree.h"

// change node until find TreeNumber->nextNode = NULL
TreeNumber *findLastNode(TreeNumber *anyNode)
{
   while(anyNode->nextNode != NULL)
      anyNode = anyNode->nextNode;
   
   return anyNode;
}
