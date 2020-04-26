#P=main
OBJECTS=cheatsheets.o configparse.o
CFLAGS=-g -Wall -O0 --std=gnu11
LDLIBS=
LDFLAGS=
CC=gcc

$(P): $(OBJECTS)

clean: 
	rm *.o

install:
	install-sh --name cs main

