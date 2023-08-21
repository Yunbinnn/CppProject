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

#pragma region 더블 버퍼링

int width = 100, height = 60;

HANDLE Screen[2];

int screenIndex;

// 버퍼를 초기화하는 함수
void Init()
{
	CONSOLE_CURSOR_INFO cursor;

	// 버퍼의 가로 사이즈, 세로 사이즈
	COORD size = { width,height };

	// LEFT, TOP, RIGHT, BOTTOM
	SMALL_RECT rect = { 0,0,width - 1,height - 1 };

	// 화면 2개를 생성합니다.
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

	// 커서의 활성화 여부
	// false : 거짓
	// true : 참
	cursor.bVisible = false;

	SetConsoleCursorInfo(Screen[0], &cursor);
	SetConsoleCursorInfo(Screen[1], &cursor);
}

// 버퍼를 교체하는 함수
void Flipping()
{
	// 버퍼는 하나만 활성화 시킬 수 있습니다.
	SetConsoleActiveScreenBuffer(Screen[screenIndex]);

	screenIndex = !screenIndex;
}

// 교체된 버퍼를 지워주는 함수
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

// 버퍼를 해제하는 함수
void ReleaseScreen()
{
	CloseHandle(Screen[0]);
	CloseHandle(Screen[1]);
}

// 버퍼를 이용해서 출력하는 함수
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
		case ESCAPE: printf("\n프로그램 종료\n"); exit(1);
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
	// x, y 좌표 설정
	COORD position = { x, y };

	// 커서 이동
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

int main()
{
#pragma region 문자열 관련 함수

	// 문자열 길이 함수
	/*
	const char* name = "James";
	int result = strlen(name);
	printf("result의 값 : %d\n", result);
	*/

	// 문자열 연결 함수
	/*
	char firstArr[20] = "First";
	char secondArr[] = "Second";

	strcat(firstArr, secondArr);

	printf("firstArr의 값 : %s\n", firstArr);
	*/

	// 문자열 복사 함수
	/*
	char a[10] = { "String" };
	char b[10];

	// 첫 번째 매개변수 : 복사받을 문자 배열
	// 두 번째 매개변수 : 복사할 문자 배열
	strcpy(b, a);

	printf("a의 문자열 : %s\n", a);
	printf("b의 문자열 : %s\n", b);
	*/

	// 문자열 비교 함수
	/*
	char firstA[] = { "ABC" };
	char secondB[] = { "ABC" };

	// 서로 같으면 "0"
	// 앞쪽에 있는 값이 크면 "1"
	// 뒤쪽에 있는 값이 크면 "-1"

	printf("두 문자열을 비교한 결과 : %d\n", strcmp(firstA, secondB));
	*/

#pragma endregion

#pragma region 똥피하기

	system("mode con cols=30 lines=25");

	Player player = { 4, 24, "■" };

	Enemy enemy = { RandomX(), 0, "▼" };

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
			printf("게임 오버\n");
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