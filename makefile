# Detect OS
ifeq ($(OS),Windows_NT)
    OS_NAME := Windows
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        OS_NAME := Linux
    else ifeq ($(UNAME_S),Darwin)
        OS_NAME := Mac
    endif
endif

# Compiler and Flags
CC := gcc
CFLAGS := -Wall -Wextra -O2 -std=c99  # C99 Standard

# OS-Specific Flags
ifeq ($(OS_NAME), Linux)
    CFLAGS += -DLINUX
else ifeq ($(OS_NAME), Mac)
    CFLAGS += -DMAC
else ifeq ($(OS_NAME), Windows)
    CFLAGS += -DWINDOWS
endif

# Source Files and Executable
SRC := 2024_bigint.c arrayfun.c bigintfun.c operation.c operation_tool.c test.c verify.c rsa.c
TARGET := 2024_bigint
CFLAGS += -DPROCESS_NAME=\"2024_bigint\"

# Build Rules
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
