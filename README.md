#  Snake Game

**Authors:**  
Ved Bhoraniya, Sukun Dalal, Tanishk Dhawan, Uma Sainitin Burra

---

##  Table of Contents

- [About the Game](#about-the-game)
- [Controls](#controls)
- [Code Structure](#code-structure)
- [Grid Size](#grid-size)
- [Major Highlights](#major-highlights)
- [How to Compile & Run](#how-to-compile--run)
- [How to Play](#how-to-play)
- [Snippet](#snippet)

---

## About the Game

This is a **classic Snake game** implemented in **C++** using the Windows console. The game features:

- **Smooth controls**
- **Dynamic speed adjustments**
- **High-score system**
- **Colorful food**

The objective is simple: **eat food, grow longer, and avoid hitting the walls or yourself**.

---

##  Controls

Use the following keys to navigate the snake:

- **W / Up Arrow** → Move Up
- **S / Down Arrow** → Move Down
- **A / Left Arrow** → Move Left
- **D / Right Arrow** → Move Right
- **Q** → Quit the Game

After Game Over:
- **R** → Restart the Game

---

## Code Structure

The game is structured into various functions for better modularity:

- **`SnakeGame` Class** → Manages game logic and state
- **`initializeConsole()`** → Sets up the console for smooth rendering
- **`moveSnake()`** → Moves the snake and checks for collisions
- **`generateFood()`** → Spawns food in a random location
- **`displayBoard()`** → Renders the game frame-by-frame
- **`play()`** → Runs the main game loop
- **`reset()`** → Resets the game after Game Over

---

##  Grid Size

- The game is played on a **25x25 grid**
- The grid is enclosed with **borders (`#`)**
- The snake (`@`, `O`) moves inside the grid, eating food (`*`)

---

##  Major Highlights

- **Smooth Keyboard Input** → Supports both **WASD and Arrow keys**
- **Dynamic Speed System** → Game speeds up as you score more points
- **High Score System** → Saves and loads the **best score** from a file
- **Colorful Food** → Food appears in random colors for a vibrant look
- **Collision Detection** → Prevents movement into walls and itself
- **Restart Option** → Easily restart after Game Over

---

##  How to Compile & Run

### **Using g++ (MinGW) on Windows**

1. **Install MinGW**: Download and install [MinGW](http://www.mingw.org/) and add it to your system’s PATH.
2. **Open Command Prompt**: Navigate to the folder containing `snake_game.cpp`.
3. **Compile the Program**:
   ```bash
   g++ main.cpp -o snake_game.exe -std=c++11
   
4.**Run the Game**:
   ```bash
   snake_game.exe
```



## Snippet








    




1
