
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Paths
SRC = src/main.c
BIN = solve
DEFAULT_MAZE = data/maze.txt

all: $(BIN)

# Compilation
$(BIN): $(SRC)
	$(CC) $(CFLAGS) $< -o $@

# Clean
clean:
	rm -f $(BIN)

# Rebuild
rebuild: clean all

# Run with default maze
run: $(BIN)
	./$(BIN) $(DEFAULT_MAZE)

# Help menu
help:
	@echo "Available commands:"
	@echo "  make        → compile the solver"
	@echo "  make run    → compile and run with $(DEFAULT_MAZE)"
	@echo "  make clean  → remove binary"
	@echo "  make rebuild→ clean + recompile"
	@echo "  make help   → show this help"

.PHONY: all clean rebuild run help
