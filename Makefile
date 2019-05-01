CFLAGS = -Wall -O3
LDFLAGS = -lm
EXECUTABLE = project

SRC = src

SOURCES=$(SRC)/numbers.c \
	$(SRC)/stack.c \
	$(SRC)/input.c \
	$(SRC)/print.c \
	$(SRC)/evaluate.c \
	$(SRC)/basic_operations.c

MAIN = $(SRC)/main.c 

MAIN_O = $(MAIN:.c=.o)
OBJECTS = $(SOURCES:.c=.o)

FINAL_OBJECTS = $(MAIN_O) $(OBJECTS)

EXECUTABLE: $(FINAL_OBJECTS)
	gcc $(CFLAGS) $(FINAL_OBJECTS) -o $(EXECUTABLE) $(LDFLAGS) 

$(OBJECTS) : %.o : %.c %.h
	gcc -c $< -o $@

$(MAIN_O) : %.o : %.c
	gcc -c $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)
