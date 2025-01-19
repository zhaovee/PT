#include "game.h"
#include <graphics.h>
#include <cstdlib>
#include <cstdio>

Game::Game() : snake(COLS / 2, ROWS / 2), score(0), isGameOver(false) 
{
    generateRedFood();
    generateBlackFood();
    generateObstacles();
}

void Game::generateRedFood() 
{
    for (int i = 0; i < 6; ++i) 
    {
        redFood[i][0] = rand() % (HEIGHT / CELL_SIZE);
        redFood[i][1] = rand() % (WIDTH / CELL_SIZE);
    }
}

void Game::generateBlackFood() 
{
    for (int i = 0; i < 3; ++i) 
    {
        blackFood[i][0] = rand() % (HEIGHT / CELL_SIZE);
        blackFood[i][1] = rand() % (WIDTH / CELL_SIZE);
    }
}

void Game::generateObstacles()
{
    for (int i = 0; i < 4; ++i) 
    {
        obstacles[i][0] = rand() % (HEIGHT / CELL_SIZE);
        obstacles[i][1] = rand() % (WIDTH / CELL_SIZE);
    }
}

void Game::moveObstacles() 
{
    for (int i = 0; i < 4; ++i) 
    {
        int direction = rand() % 4;
        switch (direction) {
            case 0: obstacles[i][0] = (obstacles[i][0] - 1 + (HEIGHT / CELL_SIZE)) % (HEIGHT / CELL_SIZE); break; // 上
            case 1: obstacles[i][0] = (obstacles[i][0] + 1) % (HEIGHT / CELL_SIZE); break;                   // 下
            case 2: obstacles[i][1] = (obstacles[i][1] - 1 + (WIDTH / CELL_SIZE)) % (WIDTH / CELL_SIZE); break; // 左
            case 3: obstacles[i][1] = (obstacles[i][1] + 1) % (WIDTH / CELL_SIZE); break;                   // 右
        }
    }
}

void Game::update() 
{
    if (isGameOver) return;

    snake.move();
    // Check to see if you hit the boundary
    if (snake.body[0][0] < 0 || snake.body[0][0] >= (HEIGHT / CELL_SIZE) ||
        snake.body[0][1] < 0 || snake.body[0][1] >= (WIDTH / CELL_SIZE)) 
    {
        isGameOver = true;
        return;
    }
    // Check for collisions with red food
    for (int i = 0; i < 6; ++i) 
    {
        if (snake.body[0][0] == redFood[i][0] && snake.body[0][1] == redFood[i][1]) 
        {
            snake.grow();
            score += 10;
            redFood[i][0] = rand() % ROWS;
            redFood[i][1] = rand() % COLS;
        }
    }

    // Check for collisions with black food
    for (int i = 0; i < 3; ++i) 
    {
        if (snake.body[0][0] == blackFood[i][0] && snake.body[0][1] == blackFood[i][1]) 
        {
            snake.shrink();
            score -= 5;
            blackFood[i][0] = rand() % ROWS;
            blackFood[i][1] = rand() % COLS;
        }
    }

    // Check for collision obstacles
    for (int i = 0; i < 4; ++i) 
    {
        for (int j = 0; j < 2; ++j) 
        {
            for (int k = 0; k < 2; ++k) 
            {
                if (snake.body[0][0] == obstacles[i][0] + j && snake.body[0][1] == obstacles[i][1] + k) 
                {
                    isGameOver = true;
                    return;
                }
            }
        }
    }

    moveObstacles();
}

void Game::draw() 
{
    cleardevice();
    readimagefile("b1.bmp",0,0,WIDTH,HEIGHT);
    if (isGameOver) 
    {
        setcolor(RED);
        outtextxy(WIDTH / 2 - 50, HEIGHT / 2 - 20, "Game Over");

        // Show total score
        char finalScoreText[30];
        sprintf(finalScoreText, "Your Score: %d", score);
        outtextxy(WIDTH / 2 - 70, HEIGHT / 2 + 20, finalScoreText);

        return;
    }

    // Draw Snake
    setcolor(BLUE);
    for (int i = 0; i < snake.length; ++i) 
    {
        rectangle(snake.body[i][1] * CELL_SIZE, snake.body[i][0] * CELL_SIZE,
                  (snake.body[i][1] + 1) * CELL_SIZE, (snake.body[i][0] + 1) * CELL_SIZE);
        setfillstyle(SOLID_FILL, BLUE);
        floodfill(snake.body[i][1] * CELL_SIZE + 1, snake.body[i][0] * CELL_SIZE + 1, BLUE);
    }

    // Draw red food
    setfillstyle(SOLID_FILL, RED);
    for (int i = 0; i < 6; ++i) 
    {
        bar(redFood[i][1] * CELL_SIZE, redFood[i][0] * CELL_SIZE,
            (redFood[i][1] + 1) * CELL_SIZE, (redFood[i][0] + 1) * CELL_SIZE);
    }

    //Draw black food
    setfillstyle(SOLID_FILL, BLACK);
    for (int i = 0; i < 3; ++i) 
    {
        bar(blackFood[i][1] * CELL_SIZE, blackFood[i][0] * CELL_SIZE,
            (blackFood[i][1] + 1) * CELL_SIZE, (blackFood[i][0] + 1) * CELL_SIZE);
    }

    // Draw obstacles
    setfillstyle(SOLID_FILL, GREEN);
    for (int i = 0; i < 4; ++i) 
    {
        bar(obstacles[i][1] * CELL_SIZE, obstacles[i][0] * CELL_SIZE,
            (obstacles[i][1] + 2) * CELL_SIZE, (obstacles[i][0] + 2) * CELL_SIZE);
    }

    // Draw score
    setcolor(WHITE);
    char scoreText[20];
    sprintf(scoreText, "Score: %d", score);
    outtextxy(10, 10, scoreText);
}
