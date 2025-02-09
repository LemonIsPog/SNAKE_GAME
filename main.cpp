#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <conio.h> // For capturing keyboard input
#include <fstream> // For saving high scores

using namespace std;

class SnakeGame {
private:
    int gridSize;                          // Size of the grid (NxN)
    queue<pair<int, int>> snake;           // Snake represented as a queue
    pair<int, int> food;                   // Current food position
    char direction;                        // Current direction of the snake
    bool gameOver;                         // Game state
    int score;                             // Current score
    int highScore;                         // Highest score saved

    void loadHighScore() {
        ifstream file("highscore.txt");
        if (file.is_open()) {
            file >> highScore;
            file.close();
        } else {
            highScore = 0;
        }
    }

    void saveHighScore() {
        if (score > highScore) {
            highScore = score;
            ofstream file("highscore.txt");
            if (file.is_open()) {
                file << highScore;
                file.close();
            }
        }
    }

    void generateFood() {
        do {
            food.first = rand() % gridSize;
            food.second = rand() % gridSize;
        } while (isSnake(food));
    }

    bool isSnake(pair<int, int> pos) {
        for (const auto& cell : snake)
            if (cell == pos) return true;
        return false;
    }

    void moveSnake() {
        pair<int, int> head = snake.back();
        pair<int, int> newHead = head;

        switch (direction) {
            case 'W': newHead.first--; break;
            case 'S': newHead.first++; break;
            case 'A': newHead.second--; break;
            case 'D': newHead.second++; break;
        }

        // Check for collisions
        if (newHead.first < 0 || newHead.first >= gridSize || 
            newHead.second < 0 || newHead.second >= gridSize || 
            isSnake(newHead)) {
            gameOver = true;
            return;
        }

        // Move the snake
        snake.push(newHead);

        // Check if food is eaten
        if (newHead == food) {
            score++;
            generateFood();
        } else {
            snake.pop(); // Remove tail
        }
    }

    void displayBoard() {
        system("cls"); // Clear the console for real-time display
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                if (isSnake({i, j}))
                    cout << "O "; // Snake body
                else if (food == make_pair(i, j))
                    cout << "F "; // Food
                else
                    cout << ". "; // Empty space
            }
            cout << endl;
        }
        cout << "Score: " << score << "  High Score: " << highScore << endl;
    }

public:
    SnakeGame(int size) : gridSize(size), direction('D'), gameOver(false), score(0) {
        snake.push({gridSize / 2, gridSize / 2}); // Start snake in the center
        generateFood();
        loadHighScore();
    }

    void play() {
        while (!gameOver) {
            if (_kbhit()) {
                char input = _getch();
                if ((input == 'W' || input == 'A' || input == 'S' || input == 'D') &&
                    abs(direction - input) != 2) {
                    direction = input;
                }
            }

            moveSnake();
            displayBoard();
            _sleep(200); // Control game speed
        }

        saveHighScore();
        cout << "Game Over! Final Score: " << score << endl;
        cout << "Press R to restart or any other key to exit: ";
        char choice;
        cin >> choice;
        if (choice == 'R' || choice == 'r') {
            reset();
            play();
        }
    }

    void reset() {
        // Reset game state
        while (!snake.empty()) snake.pop();
        snake.push({gridSize / 2, gridSize / 2});
        direction = 'D';
        score = 0;
        gameOver = false;
        generateFood();
    }
};

int main() {
    srand(time(0)); // Seed for random number generation
    SnakeGame game(10); // Initialize with a 10x10 grid
    game.play();
    return 0;
}

