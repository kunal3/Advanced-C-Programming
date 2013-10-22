# filename: Makefile
GCC = gcc
CFLAGS = -g -Wall -Wshadow
OBJS = answer07.o pa07.o
HDRS = pa07.h
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose


pa07: $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

.c.o: 
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -f pa07 $(OBJS) outputs/*

test0:  pa07
	$(VALGRIND) --log-file=outputs/memoutput0 ./pa07 inputs/input0_A inputs/input0_B
	./pa07 inputs/input0_A inputs/input0_B > outputs/output0
	diff -w outputs/output0 expected/expected0

test1:  pa07
	$(VALGRIND) --log-file=outputs/memoutput1 ./pa07 inputs/input1_A inputs/input1_B
	./pa07 inputs/input1_A inputs/input1_B > outputs/output1
	diff -w outputs/output1 expected/expected1

test2:  pa07
	$(VALGRIND) --log-file=outputs/memoutput2 ./pa07 inputs/input2_A inputs/input2_B
	./pa07 inputs/input2_A inputs/input2_B > outputs/output2
	diff -w outputs/output2 expected/expected2

test3:  pa07
	$(VALGRIND) --log-file=outputs/memoutput3 ./pa07 inputs/input3_A inputs/input3_B
	./pa07 inputs/input3_A inputs/input3_B > outputs/output3
	diff -w outputs/output3 expected/expected3

test4:  pa07
	$(VALGRIND) --log-file=outputs/memoutput4 ./pa07 inputs/input4_A inputs/input4_B
	./pa07 inputs/input4_A inputs/input4_B > outputs/output4
	diff -w outputs/output4 expected/expected4

test5:  pa07
	$(VALGRIND) --log-file=outputs/memoutput5 ./pa07 inputs/input5_A inputs/input5_B
	./pa07 inputs/input5_A inputs/input5_B > outputs/output5
	diff -w outputs/output5 expected/expected5

test6:  pa07
	$(VALGRIND) --log-file=outputs/memoutput6 ./pa07 inputs/input6_A inputs/input6_B
	./pa07 inputs/input6_A inputs/input6_B > outputs/output6
	diff -w outputs/output6 expected/expected6

test7:  pa07
	$(VALGRIND) --log-file=outputs/memoutput7 ./pa07 inputs/input7_A inputs/input7_B
	./pa07 inputs/input7_A inputs/input7_B > outputs/output7
	diff -w outputs/output7 expected/expected7

test8:  pa07
	$(VALGRIND) --log-file=outputs/memoutput8 ./pa07 inputs/input8_A inputs/input8_B
	./pa07 inputs/input8_A inputs/input8_B > outputs/output8
	diff -w outputs/output8 expected/expected8

test9:  pa07
	$(VALGRIND) --log-file=outputs/memoutput9 ./pa07 inputs/input9_A inputs/input9_B
	./pa07 inputs/input9_A inputs/input9_B > outputs/output9
	diff -w outputs/output9 expected/expected9

test10:  pa07
	$(VALGRIND) --log-file=outputs/memoutput10 ./pa07 inputs/input10_A inputs/input10_B
	./pa07 inputs/input10_A inputs/input10_B > outputs/output10
	diff -w outputs/output10 expected/expected10
