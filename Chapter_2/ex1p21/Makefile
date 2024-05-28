# Compiler
CC = cc

# Directories
OBJ_DIR = build
BIN_DIR = bin

# Object files
OBJECTS = $(OBJ_DIR)/main.o $(OBJ_DIR)/elem_sorts.o

# Executable
TARGET = transaction_sorter

# Link obj files into an executable
$(BIN_DIR)/$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(OBJECTS) -o $@

# Pattern rules to compile .c files to .o files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) -c $< -o $@

# Special Dependencies
$(OBJ_DIR)/main.o: main.c transaction.h ../elem_sorts.h | $(OBJ_DIR)
$(OBJ_DIR)/elem_sorts.o: ../elem_sorts.c ../elem_sorts.h | $(OBJ_DIR)
	$(CC) -c $< -o $@

# Directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(BIN_DIR):
	mkdir -p $(BIN_DIR)


# Cleanup Generated Files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: clean
