#include "../../include/binaryTree.h"
#include "../../include/binaryTreeDebug.h"

// print nodes of a part of the binary tree in the same order as they
// were created, if you want to print the entire tree pass a null 
// pointer as the second argument
void printTree(TreeNumber *positionNode, TreeNumber *belowThis)
{
   // search all positions of linked list for a node that is below
   // another node
   while((positionNode = findLeafPointingTo(positionNode, belowThis))
      != NULL)
   {
      printf("\nNode containing %d, pointing to -> ", // print node
         positionNode->dataValue);
      
      if(positionNode->treeUp != NULL) // print to where the node point
         printf("%d\n", (positionNode->treeUp)->dataValue);
      else
         fputs("\"NULL\"\n", stdout);
      
      // print the smaller binary tree below the node
      printTree(findFirstNode(positionNode), positionNode);
      
      printf("\n"); // for clearer output
      
      // move to nextNode to search for another node pointing to the
      // original argument passed as the second argument
      positionNode = positionNode->nextNode;
   }
   // if there's nothing found or no nodes, do nothing
}
