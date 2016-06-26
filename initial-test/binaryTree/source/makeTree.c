#include "../include/binaryTree.h"

// make the binary tree from the string input and returns a pointer
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
   
   // eliminate prefix spaces (in case of misstype)
   while(*stringTree == ' ')
      stringTree++;
   
   // copy the first member of the tree, if there is only one member
   // putAfterNextToken will return a null pointer
   stringCopyUntil(smallString, stringTree, ' ');
   stringTree = putAfterNextTokens(stringTree, ' ');
   
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
      stringTree = putAfterNextTokens(stringTree, ' ');;
      
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
