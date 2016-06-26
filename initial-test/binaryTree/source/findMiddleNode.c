#include "../include/binaryTree.h"

// return middle node between firstNode and lastNode
// breaks if lastNode comes before firstNode in the list
TreeNumber *findMiddleNode(TreeNumber *firstNode, TreeNumber *lastNode)
{
   // while there's no middle
   while(firstNode != lastNode)
   {
      lastNode = lastNode->previousNode; // move lastNode left
      
      // test again, and return if find middle
      // so it always round down the middle
      if(firstNode == lastNode)
         return firstNode;
      
      firstNode = firstNode->nextNode; // move firstNode rigth
   }
   
   return firstNode; // retrun middle
}
