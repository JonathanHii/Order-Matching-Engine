CXX      := g++
CXXFLAGS := -std=c++17 -O3 -Wall -Wextra -march=native -Iinclude
LDFLAGS  := -lpthread

# Directories
SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  := bin

SRCS     := $(SRC_DIR)/main.cpp \
            $(SRC_DIR)/orderbook.cpp

OBJS     := $(OBJ_DIR)/main.o \
            $(OBJ_DIR)/orderbook.o

TARGET   := $(BIN_DIR)/engine

# Default Target
all: $(TARGET)

# Linking: Combines all object 
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Compilation: source files into object files
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/orderbook.o: $(SRC_DIR)/orderbook.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean command 
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean