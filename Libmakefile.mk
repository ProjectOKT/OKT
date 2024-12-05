# Compiler and flags
CC = gcc
CFLAGS = -Wall -fPIC -O2 -std=c99

# Target directories
TARGET_DIR = MacOs
LIB_DIR = $(TARGET_DIR)
APP_DIR = $(TARGET_DIR)

# Source files
MAIN_SRC = arrayfun.c bigintfun.c operation_tool.c operation.c
TOOL_SRC = arrayfun.c bigintfun.c operation.c operation_tool.c 
APP_SRC = arrayfun.c bigintfun.c operation_tool.c operation.c test.c verify.c 2024_bigint.c

# Object files
MAIN_OBJ = $(MAIN_SRC:.c=.o)
TOOL_OBJ = $(TOOL_SRC:.c=.o)
APP_OBJ = $(APP_SRC:.c=.o)

# Shared library names
LIB_MAIN = liboperation.so
LIB_TOOL = liboperation_tool.so

# Executable name
APP_EXEC = bigint_app

# Phony targets
.PHONY: all clean directories

# Default target
all: directories $(LIB_DIR)/$(LIB_MAIN) $(LIB_DIR)/$(LIB_TOOL) $(APP_DIR)/$(APP_EXEC)

# Create target directories if not exist
directories:
	mkdir -p $(TARGET_DIR)

# Build shared library for operation.c
$(LIB_DIR)/$(LIB_MAIN): $(MAIN_SRC)
	$(CC) $(CFLAGS) -shared -o $@ $^

# Build shared library for operation_tool.c
$(LIB_DIR)/$(LIB_TOOL): $(TOOL_SRC)
	$(CC) $(CFLAGS) -shared -o $@ $^

# Build application
$(APP_DIR)/$(APP_EXEC): $(APP_SRC)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIB_DIR) -loperation -loperation_tool -Wl,-rpath,@executable_path

# Clean build artifacts
clean:
	rm -f *.o
	rm -f $(LIB_DIR)/$(LIB_MAIN) $(LIB_DIR)/$(LIB_TOOL) $(APP_DIR)/$(APP_EXEC)
	rmdir $(TARGET_DIR) 2>/dev/null || true