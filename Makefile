FLAGS = -Wall -O3 

SRC = .

SOURCES=$(SRC)/numbers.c \
	$(SRC)/stack.c \
	$(SRC)/calculator.c 

OBJECTS = $(SOURCES:.c=.o)

project: $(OBJECTS)
	gcc $(OBJECTS) -o project -lm

$(OBJECT) : %.o : %.c Makefile
	gcc -c $< -o $@

clean:
	rm $(SRC)/*.o
