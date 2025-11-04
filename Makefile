
# Compiler
CC = gcc

# Compiler flags
CFLAGS = -std=c99

# Libraries to link
LIBS = -lncurses

# Source and output files
SRC = main.c
OUT = main

# Default target
all: $(OUT)

# How to build the program
$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -o $(OUT)

# Clean up build files
clean:
	rm -f $(OUT)

# Run the program
run: $(OUT)
	./$(OUT)
