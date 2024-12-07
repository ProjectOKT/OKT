# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99
DLLEXT = dll

# Target directories
ifeq ($(OS),Windows_NT)
    TARGET_DIR = WinOs
    LIB_EXT = .dll
    APP_EXT = .exe
else
    TARGET_DIR = MacOs
    LIB_EXT = .so
    APP_EXT = 
    CFLAGS += -fPIC
endif

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
LIB_MAIN = liboperation$(LIB_EXT)
LIB_TOOL = liboperation_tool$(LIB_EXT)

# Executable name
APP_EXEC = bigint_app$(APP_EXT)

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

ifdef WINDOWS
    DLL_FLAGS = -Wl,--enable-auto-import
else
    DLL_FLAGS = -Wl,-rpath,@executable_path
endif

# Build application
$(APP_DIR)/$(APP_EXEC): $(APP_SRC)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIB_DIR) -loperation -loperation_tool $(DLL_FLAGS)

# Clean build artifacts
clean:
	rm -f *.o
	rm -f $(LIB_DIR)/$(LIB_MAIN) $(LIB_DIR)/$(LIB_TOOL) $(APP_DIR)/$(APP_EXEC)
	rmdir $(TARGET_DIR) 2>/dev/null || true