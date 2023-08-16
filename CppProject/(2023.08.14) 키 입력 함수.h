#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ESCAPE 27

void draw(int a[30][30])
{
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			if (a[i][j] == 0)//�����ȿ���
				printf("��");
			else if (a[i][j] == 1)//������
				printf("��");
			else if (a[i][j] == 2)//����
				printf("��");
		}
		printf("\n");
	}
}

void gotoXY(int x, int y)
{
	// x, y ��ǥ ����
	COORD position = { x, y };

	// Ŀ�� �̵�
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

int main()
{
#pragma region _kbhit() �Լ�

	/*
	char key = 0;
	int x = 5;
	int y = 5;

	// Update( )
	while (1)
	{
		gotoXY(x, y);
		printf("��");

		if (_kbhit()) // Ű���� �Է��� Ȯ���ϴ� �Լ�
		{
			key = _getch();

			if (key == -32)
			{
				key = _getch();
			}

			switch (key)
			{
			case ESCAPE: printf("\n���α׷� ����\n"); exit(1);
				break;
			case UP: if (y <= 0) break;
				y--;
				break;
			case LEFT: if (x <= 0) break;
				x--;
				break;
			case RIGHT: if (x >= 117) break;
				x++;
				break;
			case DOWN: if (y >= 33)break;
				y++;
				break;
			}

			// ��ũ���� ����� �Լ�
			system("cls");
		}
	}
	*/

#pragma endregion

#pragma region ����
	/*
	int map[30][30];
	int hide[30][30];
	srand((unsigned)time(NULL));
	int a, b, c, d, k;
	for (int i = 0; i < 30; i++)//�迭 ��簪 0���� ����
	{
		for (int j = 0; j < 30; j++)
		{
			map[i][j] = 0;
			hide[i][j] = 0;
		}
	}
	printf("������ ���ڰ����� �Է����ּ���(30x30)\n");
	scanf_s("%d", &k);
	for (int i = 0; i < k; i++)//���ڻ���
	{

		while (1)
		{
			a = rand() % 30;
			b = rand() % 30;
			if (map[a][b] == 1)
				;
			else
			{
				map[a][b] = 1;
				break;
			}
		}

		map[a][b] = 1;

	}
	while (1)
	{
		draw(hide);
		printf("x��ǥ�Է�: ");
		scanf_s("%d", &c);
		printf("y��ǥ�Է�: ");
		scanf_s("%d", &d);

		c--;
		d--;

		if (c >= 30 || d >= 30 || c < 0 || d < 0)
		{
			printf("�������� ���ڸ��Է����ּ���\n");
			Sleep(1000);
		}
		else if (map[c][d] == 1)
		{
			hide[c][d] = 1;
			system("cls");
			draw(hide);
			printf("���Դϴ�~�Ф�\n");
			Sleep(2000);
			break;
		}
		else if (hide[c][d] == 2)
		{
			printf("�̹� �湮�߽��ϴ�^^\n");
		}
		else if (map[c][d] == 0)
		{
			printf("�¾ҽ��ϴ�~^^\n");
			hide[c][d] = 2;
		}

		Sleep(1000);
		system("cls");
	}
	printf("������ġ\n");
	draw(map);//���� ������ ������ġ ������
	*/

#pragma endregion

	return 0;
}