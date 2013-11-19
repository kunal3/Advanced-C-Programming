# filename: Makefile
GCC = gcc
CFLAGS = -g -Wall -Wshadow
OBJS = answer10.o pa10.o
HDRS = pa10.h
TARGET = pa10
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

.PHONY: test clean environment test1 # uhhhhh

pa10: $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -f pa10 $(OBJS) outputs/*

test: | test1 # uhhhh


test1:  pa10
