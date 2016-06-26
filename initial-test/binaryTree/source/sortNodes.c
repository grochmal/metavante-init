#include "../include/binaryTree.h"

// sort nodes of a linked list, using a quicksort algorithm
void sortNodes(TreeNumber *actualNode, TreeNumber *pivotNode)
{
   // delimits the area being sorted for use on furter recurrency
   TreeNumber *leftFrontier, *rigthFrontier;
   
   leftFrontier = actualNode->previousNode;
   rigthFrontier = pivotNode->nextNode;
   
   // quicksort algorithm
   while(actualNode != pivotNode && pivotNode->nextNode != actualNode)
   {
      // need to move number aftervards the pivotNode
      if(actualNode->dataValue > pivotNode->dataValue)
      {
         // pivotNode is still, but the pointer to actualNode must be
         // actualized
         actualNode = changeNodes(actualNode, pivotNode->previousNode);
         
         // the pointer to pivotNode moves together
         // it's a side effect, but we actually use this side efect
         changeNodes(pivotNode->previousNode, pivotNode);
      }
      // move to next number
      else
         actualNode = actualNode->nextNode;
   }
   
   // if pivotNode isn't the first node in list do the sort to the left
   // of the pivotNode, on the actual area being sorted
   if(leftFrontier == NULL)
   {
      if(pivotNode != findFirstNode(pivotNode))
         sortNodes(findFirstNode(pivotNode), pivotNode->previousNode);
   }
   else if(pivotNode != leftFrontier->nextNode)
      sortNodes(leftFrontier->nextNode, pivotNode->previousNode);
   
   // if pivotNode isn't the last node in list do the sort to the rigth
   // of the pivotNode, on the actual are being sorted
   if(rigthFrontier == NULL)
   {
      if(pivotNode != findLastNode(pivotNode))
         sortNodes(pivotNode->nextNode, findLastNode(pivotNode));
   }
   else if(rigthFrontier->previousNode != pivotNode)
      sortNodes(pivotNode->nextNode, rigthFrontier->previousNode);
   
   return;
}
