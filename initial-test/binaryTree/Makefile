# variables
C_COMPILER = gcc
C_FLAGS = -Wall
LINKER = gcc
L_FLAGS =

# default program
all: bTree clean

# for debuging info at the end
withDebug: bTreeDebug clean

# version that ignore repeted values
elimineRepeat: bTreeElimineRepeat clean

# debug info for ignore repeat version
elimineRepeat-withDebug: bTreeElimineRepeatDebug clean

# overriden rule for inverse input
withDebug-elimineRepeat: elimineRepeat-withDebug


# default functions
bTree: main.o buildTree.o changeAdjacentNodes.o changeNodes.o findCommonNode.o findFirstNode.o findLastNode.o findMiddleNode.o findNodeWithValue.o makeTree.o printSyntax.o printTheresNoNode.o putAfterNextTokens.o sortNodes.o stringCopyUntil.o
	$(LINKER) $(L_FLAGS) -o bTree main.o buildTree.o changeAdjacentNodes.o changeNodes.o findCommonNode.o findFirstNode.o findLastNode.o findMiddleNode.o findNodeWithValue.o makeTree.o printSyntax.o printTheresNoNode.o putAfterNextTokens.o sortNodes.o stringCopyUntil.o

main.o: source/main.c include/binaryTree.h buildTree.o findCommonNode.o findFirstNode.o findLastNode.o findNodeWithValue.o makeTree.o printSyntax.o printTheresNoNode.o sortNodes.o
	$(C_COMPILER) $(C_FLAGS) -c source/main.c -I ../include/binaryTree.h

buildTree.o: source/buildTree.c include/binaryTree.h findMiddleNode.o
	$(C_COMPILER) $(C_FLAGS) -c source/buildTree.c -I ../include/binaryTree.h

changeAdjacentNodes.o: source/changeAdjacentNodes.c include/binaryTree.h
	$(C_COMPILER) $(C_FLAGS) -c source/changeAdjacentNodes.c -I ../include/binaryTree.h

changeNodes.o: source/changeNodes.c include/binaryTree.h changeAdjacentNodes.o
	$(C_COMPILER) $(C_FLAGS) -c source/changeNodes.c -I ../include/binaryTree.h

findCommonNode.o: source/findCommonNode.c include/binaryTree.h
	$(C_COMPILER) $(C_FLAGS) -c source/findCommonNode.c -I ../include/binaryTree.h

findFirstNode.o: source/findFirstNode.c include/binaryTree.h
	$(C_COMPILER) $(C_FLAGS) -c source/findFirstNode.c -I ../include/binaryTree.h

findLastNode.o: source/findLastNode.c include/binaryTree.h
	$(C_COMPILER) $(C_FLAGS) -c source/findLastNode.c -I ../include/binaryTree.h

findMiddleNode.o: source/findMiddleNode.c include/binaryTree.h
	$(C_COMPILER) $(C_FLAGS) -c source/findMiddleNode.c -I ../include/binaryTree.h

findNodeWithValue.o: source/findNodeWithValue.c include/binaryTree.h findMiddleNode.o
	$(C_COMPILER) $(C_FLAGS) -c source/findNodeWithValue.c -I ../include/binaryTree.h

makeTree.o: source/makeTree.c include/binaryTree.h putAfterNextTokens.o stringCopyUntil.o
	$(C_COMPILER) $(C_FLAGS) -c source/makeTree.c -I ../include/binaryTree.h

printSyntax.o: source/printSyntax.c include/binaryTree.h
	$(C_COMPILER) $(C_FLAGS) -c source/printSyntax.c -I ../include/binaryTree.h

printTheresNoNode.o: source/printTheresNoNode.c include/binaryTree.h
	$(C_COMPILER) $(C_FLAGS) -c source/printTheresNoNode.c -I ../include/binaryTree.h

putAfterNextTokens.o: source/putAfterNextTokens.c include/binaryTree.h
	$(C_COMPILER) $(C_FLAGS) -c source/putAfterNextTokens.c -I ../include/binaryTree.h

sortNodes.o: source/sortNodes.c include/binaryTree.h changeNodes.o findFirstNode.o findLastNode.o
	$(C_COMPILER) $(C_FLAGS) -c source/sortNodes.c -I ../include/binaryTree.h

stringCopyUntil.o: source/stringCopyUntil.c include/binaryTree.h
	$(C_COMPILER) $(C_FLAGS) -c source/stringCopyUntil.c -I ../include/binaryTree.h


# elimineRepeat version functions
bTreeElimineRepeat: mainElimineRepeat.o buildTree.o changeAdjacentNodes.o changeNodes.o dropNode.o elimineRepeatedNodes.o findCommonNode.o findFirstNode.o findLastNode.o findMiddleNode.o findNodeWithValue.o makeTree.o printSyntax.o printTheresNoNode.o putAfterNextTokens.o sortNodes.o stringCopyUntil.o
	$(LINKER) $(L_FLAGS) -o bTreeElimineRepeat mainElimineRepeat.o buildTree.o changeAdjacentNodes.o changeNodes.o dropNode.o elimineRepeatedNodes.o findCommonNode.o findFirstNode.o findLastNode.o findMiddleNode.o findNodeWithValue.o makeTree.o printSyntax.o printTheresNoNode.o putAfterNextTokens.o sortNodes.o stringCopyUntil.o

mainElimineRepeat.o: source/elimineRepeat/mainElimineRepeat.c include/binaryTree.h include/elimineRepeat.h buildTree.o elimineRepeatedNodes.o findCommonNode.o findFirstNode.o findLastNode.o findNodeWithValue.o makeTree.o printSyntax.o printTheresNoNode.o sortNodes.o
	$(C_COMPILER) $(C_FLAGS) -c source/elimineRepeat/mainElimineRepeat.c -I ../../include/

dropNode.o: source/elimineRepeat/dropNode.c include/binaryTree.h include/elimineRepeat.h
	$(C_COMPILER) $(C_FLAGS) -c source/elimineRepeat/dropNode.c -I ../../include/

elimineRepeatedNodes.o: source/elimineRepeat/elimineRepeatedNodes.c include/binaryTree.h include/elimineRepeat.h dropNode.o
	$(C_COMPILER) $(C_FLAGS) -c source/elimineRepeat/elimineRepeatedNodes.c -I ../../include/


# debug version functions
bTreeDebug: mainDebug.o buildTree.o changeAdjacentNodes.o changeNodes.o findCommonNode.o findFirstNode.o findLastNode.o findLeafPointingTo.o findMiddleNode.o findNodeWithValue.o makeTree.o printNodes.o printSyntax.o printTheresNoNode.o printTree.o putAfterNextTokens.o sortNodes.o stringCopyUntil.o
	$(LINKER) $(L_FLAGS) -o bTreeDebug mainDebug.o buildTree.o changeAdjacentNodes.o changeNodes.o findCommonNode.o findFirstNode.o findLastNode.o findLeafPointingTo.o findMiddleNode.o findNodeWithValue.o makeTree.o printNodes.o printSyntax.o printTheresNoNode.o printTree.o putAfterNextTokens.o sortNodes.o stringCopyUntil.o

mainDebug.o: source/debug/mainDebug.c include/binaryTree.h include/binaryTreeDebug.h buildTree.o findCommonNode.o findFirstNode.o findLastNode.o findNodeWithValue.o makeTree.o printNodes.o printSyntax.o printTheresNoNode.o printTree.o sortNodes.o
	$(C_COMPILER) $(C_FLAGS) -c source/debug/mainDebug.c -I ../../include/

findLeafPointingTo.o: source/debug/findLeafPointingTo.c include/binaryTree.h include/binaryTreeDebug.h
	$(C_COMPILER) $(C_FLAGS) -c source/debug/findLeafPointingTo.c -I ../../include/

printNodes.o: source/debug/printNodes.c include/binaryTree.h include/binaryTreeDebug.h
	$(C_COMPILER) $(C_FLAGS) -c source/debug/printNodes.c -I ../../include/

printTree.o: source/debug/printTree.c include/binaryTree.h include/binaryTreeDebug.h findFirstNode.o findLeafPointingTo.o
	$(C_COMPILER) $(C_FLAGS) -c source/debug/printTree.c -I ../../include/


# elimineRepeat version with debug info
bTreeElimineRepeatDebug: mainElimineRepeatDebug.o buildTree.o changeAdjacentNodes.o changeNodes.o dropNode.o elimineRepeatedNodes.o findCommonNode.o findFirstNode.o findLastNode.o findLeafPointingTo.o findMiddleNode.o findNodeWithValue.o makeTree.o printNodes.o printSyntax.o printTheresNoNode.o printTree.o putAfterNextTokens.o sortNodes.o stringCopyUntil.o
	$(LINKER) $(L_FLAGS) -o bTreeElimineRepeatDebug mainElimineRepeatDebug.o buildTree.o changeAdjacentNodes.o changeNodes.o dropNode.o elimineRepeatedNodes.o findCommonNode.o findFirstNode.o findLastNode.o findLeafPointingTo.o findMiddleNode.o findNodeWithValue.o makeTree.o printNodes.o printSyntax.o printTheresNoNode.o printTree.o putAfterNextTokens.o sortNodes.o stringCopyUntil.o

mainElimineRepeatDebug.o: source/elimineRepeatDebug/mainElimineRepeatDebug.c include/binaryTree.h include/binaryTreeDebug.h include/elimineRepeat.h buildTree.o elimineRepeatedNodes.o findCommonNode.o findFirstNode.o findLastNode.o findNodeWithValue.o makeTree.o printNodes.o printSyntax.o printTheresNoNode.o printTree.o sortNodes.o
	$(C_COMPILER) $(C_FLAGS) -c source/elimineRepeatDebug/mainElimineRepeatDebug.c -I ../../include/


# clean rule, used for all versions
clean:
	rm -f *.o
