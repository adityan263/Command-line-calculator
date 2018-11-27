FLAGS = -Wall -O3 

SRC = src

SOURCES=$(SRC)/numbers.c \
	$(SRC)/stack.c \
	$(SRC)/input.c \
	$(SRC)/print.c \
	$(SRC)/evaluate.c \
	$(SRC)/basic_operations.c \
	$(SRC)/main.c 

OBJECTS = $(SOURCES:.c=.o)

project: $(OBJECTS)
	gcc $(OBJECTS) -o project -lm

$(OBJECT) : %.o : %.c Makefile
	gcc -c $< -o $@

clean:
	rm $(SRC)/*.o
