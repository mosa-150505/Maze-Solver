# 🌀 Maze Solver — Depth-First Search in Pure C99

> A minimal, memory-safe maze solver using recursive DFS with backtracking.

## ▶️ Build & Run

```bash
#Optional for the banner
sudo apt install figlet
sudo dnf install figlet

#Compile
make

#Compile and run with default maze
make run

#Clean && rebuild
make rebuild

#Solve
./solve data/maze.txt
```

## 🧩 Maze Format

| Symbol | Meaning  |
|--------|----------|
| `s`    | Start    |
| `g`    | Goal     |
| `+`    | Wall     |
| ` `    | Path     |

> *“Sometimes, the only way out is to go back”*
