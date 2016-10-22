project: calculator.o stack.o
	cc *.o -o project -lm
stack.o: stack.c stack.h
	cc -c stack.c stack.h -Wall
calculator.o: calculator.c
	cc -c calculator.c -Wall
