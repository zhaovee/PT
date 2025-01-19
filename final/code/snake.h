#ifndef SNAKE_H
#define SNAKE_H

const int MAX_LENGTH = 100;

enum Direction { UP, DOWN, LEFT, RIGHT };

class Snake {
public:
    int body[MAX_LENGTH][2];
    int length;
    Direction direction;

    Snake(int startX, int startY);
    void move();
    void grow();
    void shrink();
    bool isCollision(int x, int y);
};

#endif
