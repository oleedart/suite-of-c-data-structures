# Makefile for 'counter' module
#
# Oscar Lee, 4/21/2020

PROG = countertest
OBJS = countertest.o counters.o ../common/readlinep.o ../common/memory.o
LIBS =

# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../common
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

bagtest.o: counters.h ../common/readlinep.h
bag.o: counters.h
readline.o: ../common/readlinep.h

.PHONY: test clean

test: $(PROG) test_keys
	./$(PROG) < test_keys

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
	rm -f stocks

