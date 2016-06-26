#include "../include/binaryTree.h"

// find the common node in a binary tree between two nodes
TreeNumber *findCommonNode(TreeNumber *oneNode, TreeNumber *otherNode)
{
   TreeNumber *tempOtherNode; // for the second loop
   
   // pass through second loop once for each element of first loop
   while(oneNode != NULL)
   {
      tempOtherNode = otherNode;
      
      while(tempOtherNode != NULL)
      {
         if(tempOtherNode == oneNode) // comparison
            return tempOtherNode;
         
         tempOtherNode = tempOtherNode->treeUp; // increment
      }
      
      oneNode = oneNode->treeUp; // increment
   }
   
   // if the arguments are in a binary tree the control should not get
   // to this point
   return NULL;
}
