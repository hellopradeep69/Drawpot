CC= gcc
SOURCE= src/main.c
TARGET= target/main

run: compile
	./$(TARGET)


compile:
	$(CC) $(SOURCE) -o $(TARGET)
