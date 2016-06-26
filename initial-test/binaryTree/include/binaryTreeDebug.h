/***********************************************************************
* bTree program debug functions.                                       *
* Include this file in the debuging applications for bTree             *
***********************************************************************/

// extra functions used
TreeNumber *findLeafPointingTo(TreeNumber *positionNode,
   TreeNumber *upperLeaf);
void printNodes(TreeNumber *firstNode);
void printTree(TreeNumber *positionNode, TreeNumber *belowThis);
