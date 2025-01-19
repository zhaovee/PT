#ifndef GAME_H
#define GAME_H
#include "snake.h"

#define ROWS 20
#define COLS 30
#define CELL_SIZE 20
#define WIDTH 1280
#define HEIGHT 720

class Game {
public:
    Snake snake;
    int score;
    int redFood[6][2];
    int blackFood[3][2];
    int obstacles[4][2];
    bool isGameOver; // 用于检测游戏是否结束

    Game();
    void generateRedFood();
    void generateBlackFood();
    void generateObstacles();
    void moveObstacles();
    void update();
    void draw();
};

#endif

