#include "../../include/binaryTree.h"
#include "../../include/binaryTreeDebug.h"

// test the input and divides actions on the program
int main(int argc, char **argv)
{
   // our linked list
   TreeNumber *treeList, *nodeToFindA, *nodeToFindB, 
      *firstNode, *lastNode;
   
   // if the input isn't the desired inform the user about the syntax
   // woks even with tree -?, tree -h and tree --help :)
   if(argc != 4)
   {
      printSyntax();
      return 0;
   }
   
   // we need only the first member of a linked list
   treeList = makeTree(argv[1]);
   
   // a binary search couldn't be done without an orginized list
   sortNodes(treeList, findLastNode(treeList));
   
   // build the binary tree from the linked list
   buildTree(firstNode = findFirstNode(treeList),
      lastNode = findLastNode(treeList), MIDDLE);
   
   // search the binary tree for the node of argument 2
   if((nodeToFindA = findNodeWithValue(firstNode, lastNode,
      atoi(argv[2]))) == NULL)
   {
      printTheresNoNode(atoi(argv[2])); // there's no such node
      return 0;
   }
   
   // search the binary tree for the node of argument 3
   if((nodeToFindB = findNodeWithValue(firstNode, lastNode,
      atoi(argv[3]))) == NULL)
   {
      printTheresNoNode(atoi(argv[3])); // there's no such node
      return 0;
   }
   
   // print the common node value
   printf("%d\n",
      (findCommonNode(nodeToFindA, nodeToFindB))->dataValue);
   
   // after doing all print the state of variables
   printNodes(firstNode);
   printTree(firstNode, NULL);
   
   return 0;
}
