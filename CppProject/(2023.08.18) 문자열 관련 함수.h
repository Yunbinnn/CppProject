#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ESCAPE 27

struct Player
{
	int x, y;
	const char* shape;
};

struct Enemy
{
	int x, y;
	const char* shape;
};

#pragma region ���� ���۸�

int width = 100, height = 60;

HANDLE Screen[2];

int screenIndex;

// ���۸� �ʱ�ȭ�ϴ� �Լ�
void Init()
{
	CONSOLE_CURSOR_INFO cursor;

	// ������ ���� ������, ���� ������
	COORD size = { width,height };

	// LEFT, TOP, RIGHT, BOTTOM
	SMALL_RECT rect = { 0,0,width - 1,height - 1 };

	// ȭ�� 2���� �����մϴ�.
	// FRONT BUFFER
	Screen[0] = CreateConsoleScreenBuffer
	(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);

	SetConsoleScreenBufferSize(Screen[0], size);

	SetConsoleWindowInfo(Screen[0], TRUE, &rect);

	// BACK BUFFER
	Screen[1] = CreateConsoleScreenBuffer
	(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);

	SetConsoleScreenBufferSize(Screen[1], size);

	SetConsoleWindowInfo(Screen[1], TRUE, &rect);

	// Ŀ���� Ȱ��ȭ ����
	// false : ����
	// true : ��
	cursor.bVisible = false;

	SetConsoleCursorInfo(Screen[0], &cursor);
	SetConsoleCursorInfo(Screen[1], &cursor);
}

// ���۸� ��ü�ϴ� �Լ�
void Flipping()
{
	// ���۴� �ϳ��� Ȱ��ȭ ��ų �� �ֽ��ϴ�.
	SetConsoleActiveScreenBuffer(Screen[screenIndex]);

	screenIndex = !screenIndex;
}

// ��ü�� ���۸� �����ִ� �Լ�
void Clear()
{
	COORD coord = { 0, };

	DWORD dw;

	FillConsoleOutputCharacter
	(
		Screen[screenIndex],
		' ',
		width * height,
		coord,
		&dw
	);
}

// ���۸� �����ϴ� �Լ�
void ReleaseScreen()
{
	CloseHandle(Screen[0]);
	CloseHandle(Screen[1]);
}

// ���۸� �̿��ؼ� ����ϴ� �Լ�
void ShowBuffer(int x, int y, const char* string)
{
	COORD cursorPosition = { x,y };

	DWORD dw;

	SetConsoleCursorPosition(Screen[screenIndex], cursorPosition);

	WriteFile
	(
		Screen[screenIndex],
		string,
		strlen(string),
		&dw,
		NULL
	);
}

#pragma endregion

void Keyboard(Player* player)
{
	char key = 0;

	if (_kbhit())
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
		case LEFT: if (player->x <= 0) return;
			player->x -= 2;
			break;
		case RIGHT: if (player->x >= 28)return;
			player->x += 2;
			break;
		}
	}
}

int RandomX()
{
	srand(time(NULL));

	int x = rand() % 31;

	if (x % 2 == 1)
	{
		x += 1;
	}

	return x;
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
#pragma region ���ڿ� ���� �Լ�

	// ���ڿ� ���� �Լ�
	/*
	const char* name = "James";
	int result = strlen(name);
	printf("result�� �� : %d\n", result);
	*/

	// ���ڿ� ���� �Լ�
	/*
	char firstArr[20] = "First";
	char secondArr[] = "Second";

	strcat(firstArr, secondArr);

	printf("firstArr�� �� : %s\n", firstArr);
	*/

	// ���ڿ� ���� �Լ�
	/*
	char a[10] = { "String" };
	char b[10];

	// ù ��° �Ű����� : ������� ���� �迭
	// �� ��° �Ű����� : ������ ���� �迭
	strcpy(b, a);

	printf("a�� ���ڿ� : %s\n", a);
	printf("b�� ���ڿ� : %s\n", b);
	*/

	// ���ڿ� �� �Լ�
	/*
	char firstA[] = { "ABC" };
	char secondB[] = { "ABC" };

	// ���� ������ "0"
	// ���ʿ� �ִ� ���� ũ�� "1"
	// ���ʿ� �ִ� ���� ũ�� "-1"

	printf("�� ���ڿ��� ���� ��� : %d\n", strcmp(firstA, secondB));
	*/

#pragma endregion

#pragma region �����ϱ�

	system("mode con cols=30 lines=25");

	Player player = { 4, 24, "��" };

	Enemy enemy = { RandomX(), 0, "��" };

	Init();

	while (1)
	{
		Keyboard(&player);

		if (enemy.y >= 25)
		{
			enemy.y = 0;
			enemy.x = RandomX();
		}

		if (player.x == enemy.x && player.y == enemy.y)
		{
			break;
			printf("���� ����\n");
			exit(1);
		}

		gotoXY(enemy.x, enemy.y++);
		printf("%s", enemy.shape);

		gotoXY(player.x, player.y);
		printf("%s", player.shape);

		Sleep(100);

		system("cls");
	}
#pragma endregion

	return 0;
}