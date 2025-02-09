#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <fstream>

using namespace std;

class SnakeGame {
private:
    int gridSize;
    queue<pair<int, int>> snake;
    pair<int, int> food;
    char direction;
    bool gameOver;
    int score;
    int highScore;

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

        if (newHead.first < 0 || newHead.first >= gridSize || 
            newHead.second < 0 || newHead.second >= gridSize || 
            isSnake(newHead)) {
            gameOver = true;
            return;
        }

        snake.push(newHead);

        if (newHead == food) {
            score++;
            generateFood();
        } else {
            snake.pop();
        }
    }

    void displayBoard() {
        system("cls");
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                if (isSnake({i, j}))
                    cout << "O ";
                else if (food == make_pair(i, j))
                    cout << "F ";
                else
                    cout << ". ";
            }
            cout << endl;
        }
        cout << "Score: " << score << "  High Score: " << highScore << endl;
    }

public:
    SnakeGame(int size) : gridSize(size), direction('D'), gameOver(false), score(0) {
        snake.push({gridSize / 2, gridSize / 2});
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
            _sleep(200);
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
        while (!snake.empty()) snake.pop();
        snake.push({gridSize / 2, gridSize / 2});
        direction = 'D';
        score = 0;
        gameOver = false;
        generateFood();
    }
};

int main() {
    srand(time(0));
    SnakeGame game(10);
    game.play();
    return 0;
}
