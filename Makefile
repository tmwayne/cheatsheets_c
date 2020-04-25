#P=main
OBJECTS=
CFLAGS=-g -Wall -O0 --std=gnu11
LDLIBS=
LDFLAGS=
CC=gcc

$(P): $(OBJECTS)

clean: 
	rm *.o

run: $(P)
	./$(P) $(PARGS)

