# filename: Makefile
GCC = gcc
CFLAGS = -g -Wall -Wshadow
OBJS = answer11.o pa11.o
HDRS = pa11.h
TARGET = pa11
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

.PHONY: test clean environment test1

pa11: $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -f pa11 $(OBJS) outputs/*

test: | test1

test1:  pa11
