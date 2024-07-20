# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Werror -fPIC -I$(INC_DIR)

# Target library name
TARGET_LIB = liblinuxsystemmonitor.so
# Target executable name
TARGET_EXE = linuxSystemLogger

# Directories
SRC_DIR = src
LIB_DIR = lib
BIN_DIR = bin
INC_DIR = include

# Phony targets
.PHONY: all clean

# Default target
all: $(LIB_DIR)/$(TARGET_LIB) $(BIN_DIR)/$(TARGET_EXE)

# Build library
$(LIB_DIR)/$(TARGET_LIB): $(SRC_DIR)/linuxSystemMonitor.cpp $(INC_DIR)/linuxSystemMonitor.hpp $(LIB_DIR)
	$(CC) $(CFLAGS) -shared -o $(LIB_DIR)/$(TARGET_LIB) $(SRC_DIR)/linuxSystemMonitor.cpp

# Build executable
$(BIN_DIR)/$(TARGET_EXE): $(SRC_DIR)/linuxSystemLogger.cpp $(INC_DIR)/linuxSystemMonitor.hpp $(LIB_DIR)/$(TARGET_LIB) $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(TARGET_EXE) $(SRC_DIR)/linuxSystemLogger.cpp -L$(LIB_DIR) -llinuxsystemmonitor

# Create library directory
$(LIB_DIR):
	mkdir -p $(LIB_DIR)

# Create binary directory
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean
clean:
	rm -rf $(LIB_DIR) $(BIN_DIR)
