#include "../../include/binaryTree.h"
#include "../../include/elimineRepeat.h"

// remove all the repeated nodes from a linked list after the node
// passed as argument, it does not count the values in the nodes before
// it's argument
void elimineRepeatedNodes(TreeNumber *firstNode)
{
   // for the node we are comparing
   TreeNumber *positionNode;
   
   // from firstNode to end
   while(firstNode != NULL)
   {
      positionNode = firstNode->nextNode;
      
      // from next node to actual firstNode to end
      while(positionNode != NULL)
      {
         // compare values in nodes
         if(firstNode->dataValue == positionNode->dataValue)
         {
            // if is repeated remove node from list
            if(positionNode->nextNode != NULL)
            {
               positionNode = positionNode->nextNode;
               dropNode(positionNode->previousNode);
            }
            else // in the case it's the last node
            {
               dropNode(positionNode);
               positionNode = NULL;
            }
         }
         else // is not repeated, continue
            positionNode = positionNode->nextNode;
      } // end inner while
      
      firstNode = firstNode->nextNode; // increment of firstNode
   } // end while
}
