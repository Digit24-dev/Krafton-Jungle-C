# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -g  # Wall for all warnings, g for debug information

# Define the C source files
SOURCES = $(wildcard Q*_C_SQ.c)
# Define the executable files
EXECUTABLES = $(SOURCES:.c=.exe)

# Default target
all: $(EXECUTABLES)

# Rule to create an executable from a .c file
%.exe: %.c
	$(CC) $(CFLAGS) $< -o $@

# Clean target
clean:
	rm -f $(EXECUTABLES)

# Phony targets
.PHONY: all clean
