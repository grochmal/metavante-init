# variables
C_COMPILER = gcc
C_FLAGS = -Wall
LINKER = gcc
L_FLAGS =

# default make
all: memoryUsedByDouble clean

# linker
memoryUsedByDouble: main.o makeBinary.o printExponent.o printInfinity.o printMantissa.o printSignal.o printZero.o
	$(LINKER) $(L_FLAGS) -o memoryUsedByDouble main.o makeBinary.o printExponent.o printInfinity.o printMantissa.o printSignal.o printZero.o

# functions
main.o: source/main.c include/memoryUsedByDouble.h makeBinary.o printInfinity.o printZero.o
	$(C_COMPILER) $(C_FLAGS) -c source/main.c -I ../include/memoryUsedByDouble.h

makeBinary.o: source/makeBinary.c include/memoryUsedByDouble.h printExponent.o printMantissa.o printSignal.o
	$(C_COMPILER) $(C_FLAGS) -c source/makeBinary.c -I ../include/memoryUsedByDouble.h

printExponent.o: source/printExponent.c include/memoryUsedByDouble.h
	$(C_COMPILER) $(C_FLAGS) -c source/printExponent.c -I ../include/memoryUsedByDouble.h

printInfinity.o: source/printInfinity.c include/memoryUsedByDouble.h
	$(C_COMPILER) $(C_FLAGS) -c source/printInfinity.c -I ../include/memoryUsedByDouble.h

printMantissa.o: source/printMantissa.c include/memoryUsedByDouble.h
	$(C_COMPILER) $(C_FLAGS) -c source/printMantissa.c -I ../include/memoryUsedByDouble.h

printSignal.o: source/printSignal.c include/memoryUsedByDouble.h
	$(C_COMPILER) $(C_FLAGS) -c source/printSignal.c -I ../include/memoryUsedByDouble.h

printZero.o: source/printZero.c include/memoryUsedByDouble.h
	$(C_COMPILER) $(C_FLAGS) -c source/printZero.c -I ../include/memoryUsedByDouble.h

# clean rule
clean:
	rm -f *.o
