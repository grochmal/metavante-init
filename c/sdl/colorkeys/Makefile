# Makefile

TARGET = colorkeys
OBJS = colorkeys.o
INCLUDES = `sdl-config --cflags`
LIBS = `sdl-config --libs`


CC = gcc
CFLAGS = -fPIC -O2 -W -Wall -pedantic
LDFLAGS =
SHLIBFLAGS = -shared -Wl, -soname,


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

