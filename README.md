# Snake Game in C++

## Authors
- Ved
- Tanishk
- Sukun
- Nitin

---

## Description
This is a classic Snake Game implemented in C++ without using any external libraries. The game runs in the console and provides a fun, interactive way to play the traditional snake game.

The game includes the following features:
- A 10x10 grid where the snake moves and grows.
- Food spawns randomly on the grid, and the snake grows when it eats the food.
- The game ends if the snake collides with itself or the boundary of the grid.
- A score counter and a high score tracker that saves your best score to a file (`highscore.txt`).
- Option to restart the game after a game-over.

---

## Requirements
- **Operating System**: Windows (for `_kbhit()` and `_getch()` functions).
- **Compiler**: A C++ compiler that supports C++11 or later.
  - Examples: MinGW (for Windows), GCC (for Linux), or MSVC (Visual Studio).
- **IDE (Optional)**: Visual Studio Code, Dev-C++, Code::Blocks, or any other IDE that supports C++ development.

---

## How to Run the Game
1. Clone the repository or copy the source code into a `.cpp` file.
2. Compile the program using a C++ compiler:
   ```bash
   g++ -o SnakeGame SnakeGame.cpp
