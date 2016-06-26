#include "../include/binaryTree.h"

// build next leaf on the binary tree and append it to the upper leaf
void buildTree(TreeNumber *leftNode, TreeNumber *rigthNode,
   directionOf leafSide)
{
   TreeNumber *middleNode;
   
   middleNode = findMiddleNode(leftNode, rigthNode); // find middle
   
   // determine in wich direction the this leaf came from the above
   switch(leafSide)
   {
      case MIDDLE: // this is the upper leaf
         middleNode->treeUp = NULL;
         break;
      
      case LEFT: // came in left direction from a rigth node
         middleNode->treeUp = rigthNode->nextNode;
         break;
      
      case RIGTH: // came in rigth direction from a left node
         middleNode->treeUp = leftNode->previousNode;
         break;
   }
   
   // if leftNode is the same as rigthNode, the middleNode also points
   // to the same thing, therefore the job is done 
   if(leftNode == rigthNode)
      return;
   
   // if middleNode isn't the first node in area beeing build theres
   // more nodes to the left, build a smaller tree from them and append
   // it on the left of middle node
   if(middleNode != leftNode)
      buildTree(leftNode, middleNode->previousNode, LEFT);
   
   // if middleNode isn't the last node in area being build theres more
   // nodes to the rigth, build a smaller tree from them and append it 
   // on the rigth of middle node
   if(middleNode != rigthNode)
      buildTree(middleNode->nextNode, rigthNode, RIGTH);
   
   return;
}
