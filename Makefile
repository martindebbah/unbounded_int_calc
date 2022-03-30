CC = gcc
CFLAGS = -Wall -g -pedantic -target x86_64-apple-darwin
LDFLAGS =
EXEC = main

all : $(EXEC)

main : test_unbounded.o unbounded_int.o
	$(CC) -o $@ $^ $(LDFLAGS)

test_unbounded.o : test_unbounded.c unbounded_int.h
	$(CC) $(CFLAGS) $< -o $@

unbounded_int.o : unbounded_int.c unbounded_int.h
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -rf main *.o