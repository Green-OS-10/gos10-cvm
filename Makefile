# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -Wno-unused-variable -Wno-unused-parameter -std=c99

# Source files
SRCS = $(wildcard src/*.c)

# Object files
OBJS = $(patsubst src/%.c, bin/%.o, $(SRCS))

# Executable
TARGET = bin/cvm

# Default target
all: $(TARGET)
	clear

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
bin/%.o: src/%.c | bin
	$(CC) $(CFLAGS) -c $< -o $@

# Create bin directory if it does not exist
bin:
	mkdir -p bin

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean bin