CC = gcc
CFLAGS = -Wall -g -pedantic
LDFLAGS =
EXEC = test calc_unbounded_int

all : $(EXEC)

test : test_unbounded.c unbounded_int.c
	$(CC) $(CFLAGS) $^ -o $@

calc_unbounded_int : calc_unbounded_int.c unbounded_int.c
	$(CC) $(CFLAGS) $^ -o $@

clean :
	rm -rf $(EXEC) *.o