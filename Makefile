CC = gcc
CFLAGS = -Wall -Wextra -O2
SRC = main.c sudoku.c
OBJ = $(SRC:.c=.o)
OUT = sudoku

.PHONY: all dev build clean

all: build

dev:
	@echo "Compiling and running..."
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)
	./$(OUT)

build:
	@echo "Compiling..."
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

clean:
	@echo "Cleaning..."
	rm -f $(OUT) *.o