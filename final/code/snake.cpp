#include "snake.h"

Snake::Snake(int startX, int startY) 
{
    body[0][0] = startX;
    body[0][1] = startY;
    length = 1;
    direction = RIGHT;
}

void Snake::move() 
{
    for (int i = length - 1; i > 0; --i) 
    {
        body[i][0] = body[i - 1][0];
        body[i][1] = body[i - 1][1];
    }
    switch (direction) 
    {
        case UP: body[0][0]--; break;
        case DOWN: body[0][0]++; break;
        case LEFT: body[0][1]--; break;
        case RIGHT: body[0][1]++; break;
    }
}

void Snake::grow() 
{
    if (length < MAX_LENGTH) 
    {
        body[length][0] = body[length - 1][0];
        body[length][1] = body[length - 1][1];
        length++;
    }
}

void Snake::shrink() 
{
    if (length > 1) 
    {
        length--;
    }
}

bool Snake::isCollision(int x, int y) 
{
    for (int i = 0; i < length; ++i) 
    {
        if (body[i][0] == x && body[i][1] == y) 
        return true;
    }
    return false;
}
