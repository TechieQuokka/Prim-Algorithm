# Makefile for Prim's Algorithm Implementation

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
DEBUG_FLAGS = -g -DDEBUG
INCLUDE_DIR = include
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# Source files
SOURCES = $(SRC_DIR)/utils.c $(SRC_DIR)/graph.c $(SRC_DIR)/priority_queue.c $(SRC_DIR)/prim.c
MAIN_SOURCE = $(SRC_DIR)/main.c
TEST_SOURCE = $(TEST_DIR)/test_cases.c

# Object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
MAIN_OBJECT = $(BUILD_DIR)/main.o
TEST_OBJECT = $(BUILD_DIR)/test_cases.o

# Target executables
TARGET = prim_algorithm
TEST_TARGET = test_prim
DEBUG_TARGET = prim_debug

# Default target
all: $(TARGET)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR)/test_cases.o: $(TEST_SOURCE) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Main executable
$(TARGET): $(OBJECTS) $(MAIN_OBJECT)
	$(CC) $(CFLAGS) $^ -o $@

# Debug executable
debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): CFLAGS += $(DEBUG_FLAGS)
$(DEBUG_TARGET): $(OBJECTS) $(MAIN_OBJECT)
	$(CC) $(CFLAGS) $^ -o $@

# Test executable
test: $(TEST_TARGET)

$(TEST_TARGET): $(OBJECTS) $(TEST_OBJECT)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $^ -o $@

# Run tests
run-test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Run main program
run: $(TARGET)
	./$(TARGET)

# Run debug version
run-debug: $(DEBUG_TARGET)
	./$(DEBUG_TARGET)

# Clean build files
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET) $(TEST_TARGET) $(DEBUG_TARGET)

# Install (copy to system bin - optional)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Uninstall
uninstall:
	rm -f /usr/local/bin/$(TARGET)

# Show help
help:
	@echo "Available targets:"
	@echo "  all        - Build main executable (default)"
	@echo "  debug      - Build debug version with debug symbols"
	@echo "  test       - Build test executable"
	@echo "  run        - Build and run main program"
	@echo "  run-test   - Build and run tests"
	@echo "  run-debug  - Build and run debug version"
	@echo "  clean      - Remove all build files"
	@echo "  install    - Install to /usr/local/bin"
	@echo "  uninstall  - Remove from /usr/local/bin"
	@echo "  help       - Show this help message"

# Check for memory leaks (requires valgrind)
memcheck: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# Static analysis (requires cppcheck)
static-analysis:
	cppcheck --enable=all --std=c99 -I$(INCLUDE_DIR) $(SRC_DIR)/ $(TEST_DIR)/

# Format code (requires clang-format)
format:
	clang-format -i -style=Linux $(SRC_DIR)/*.c $(INCLUDE_DIR)/*.h $(TEST_DIR)/*.c

# Create documentation (requires doxygen)
docs:
	doxygen Doxyfile

# Package for distribution
dist: clean
	tar -czf prim-algorithm.tar.gz --exclude='.git' --exclude='*.tar.gz' .

.PHONY: all debug test run run-test run-debug clean install uninstall help memcheck static-analysis format docs dist