CC = gcc
FLAGS = -std=c17 -Wall -Wextra -pedantic -fsanitize=address,undefined
LFLAGS = 
SRC = listen.c
BIN = OUTFILE

all: $(BIN)

$(BIN):
	$(CC) $(SRC) -o $@ $(FLAGS) $(LFLAGS)
	rm -f $(BIN)

run:
	$(CC) $(SRC) -o $(BIN) $(FLAGS) $(LFLAGS)
	./$(BIN)
	rm -f $(BIN)