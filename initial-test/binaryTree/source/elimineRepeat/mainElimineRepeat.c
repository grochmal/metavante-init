#include "../../include/binaryTree.h"
#include "../../include/elimineRepeat.h"

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
   
   // this time we need to find the firstNode earlier because we can 
   // drop the node pointed by treeList in the next function
   firstNode = findFirstNode(treeList);
   
   // the pointer to firstNode is secure because even if all the values
   // are the same the firstNode is maintained in memory
   elimineRepeatedNodes(firstNode);
   
   // build the binary tree from the linked list
   buildTree(firstNode, lastNode = findLastNode(firstNode), MIDDLE);
   
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
   
   return 0;
}
