CC = gcc
CFLAGS = -Wall -g -pedantic
LDFLAGS =
EXEC = main

all : $(EXEC)

main : test_unbounded.c unbounded_int.c
	$(CC) $(CFLAGS) $^ -o $@

clean :
	rm -rf $(EXEC) *.o