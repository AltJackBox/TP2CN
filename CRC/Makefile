CC = gcc
CFLAGS = -Wall -Werror
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
RM = rm -f

all: clean test_code

test_code: main.o code.o
	$(CC) -o test_code main.o code.o

main.o: main.c code.h
	$(CC) $(CFLAGS) -c -g main.c

code.o: code.c code.h
	$(CC) $(CFLAGS) -c -g code.c

.PHONY: clean

clean:
	$(RM) $(OBJECTS) test_code
