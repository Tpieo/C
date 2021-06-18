#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define HIGH 40
#define WIDTH 100

int cnt = 0;
struct BALL
{
    int X;  //球在x方向的位置    o _________ 
    int Y;  //球在y方向的位置     |       y
    int dX; //球在x方向的速度     |
    int dY; //球在y方向的速度     | x
    char icon;
    int flag_dX;
    int flag_dY;
};

void init_pic(char (*pic)[WIDTH]);
void init_ball(struct BALL *ball, int num);
void process(struct BALL *ball, char (*pic)[WIDTH], int num);

void main()
{
    system("mode con cols=100 lines=41"); //设置窗口大小
    srand(time(NULL));

    //接受球的个数，最大是10
    printf("请输入球的个数（最大值：10）：");
    int num; //球的个数
    scanf("%d", &num);
    if (num > 10)
        num = 10;

    //图像初始化
    char pic[HIGH][WIDTH] = {0};
    init_pic(pic);

    //球初始化
    struct BALL *ball = (struct BALL *)malloc(sizeof(struct BALL) * num);
    init_ball(ball, num);

    while (1)
    {
        //处理每一张图像
        process(ball, pic, num);
        Sleep(25);
        system("cls");
    }
}

void init_pic(char (*pic)[WIDTH])
{
    int i, j;
    for (i = 0; i < HIGH; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            pic[i][j] = ' ';
        }
    }
    for (i = 0; i < HIGH; i++)
    {
        pic[i][WIDTH - 1] = '\n';
        pic[i][0] = '|';
        pic[i][WIDTH - 2] = '|';
    }
    for (i = 0; i < WIDTH - 1; i++)
    {
        pic[0][i] = '*';
        pic[HIGH - 1][i] = '*';
    }
    pic[HIGH - 1][WIDTH - 1] = '\0';
}

void init_ball(struct BALL *ball, int num)
{
    char icon_8[8] = {'@', '#', '$', '%', 'o', 'O', 'Q', '&'};
    for (int i = 0; i < num; i++)
    {
        (ball + i)->X = rand() % (HIGH - 6) + 3;
        (ball + i)->Y = rand() % (WIDTH - 6) + 3;
        (ball + i)->dX =rand() % 5 - 2;
        while ((ball + i)->dX == 0)
            (ball + i)->dX =rand() % 5 - 2;
        (ball + i)->dY =rand() % 5 - 2;
        while ((ball + i)->dY == 0)
            (ball + i)->dY =rand() % 5 - 2;
        (ball + i)->icon = icon_8[rand() % 8];
        (ball + i)->flag_dX = 0;
        (ball + i)->flag_dY = 0;
    }
}

void process(struct BALL *ball, char (*pic)[WIDTH], int num)
{
    //打印
    for (int i = 0; i < num; i++)
        pic[(ball + i)->X][(ball + i)->Y] = (ball + i)->icon;
    printf("%s", pic);
    init_pic(pic);
    for (int i = 0; i < num; i++)
    {
        (ball + i)->X += (ball + i)->dX;
        (ball + i)->Y += (ball + i)->dY;
    }

    //边界检测
    for (int i = 0; i < num; i++)
    {
        if ((ball + i)->X >= HIGH - 3)
        {
            (ball + i)->dX = -(ball + i)->dX;
            (ball + i)->flag_dX = 1;
            cnt++;
            putchar('\7');
        }
        if ((ball + i)->X <= 2)
            (ball + i)->dX = -(ball + i)->dX;
            (ball + i)->flag_dX = 1;
        if ((ball + i)->Y >= WIDTH - 3)
            (ball + i)->dY = -(ball + i)->dY;
            (ball + i)->flag_dY = 1;
        if ((ball + i)->Y <= 2)
            (ball + i)->dY = -(ball + i)->dY;
            (ball + i)->flag_dY = 1;
    }

    //碰撞检测
    for (int i = 0; i < num; i++)
    {
        for (int j = i + 1; j < num; j++)
        {
            double dist = sqrt(pow((ball + i)->X - (ball + j)->X, 2) + pow((ball + i)->Y - ((ball + j)->Y), 2));
            if (dist <= 1)
            {
                if ((ball + i)->flag_dX == 0)
                    (ball + i)->dX = -(ball + i)->dX;
                if ((ball + i)->flag_dY == 0)
                    (ball + i)->dY = -(ball + i)->dY;
                if ((ball + j)->flag_dX == 0)
                    (ball + j)->dX = -(ball + j)->dX;
                if ((ball + j)->flag_dY == 0)
                    (ball + j)->dY = -(ball + j)->dY;
            }
        }
    }

    for (int i = 0; i < num; i++)
    {
        (ball + i)->flag_dX = 0;
        (ball + i)->flag_dY = 0;
    }
    printf("\n落地次数%d", cnt);
}
