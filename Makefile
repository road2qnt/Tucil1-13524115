
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Isrc/include
SRC_DIR := src
BIN_DIR := bin
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)
TARGET  := $(BIN_DIR)/solver

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "[LINKING] Membuat executable..."
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@
	@echo "Build Success! Run with: ./$(TARGET)" || echo "Build Success! Run with: bin\solver.exe"

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	@echo "[COMPILING] $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "[CLEANING] Hapus build files..."
	rm -rf $(BIN_DIR)
run: all
	./$(TARGET) || bin\solver.exe

.PHONY: all clean run