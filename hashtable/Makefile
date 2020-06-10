# Makefile for 'hashtable' module
#
# David Kotz, April 2016, 2017
# updated by Xia Zhou, July 2016, 2018, January 2019
# updated by Temi Prioleau, January 2020

PROG = hashtabletest
OBJS = hashtabletest.o hashtable.o jhash.o ../common/readlinep.o ../common/memory.o ../set/set.o
LIBS =

# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../common -I../set
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

bagtest.o: hashtable.h ../common/readlinep.h
bag.o: hashtable.h ../set/set.h jhash.h
readline.o: ../common/readlinep.h

.PHONY: test clean

test: $(PROG) test_pairs
	./$(PROG) < test_pairs
clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
	rm -f stocks

