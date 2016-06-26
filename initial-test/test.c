#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NumberNode
{
   struct NumberNode *previousNode;
   
   struct NumberNode *treeUp;
   
   int dataValue;
   
   struct NumberNode *nextNode;
}TreeNumber;

typedef enum
{
   FALSE,
   TRUE
}boolean;

TreeNumber *changeNodes(TreeNumber *nodeA, TreeNumber *nodeB);
void printNodes(TreeNumber *firstNode);

int main(int argc, char **argv)
{
   TreeNumber *one, *two, *three, *four;
   
   one = (TreeNumber *) malloc(sizeof(TreeNumber));
   two = (TreeNumber *) malloc(sizeof(TreeNumber));
   three = (TreeNumber *) malloc(sizeof(TreeNumber));
   four = (TreeNumber *) malloc(sizeof(TreeNumber));
   
   one->dataValue = 1;
   two->dataValue = 2;
   three->dataValue = 3;
   four->dataValue = 4;
   
   one->previousNode = NULL;
   two->previousNode = one;
   three->previousNode = two;
   four->previousNode = three;
   
   one->nextNode = two;
   two->nextNode = three;
   three->nextNode = four;
   four->nextNode = NULL;
   
   //one->nextNode->dataValue = 5;
   
   //two->nextNode->nextNode = one;
   
   changeNodes(one, two);
   
   printf("testing form one->nextNode->dataValue: %d\n", one->nextNode->dataValue);
   
   printf("Values: %d %d %d %d\n", one->dataValue, two->dataValue,
      three->dataValue, four->dataValue);
   
   printf("value of one->nextNode->dataValue: %d\n",
      one->nextNode->dataValue);
   
   printNodes(three);
   
   printNodesBackward
   
   return 0;
}

TreeNumber *changeNodes(TreeNumber *nodeA, TreeNumber *nodeB)
{
   TreeNumber *magazineNode, *leftNode, *middleNode, *rigthNode;
   
   boolean isSideBySide = FALSE;
   
   printf("does changeNodes enters?\n");
   
   if(nodeA == nodeB)
      printf("************** one equal ****************\n");
   else
   {
      if(nodeA->nextNode == nodeB || nodeB->nextNode == nodeA)
      {
         isSideBySide = TRUE;
         
         middleNode = (TreeNumber *) malloc(sizeof(TreeNumber));
         
         if(nodeA->nextNode == nodeB)
         {
            leftNode = nodeA;
            rigthNode = nodeB;
         }
         else
         {
            leftNode = nodeB;
            rigthNode = nodeA;
         }
         
         leftNode->nextNode = middleNode;
         
         middleNode->previousNode = leftNode;
         middleNode->nextNode = rigthNode;
         
         rigthNode->previousNode = middleNode;
      }
         
      printf("start changeNodes else\n");
      
      if(nodeA->previousNode != NULL)
         nodeA->previousNode->nextNode = nodeB;
      
      printf("it's the first command if i'am correct\n");
      
      if(nodeA->nextNode != NULL)
         nodeA->nextNode->previousNode = nodeB;
      
      printf("changeNodes else part 2\n");
      
      if(nodeB->previousNode != NULL){printf("Where?\n");
         nodeB->previousNode->nextNode = nodeA;}
      
      if(nodeB->nextNode != NULL)
         nodeB->nextNode->previousNode = nodeA;
      
      printf("ends part 2\n");
      
      magazineNode = (TreeNumber *) malloc(sizeof(TreeNumber));
      
      printf("does it make the alloc memo?\n");
      
      magazineNode = nodeA->previousNode;
      nodeA->previousNode = nodeB->previousNode;
      nodeB->previousNode = magazineNode;
      
      printf("pass trougth the first part?\n");
      
      magazineNode = nodeA->nextNode;
      nodeA->nextNode = nodeB->nextNode;
      nodeB->nextNode = magazineNode;
      
      printf("end function?\n");
      
      if(isSideBySide == TRUE)
      {
         rigthNode->nextNode = leftNode;
         leftNode->previousNode = rigthNode;
         
         //free(middleNode);
      }
      
      printf("is the if?\n");
      
      free(magazineNode);
      
      printf("free magazineNode?\n");
   }
   
   printf("pass else?\n");
   
   return nodeB;
}

// for testing purposes
void printNodes(TreeNumber *firstNode)
{
   fputs("The string was: \"", stdout);
   
   while(firstNode->nextNode != NULL)
   {
      printf("%d ", firstNode->dataValue);
      
      firstNode = firstNode->nextNode;
   }
   
   printf("%d\"\n", firstNode->dataValue);
}
