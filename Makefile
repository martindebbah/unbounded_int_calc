CC = gcc
CFLAGS = -Wall -g -pedantic
LDFLAGS =
EXEC = main calc_unbounded_int

all : $(EXEC)

main : test_unbounded.c unbounded_int.c
	$(CC) $(CFLAGS) $^ -o $@

calc_unbounded_int : calc_unbounded_int.c unbounded_int.c
	$(CC) $(CFLAGS) $^ -o $@

clean :
	rm -rf $(EXEC) *.o