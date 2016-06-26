#include "../include/binaryTree.h"

// find the node with a certain value in a linked list or returns a
// null pointer
TreeNumber *findNodeWithValue(TreeNumber *firstNode,
   TreeNumber *lastNode, int valueToFind)
{
   TreeNumber *middleNode;
   
   // binary search, after all if we are searching on a binary tree
   // the linked list is sorted
   while(firstNode != lastNode)
   {
      middleNode = findMiddleNode(firstNode, lastNode);
      
      if(middleNode->dataValue == valueToFind)
         return middleNode;
      else if(middleNode->dataValue > valueToFind)
         lastNode = middleNode;
      else
         firstNode = middleNode;
   }
   
   // in case where there is only one node
   if(firstNode->dataValue == valueToFind)
      return firstNode;
   
   return NULL; // nothing found
}
