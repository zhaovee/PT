#include <graphics.h>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include "game.h"

// 定义菜单相关函数
void showMenu();
bool isButtonClicked(int x1, int y1, int x2, int y2, int clickX, int clickY);

int main() 
{
    initwindow(WIDTH, HEIGHT, "Snake Game");

    // 显示菜单
    showMenu();

    Game game;

    int activepage = 0; // 当前活动页面

    clock_t lastUpdate = clock(); // 记录上一次更新的时间

    while (true) {
        // 处理输入：优先检测退出键
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            break;

        // 检测方向键输入
        if (GetAsyncKeyState(VK_UP) & 0x8000 && game.snake.direction != DOWN)
            game.snake.direction = UP;
        if (GetAsyncKeyState(VK_DOWN) & 0x8000 && game.snake.direction != UP)
            game.snake.direction = DOWN;
        if (GetAsyncKeyState(VK_LEFT) & 0x8000 && game.snake.direction != RIGHT)
            game.snake.direction = LEFT;
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && game.snake.direction != LEFT)
            game.snake.direction = RIGHT;

        // 控制游戏逻辑更新频率
        if (clock() - lastUpdate > 200) 
        { 
            lastUpdate = clock();

            // 设置活动页面（绘制）
            setactivepage(activepage);
            cleardevice();

            // 更新游戏逻辑并绘制
            game.update();
            game.draw();

            // 设置显示页面
            setvisualpage(activepage);

            // 页面切换
            activepage = 1 - activepage;
        }

        delay(50); // 短时间延迟，用于输入检测更灵敏
    }

    closegraph();
    return 0;
}

void showMenu() {
    // 加载菜单背景图片
    readimagefile("b1.bmp", 0, 0, WIDTH, HEIGHT);

    // 计算按钮位置（居中）
    int buttonWidth = 240;
    int buttonHeight = 50;
    int startX = (WIDTH - buttonWidth) / 2;
    int startY1 = HEIGHT / 3;
    int startY2 = startY1 + buttonHeight + 50; // 两个按钮之间留 50 像素间距

    // 绘制“游戏开始”按钮
    setfillstyle(SOLID_FILL, LIGHTGREEN);
    bar(startX, startY1, startX + buttonWidth, startY1 + buttonHeight);
    setcolor(WHITE);
    outtextxy(startX + (buttonWidth - textwidth("Game Start")) / 2, startY1 + (buttonHeight - textheight("Game Start")) / 2, "Game Start");

    // 绘制“退出游戏”按钮
    setfillstyle(SOLID_FILL, RED);
    bar(startX, startY2, startX + buttonWidth, startY2 + buttonHeight);
    setcolor(WHITE);
    outtextxy(startX + (buttonWidth - textwidth("Exit Game")) / 2, startY2 + (buttonHeight - textheight("Exit Game")) / 2, "Exit Game");

    // 等待用户点击
    while (true) 
    {
        if (ismouseclick(WM_LBUTTONDOWN)) 
        {
            int clickX, clickY;
            getmouseclick(WM_LBUTTONDOWN, clickX, clickY);

            // 检测是否点击了“游戏开始”按钮
            if (isButtonClicked(startX, startY1, startX + buttonWidth, startY1 + buttonHeight, clickX, clickY)) 
            {
                clearmouseclick(WM_LBUTTONDOWN);
                break; // 进入游戏
            }

            // 检测是否点击了“退出游戏”按钮
            if (isButtonClicked(startX, startY2, startX + buttonWidth, startY2 + buttonHeight, clickX, clickY)) 
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                exit(0); // 退出程序
            }
        }
        delay(10);
    }
}

bool isButtonClicked(int x1, int y1, int x2, int y2, int clickX, int clickY) 
{
    return clickX >= x1 && clickX <= x2 && clickY >= y1 && clickY <= y2;
}
