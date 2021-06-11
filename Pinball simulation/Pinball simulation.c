// ���ߣ�֣����

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
    int X;  //����x�����λ��    o _________ 
    int Y;  //����y�����λ��     |       y
    int dX; //����x������ٶ�     |
    int dY; //����y������ٶ�     | x
};

void init_pic(char (*pic)[WIDTH]);
void init_ball(struct BALL *ball, int num);
void process(struct BALL *ball, char (*pic)[WIDTH], int num);

void main()
{
    system("mode con cols=100 lines=41"); //���ô��ڴ�С
    srand(time(NULL));

    //������ĸ����������10
    printf("��������ĸ�����");
    int num; //��ĸ���
    scanf("%d", &num);
    if (num > 10)
        num = 10;

    //ͼ���ʼ��
    char pic[HIGH][WIDTH] = {0};
    init_pic(pic);

    //���ʼ��
    struct BALL *ball = (struct BALL *)malloc(sizeof(struct BALL) * num);
    init_ball(ball, num);

    while (1)
    {
        //����ÿһ��ͼ��
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
    for (int i = 0; i < num; i++)
    {
        (ball + i)->X = rand() % (HIGH - 5) + 1;
        (ball + i)->Y = rand() % (WIDTH - 5) + 1;
        (ball + i)->dX = rand() % 2 + 1;
        (ball + i)->dY = rand() % 2 + 1;
    }
}

void process(struct BALL *ball, char (*pic)[WIDTH], int num)
{
    //��ӡ
    for (int i = 0; i < num; i++)
        pic[(ball + i)->X][(ball + i)->Y] = 'o';
    printf("%s", pic);
    init_pic(pic);
    for (int i = 0; i < num; i++)
        pic[(ball + i)->X][(ball + i)->Y] = ' ';
    for (int i = 0; i < num; i++)
    {
        (ball + i)->X += (ball + i)->dX;
        (ball + i)->Y += (ball + i)->dY;
    }

    //�߽���
    for (int i = 0; i < num; i++)
    {
        if ((ball + i)->X >= HIGH - 3)
        {
            (ball + i)->dX = -(ball + i)->dX;
            cnt++;
            putchar('\7');
        }
        if ((ball + i)->X <= 2)
            (ball + i)->dX = -(ball + i)->dX;
        if ((ball + i)->Y >= WIDTH - 5)
            (ball + i)->dY = -(ball + i)->dY;
        if ((ball + i)->Y <= 2)
            (ball + i)->dY = -(ball + i)->dY;
    }
    printf("\n��ش���%d", cnt);

    //��ײ���
    for (int i = 0; i < num; i++)
    {
        for (int j = i + 1; j < num; j++)
        {
            double dist = sqrt(pow((ball + i)->X - (ball + j)->X, 2) + pow((ball + i)->Y - ((ball + j)->Y), 2));
            if (dist <= 1)
            {
                (ball + i)->dX = -(ball + i)->dX;
                (ball + i)->dY = -(ball + i)->dY;
                (ball + j)->dX = -(ball + j)->dX;
                (ball + j)->dY = -(ball + j)->dY;
            }
        }
    }
}