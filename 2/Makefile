CC = gcc
FLAGS = -std=c17 -Wall -Wextra -pedantic -fsanitize=address,undefined
LFLAGS = 
SRC = listen.c
BIN = OUTFILE

all: $(BIN)
	./$(BIN)
	rm -f $(BIN)

$(BIN):
	$(CC) $(SRC) -o $@ $(FLAGS) $(LFLAGS)
