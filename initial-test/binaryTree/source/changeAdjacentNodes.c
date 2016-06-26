#include "../include/binaryTree.h"

// change nodes that are adjacent
// it's important that leftNode->nextNode = rigthNode not
// rigthNode->nextNode = leftNode, unless you want a segmantation fault
TreeNumber *changeAdjacentNodes(TreeNumber *leftNode,
   TreeNumber *rigthNode)
{
   // apart from changing miscleaneous nodes, adjacent nodes need to
   // change only two pointers in other nodes
   if(leftNode->previousNode != NULL)
      leftNode->previousNode->nextNode = rigthNode;
   
   if(rigthNode->nextNode != NULL)
      rigthNode->nextNode->previousNode = leftNode;
   
   // note that we don't need a magazine for the changes, because
   // we always have the other adress
   leftNode->nextNode = rigthNode->nextNode;
   rigthNode->nextNode = leftNode;
   
   rigthNode->previousNode = leftNode->previousNode;
   leftNode->previousNode = rigthNode;
   
   // the function change nodes uses this return value, for more
   // information read the comments on changenodes()
   return rigthNode;
}
