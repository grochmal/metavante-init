#include "../../include/binaryTree.h"
#include "../../include/elimineRepeat.h"

// remove a node from a linked list
// this function can remove the node that give you the access to the
// linked list, be careful
void dropNode(TreeNumber *nodeToDrop)
{
   // if node isn't the first node point the node before it to the
   // one after it
   if(nodeToDrop->previousNode != NULL)
      (nodeToDrop->previousNode)->nextNode = nodeToDrop->nextNode;
   
   // if node isn't the last point the node after it to the one before
   // it
   if(nodeToDrop->nextNode != NULL)
      (nodeToDrop->nextNode)->previousNode = nodeToDrop->previousNode;
   
   // free the memory of the node, we don't have access to him afterall
   free(nodeToDrop);
}
