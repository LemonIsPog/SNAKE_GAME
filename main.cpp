#include <iostream>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <fstream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <string>
#include <windows.h>
#include <vector>

using namespace std;

// Color codes for Windows console
enum COLOR {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    LIGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

class SnakeGame {
private:
    const int GRID_SIZE = 25;
    const int INITIAL_SPEED = 100;
    const int MIN_SPEED = 30;
    const int SPEED_INCREASE = 8;
    
    deque<pair<int, int>> snake;
    pair<int, int> food;
    char direction;
    bool gameOver;
    int score;
    int highScore;
    int gameSpeed;
    int foodColor;
    HANDLE console;
    COORD cursorPosition;
    vector<int> colors = {
        LIGHTRED, LIGHTGREEN, LIGHTBLUE, YELLOW, 
        LIGHTMAGENTA, LIGHTCYAN, WHITE
    };

    void initializeConsole() {
        console = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(console, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(console, &cursorInfo);
    }

    void setColor(int color) {
        SetConsoleTextAttribute(console, color);
    }

    void setCursorPosition(int x, int y) {
        cursorPosition.X = x;
        cursorPosition.Y = y;
        SetConsoleCursorPosition(console, cursorPosition);
    }

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
        if (snake.size() >= GRID_SIZE * GRID_SIZE) {
            gameOver = true;
            return;
        }

        do {
            food.first = rand() % GRID_SIZE;
            food.second = rand() % GRID_SIZE;
        } while (isSnake(food));
        
        foodColor = colors[rand() % colors.size()];
    }

    bool isSnake(const pair<int, int>& pos) const {
        return find(snake.begin(), snake.end(), pos) != snake.end();
    }

    bool isValidMove(char newDirection) const {
        if ((direction == 'W' && newDirection == 'S') ||
            (direction == 'S' && newDirection == 'W') ||
            (direction == 'A' && newDirection == 'D') ||
            (direction == 'D' && newDirection == 'A')) {
            return false;
        }
        return true;
    }

    void updateGameSpeed() {
        gameSpeed = max(MIN_SPEED, INITIAL_SPEED - (score * SPEED_INCREASE));
    }

    void moveSnake() {
        pair<int, int> head = snake.front();
        pair<int, int> newHead = head;

        switch (toupper(direction)) {
            case 'W': newHead.first--; break;
            case 'S': newHead.first++; break;
            case 'A': newHead.second--; break;
            case 'D': newHead.second++; break;
            default: return;
        }

        if (newHead.first < 0 || newHead.first >= GRID_SIZE || 
            newHead.second < 0 || newHead.second >= GRID_SIZE || 
            isSnake(newHead)) {
            gameOver = true;
            return;
        }

        snake.push_front(newHead);

        if (newHead == food) {
            score++;
            generateFood();
            updateGameSpeed();
        } else {
            snake.pop_back();
        }
    }

    void drawBorder() {
        setColor(LIGHTCYAN);
        setCursorPosition(0, 0);
        cout << string(GRID_SIZE * 2 + 2, '#');

        for (int i = 1; i <= GRID_SIZE; i++) {
            setCursorPosition(0, i);
            cout << '#';
            setCursorPosition(GRID_SIZE * 2 + 1, i);
            cout << '#';
        }

        setCursorPosition(0, GRID_SIZE + 1);
        cout << string(GRID_SIZE * 2 + 2, '#');
    }

    void displayBoard() {
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                setCursorPosition(j * 2 + 1, i + 1);
                
                if (make_pair(i, j) == snake.front()) {
                    setColor(LIGHTGREEN);
                    cout << "@ ";
                }
                else if (isSnake({i, j})) {
                    setColor(GREEN);
                    cout << "O ";
                }
                else if (food == make_pair(i, j)) {
                    setColor(foodColor);
                    cout << "* ";
                }
                else {
                    setColor(DARKGRAY);
                    cout << ". ";
                }
            }
        }

        setColor(WHITE);
        setCursorPosition(0, GRID_SIZE + 2);
        cout << "Score: " << score << "  High Score: " << highScore << "  Speed: " << (100 - (gameSpeed - MIN_SPEED)) << "%     ";
        setCursorPosition(0, GRID_SIZE + 3);
        cout << "Controls: W/A/S/D or Arrow keys to move, Q to quit     ";
    }

public:
    SnakeGame() : direction('D'), gameOver(false), score(0), gameSpeed(INITIAL_SPEED) {
        int midRow = GRID_SIZE / 2;
        int midCol = GRID_SIZE / 2;
        snake.push_front({midRow, midCol});
        snake.push_back({midRow, midCol - 1});
        snake.push_back({midRow, midCol - 2});
        
        initializeConsole();
        generateFood();
        loadHighScore();
        system("cls");
        drawBorder();
    }

    void play() {
        while (!gameOver) {
            if (_kbhit()) {
                int input = _getch();
                char newDirection = direction;
                
                // Handle arrow keys and WASD
                if (input == 0 || input == 224) {
                    switch (_getch()) {
                        case 72: newDirection = 'W'; break; // Up arrow
                        case 80: newDirection = 'S'; break; // Down arrow
                        case 75: newDirection = 'A'; break; // Left arrow
                        case 77: newDirection = 'D'; break; // Right arrow
                    }
                } else {
                    input = toupper(input);
                    switch (input) {
                        case 'W':
                        case 'A':
                        case 'S':
                        case 'D':
                            newDirection = input;
                            break;
                        case 'Q':
                            gameOver = true;
                            break;
                    }
                }
                
                if (isValidMove(newDirection)) {
                    direction = newDirection;
                }
            }

            moveSnake();
            displayBoard();
            this_thread::sleep_for(chrono::milliseconds(gameSpeed));
        }

        saveHighScore();
        setColor(WHITE);
        setCursorPosition(0, GRID_SIZE + 4);
        cout << "\nGame Over! Final Score: " << score << endl;
        if (snake.size() >= GRID_SIZE * GRID_SIZE) {
            cout << "Congratulations! You've won!" << endl;
        }
        cout << "Press R to restart or any other key to exit: ";
        char choice;
        cin >> choice;
        if (toupper(choice) == 'R') {
            system("cls");
            reset();
            play();
        }
    }

    void reset() {
        snake.clear();
        int midRow = GRID_SIZE / 2;
        int midCol = GRID_SIZE / 2;
        snake.push_front({midRow, midCol});
        snake.push_back({midRow, midCol - 1});
        snake.push_back({midRow, midCol - 2});
        
        direction = 'D';
        score = 0;
        gameSpeed = INITIAL_SPEED;
        gameOver = false;
        system("cls");
        drawBorder();
        generateFood();
    }

    ~SnakeGame() {
        setColor(WHITE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(console, &cursorInfo);
        cursorInfo.bVisible = true;
        SetConsoleCursorInfo(console, &cursorInfo);
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));
    
    cout << "Welcome to Snake Game!" << endl;
    cout << "Press any key to start...";
    _getch();

    SnakeGame game;
    game.play();
    
    return 0;
}
