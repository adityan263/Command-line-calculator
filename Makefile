calc: calculator.o stack.o
	cc *.o -o calc -lm
stack.o: stack.c stack.h
	cc -c stack.c stack.h -Wall
calculator.o: calculator.c
	cc -c calculator.c -Wall
