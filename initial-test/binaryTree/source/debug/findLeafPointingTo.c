#include "../../include/binaryTree.h"
#include "../../include/binaryTreeDebug.h"

// find next object pointing to an upperLeaf, starting the search from
// positionNode and going left to rigth
TreeNumber *findLeafPointingTo(TreeNumber *positionNode,
   TreeNumber *upperLeaf)
{
   // as the function start from the positionNode it only ends a 
   // concatenated search after the last node searched
   if(positionNode == NULL)
      return NULL;
   
   // while not got to the last node
   while(positionNode->nextNode != NULL)
   {
      if(positionNode->treeUp == upperLeaf) // pointing node found
         return positionNode;
      
      positionNode = positionNode->nextNode; // increment
   }
   
   // pointing node found on last node
   if(positionNode->treeUp == upperLeaf)
         return positionNode;
   
   return NULL; // not found
}
