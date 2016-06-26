/***********************************************************************
* bTree a program that designs a binary tree form the user's input and *
* find common nodes for values (from nodes of the tree).               *
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

// this statement is normally present in the stdlib.h, but normally
// isn't sufficient so let's be certain
typedef enum
{
   FALSE,
   TRUE
}boolean;

// for greater clarity we use enum fo directions inside the tree
typedef enum
{
   LEFT,
   MIDDLE,
   RIGTH
}directionOf;

// work of functions stated on their proper files
void buildTree(TreeNumber *leftNode, TreeNumber *rigthNode,
   directionOf leafSide);
TreeNumber *changeAdjacentNodes(TreeNumber *leftNode,
   TreeNumber *rigthNode);
TreeNumber *changeNodes(TreeNumber *nodeA, TreeNumber *nodeB);
TreeNumber *findCommonNode(TreeNumber *oneNode, TreeNumber *otherNode);
TreeNumber *findFirstNode(TreeNumber *anyNode);
TreeNumber *findLastNode(TreeNumber *anyNode);
TreeNumber *findMiddleNode(TreeNumber *firstNode, TreeNumber *lastNode);
TreeNumber *findNodeWithValue(TreeNumber *firstNode,
   TreeNumber *lastNode, int valueToFind);
TreeNumber *makeTree(char *stringTree);
void printSyntax(void);
void printTheresNoNode(int valueOfNode);
char *putAfterNextTokens(char *stringToMove, char token);
void sortNodes(TreeNumber *firstNode, TreeNumber *lastNode);
void stringCopyUntil(char *firstString, char *secondString, char token);
