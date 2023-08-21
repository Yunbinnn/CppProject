#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#define MAP_X_MAX 49
#define MAP_Y_MAX 17

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ESCAPE 27

char mapData[MAP_X_MAX * MAP_Y_MAX];

void SetConsole()
{
	system("title RPG test");
	system("mode con:cols=49 lines17");

	HANDLE console;
	CONSOLE_CURSOR_INFO cursor;
	console = GetStdHandle(STD_OUTPUT_HANDLE);

	cursor.bVisible = 0;
	cursor.dwSize = 1;

	SetConsoleCursorInfo(console, &cursor);

	COORD pos = { 0,0 };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetValue()
{
	for (int i = 0; i < MAP_X_MAX * MAP_Y_MAX; i++)
	{
		mapData[i] = ' ';
	}
}

//int main()
//{
//	SetConsole();
//	SetValue();
//
//	int characterX = MAP_X_MAX / 2 + 1;
//	int characterY = MAP_Y_MAX / 2 + 1;
//
//	return 0;
//}