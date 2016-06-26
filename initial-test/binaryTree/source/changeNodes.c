#include "../include/binaryTree.h"

// change two existing nodes in a linked list
// it's important that any one of the two pointers to the nodes
// is not be null
TreeNumber *changeNodes(TreeNumber *nodeA, TreeNumber *nodeB)
{
   // if the both nodes point to the same thing do nothing
   if(nodeA == nodeB)
      return nodeA;
   
   // if the nodes are adjacent use the subfunction instead
   else if(nodeA->nextNode == nodeB)
      return changeAdjacentNodes(nodeA, nodeB);
   
   else if(nodeB->nextNode == nodeA)
      return changeAdjacentNodes(nodeB, nodeA);
   
   // as we know that the nodes are different and not adjacent we can
   // change them without worrying about their precedence
   else
   {
      // to hold pointers wilhe changing between nodes
      TreeNumber *magazineNode;
      
      // first change the pointers in all adjacent nodes
      if(nodeA->previousNode != NULL)
         nodeA->previousNode->nextNode = nodeB;
      
      if(nodeA->nextNode != NULL)
         nodeA->nextNode->previousNode = nodeB;
      
      if(nodeB->previousNode != NULL)
         nodeB->previousNode->nextNode = nodeA;
      
      if(nodeB->nextNode != NULL)
         nodeB->nextNode->previousNode = nodeA;
      
      // now change the effective positions of both nodes
      magazineNode = nodeA->previousNode;
      nodeA->previousNode = nodeB->previousNode;
      nodeB->previousNode = magazineNode;
      
      magazineNode = nodeA->nextNode;
      nodeA->nextNode = nodeB->nextNode;
      nodeB->nextNode = magazineNode;
   }
   
   /* Remember that the pointer passed to changeNodes() still point to *
   * the same point in memory, unless it was one of the pointers       *
   * changed in the function. If you want to change the value of this  *
   * pointer to the other node, pass it as the first argument and      *
   * assign the return of changeNodes() to the pointer.               */
   return nodeB;
}
