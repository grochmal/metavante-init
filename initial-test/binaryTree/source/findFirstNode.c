#include "../include/binaryTree.h"

// change node until find TreeNumber->previousNode = NULL
TreeNumber *findFirstNode(TreeNumber *anyNode)
{
   while(anyNode->previousNode != NULL)
      anyNode = anyNode->previousNode;
   
   return anyNode;
}
