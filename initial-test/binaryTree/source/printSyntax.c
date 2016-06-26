#include "../include/binaryTree.h"

// print the help on how to use the program
void printSyntax(void)
{
   fputs("\n\nbTree\n\n\
A binary tree builder porgram\n\
usage:\n\n\
bTree <\"string containing values\"> <First Value> <Second Value>\n\n\
bTree build the binary tree and make a binary search for both values\n\
and return the lowest common node between them.\n\n\
exmaple:\n\
tree \"23 12 45 123 56 8 19 14 96 3\" 96 45\n\n", stdout);
}
