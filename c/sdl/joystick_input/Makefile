###############################################################################
# File: Makefile
#
# Author(s): Michal Grochmal
# Copyright (C): This program is free software under GNU GPL.
#
# Purpose: Makefile for keyboard_input.
# Comments:
###############################################################################

###############################################################################
# These are the variables you normally need to play with.
###############################################################################
TARGET = joystick_input
OBJS = joystick_input.o
INCLUDES = `sdl-config --cflags`
LIBS = `sdl-config --libs` -lSDL_image-1.2


###############################################################################
# These are quite untouchable.
###############################################################################
CC = gcc
CFLAGS = -fPIC -O2 -W -Wall -pedantic
LDFLAGS =
SHLIBFLAGS = -shared -Wl, -soname,


###############################################################################
# Rules (this could go to a generic Makefile).
###############################################################################
all: $(TARGET)

# $@ stands for the target to build.
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

# $< stands for the dependencies matched.
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)


.PHONY: clean

clean:
	rm $(OBJS)
	rm $(TARGET)

