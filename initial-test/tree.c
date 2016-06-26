/***********************************************************************
* tree.c a program that disigns a binary tree form the user's input    *
* and find common nodes for values (also from the imput).              *
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************************
* We are going to use a struct as one part of the binary tree, this    *
* way we don't bother with the size of the string imputed by the user. *
* The memory for the tree is allocated dynamycally so only hardware    *
* limitations hinder the size of our tree.                             *
***********************************************************************/
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

// work of functions stated below
TreeNumber *changeNodes(TreeNumber *nodeA, TreeNumber *nodeB);
TreeNumber *findFirstNode(TreeNumber *anyNode);
TreeNumber *findLastNode(TreeNumber *anyNode);
TreeNumber *makeTree(char *stringTree);
void printNodes(TreeNumber *firstNode);
char *putAfterNextToken(char *stringToMove, char token);
void sortNodes(TreeNumber *firstNode, TreeNumber *lastNode);
void stringCopyUntil(char *firstString, char *secondString, char token);

// test the input and divides actions on the program
int main(int argc, char **argv)
{
   // our linked list
   TreeNumber *firstNode, *lastNode;
   
   // if the input isn't the desired inform the user about the syntax
   // woks even with tree -?, tree -h and tree --help :)
   if(argc != 4)
   {
      fputs("\n\ntree\n\n", stdout);
      fputs("A binary tree builder porgram\n", stdout);
      fputs("usage:\n\n", stdout);
      fputs("tree <\"string containing int values\"> ", stdout);
      fputs("<First Value> <Second Value>\n\n", stdout);
      fputs("tree build the bianry tree make binary search ", stdout);
      fputs("for both values and return\nthe lowest common ", stdout);
      fputs("node between them\n\n", stdout);
      fputs("exmaple:\n", stdout);
      fputs("tree \"23 12 45 123 56 8 19 14 96 3\" 96 45\n\n", stdout);
      
      return 0;
   }
   
   // we need only the first member of a linked list
   firstNode = makeTree(argv[1]);
   
   // find lastNode for our sort function
   lastNode = findLastNode(firstNode);
   printf("the find last node is ok!\n");
   // a binary search couldn't be done without an orginized list
   sortNodes(firstNode, lastNode);
   printf("the sortNodes not?\n");
   printNodes(firstNode);
   
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
      printf("seg fault is here!!\n");
      
      if(nodeA->nextNode == nodeB || nodeB->nextNode == nodeA)
      {
         printf("or inside?\n");
         
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

TreeNumber *findFirstNode(TreeNumber *anyNode)
{
   while(anyNode->previousNode != NULL)
      anyNode = anyNode->previousNode;
   
   return anyNode;
}

// change node until find TreeNumber->nextNode = NULL
TreeNumber *findLastNode(TreeNumber *anyNode)
{
   while(anyNode->nextNode != NULL)
      anyNode = anyNode->nextNode;
   
   return anyNode;
}

// make the binary tree from the string imput and returns a pointer
// to the first element of the sorted tree
TreeNumber *makeTree(char *stringTree)
{
   // one pointe for return, one for current node and one for
   // the node being read
   TreeNumber *firstNode, *actualNode, *readNode;
   
   // to be certain that atoi() will work lets copy the values
   // from the input to a smaller string
   // smallString <= stringTree so the max lenght should be stringTree
   char smallString[strlen(stringTree)];
   
   // the adress of the first node is maintained for performance
   // purposes (to not have to return all nodes at the end)
   firstNode = (TreeNumber *) malloc(sizeof(TreeNumber));
   actualNode = firstNode;
   
   // copy the first member of the tree, if there is only one member
   // putAfterNextToken will return a null pointer
   stringCopyUntil(smallString, stringTree, ' ');
   stringTree = putAfterNextToken(stringTree, ' ');
   
   // set up the first node
   actualNode->dataValue = atoi(smallString);
   actualNode->previousNode = NULL;
   
   // if there are more than one items make the list the while
   // executes until there are no more items
   while(stringTree != NULL)
   {
      // allocate memory for next item
      readNode = (TreeNumber *) malloc(sizeof(TreeNumber));
      
      // copy for atoi() because it not register preceding spaces
      stringCopyUntil(smallString, stringTree, ' ');
      stringTree = putAfterNextToken(stringTree, ' ');;
      
      // set up next node
      readNode->dataValue = atoi(smallString);
      
      // set the relationship between nodes
      actualNode->nextNode = readNode;
      readNode->previousNode = actualNode;
      
      // now the actual node is the next node
      actualNode = readNode;
   }
   
   // after the while we are at the last node, lets mark it the last
   actualNode->nextNode = NULL;
   
   return firstNode;
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

// return a pointer to the next part of text after a specified token
// if there are no more tokens return a null pointer
char *putAfterNextToken(char *stringToMove, char token)
{
   while(*stringToMove != token && *stringToMove != '\0')
      stringToMove++;
   
   // token found
   if(*stringToMove == token)
      return ++stringToMove; // return next position;
   
   // token not found
   return NULL;
}

void sortNodes(TreeNumber *firstNode, TreeNumber *lastNode)
{
   TreeNumber *actualNode, *pivotNode;
   printf("the sortNodes at least works\n");
   if(firstNode == lastNode){printf("uses our if *************************\n");
      return;}
   
   pivotNode = lastNode;
   actualNode = firstNode;
   
   while(actualNode != pivotNode)
   {
      printf("enters the while of sortNodes?\n");
      if(actualNode->dataValue > pivotNode->dataValue)
      {
         printf("Value of actualNode %d\n", actualNode->dataValue);
         printf("Value of pivotNode %d\n", pivotNode->dataValue);
         //printf("pivotNode->previousNode->dataValue: %d\n", pivotNode->previousNode->dataValue);
         printf("adress of actualNode: %d\n", actualNode);
         printf("adress of pivotNode->previousNode: %d\n", pivotNode);
         
         actualNode = changeNodes(actualNode, pivotNode->previousNode); // pivotNode is still
         changeNodes(pivotNode->previousNode, pivotNode);
      }
      else{ printf("******************* woks *************\n");
         actualNode = actualNode->nextNode;}
   }
   
   printf("exits the while?\n");
   
   if(findFirstNode(pivotNode) != pivotNode)
      sortNodes(findFirstNode(pivotNode), pivotNode->previousNode);
   
   if(pivotNode != findLastNode(pivotNode))
      sortNodes(pivotNode->nextNode, findLastNode(pivotNode));
   
   return;
}

// copy string until specific token or until the end of the string
void stringCopyUntil(char *firstString, char *secondString, char token)
{
   while(*secondString != token && *secondString != '\0')
      *(firstString++) = *(secondString++);
   
   *firstString = '\0'; // in any case end string
}
