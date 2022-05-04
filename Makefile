CC = gcc
CFLAGS = -Wall -g -pedantic
LDFLAGS =
EXEC = main calc

all : $(EXEC)

main : test_unbounded.c unbounded_int.c
	$(CC) $(CFLAGS) $^ -o $@

calc : calc_unbounded_int.c unbounded_int.c
	$(CC) $(CFLAGS) $^ -o $@

clean :
	rm -rf $(EXEC) *.o