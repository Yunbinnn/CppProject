#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#define WIDTH 11
#define HEIGHT 11

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ESCAPE 27

// 미로 맵 데이터
char maze[WIDTH][HEIGHT];

// 플레이어 데이터
struct Player
{
	int x, y;
	const char* shape;
};

// 미로 생성 함수
void CreateMaze()
{
	// 0 : 빈 공간 ("  ")
	// 1 : 벽	  ("■")
	// 2 : 탈출구  ("◎")

	strcpy(maze[0], "1111111111");
	strcpy(maze[1], "1001000101");
	strcpy(maze[2], "1100010001");
	strcpy(maze[3], "1111011111");
	strcpy(maze[4], "1000000001");
	strcpy(maze[5], "1011110111");
	strcpy(maze[6], "1110000101");
	strcpy(maze[7], "1000111101");
	strcpy(maze[8], "1010000001");
	strcpy(maze[9], "1110111011");
	strcpy(maze[10], "1111111211");
}

// 화면에 미로를 렌더링
void Renderer()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			if (maze[i][j] == '0')
				printf("  ");

			if (maze[i][j] == '1')
				printf("■");

			if (maze[i][j] == '2')
				printf("◎");
		}
		printf("\n");
	}
}

// 키보드 입력 함수
void Keyboard(char map[WIDTH][HEIGHT], Player* player)
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
		case LEFT: if (map[player->y][player->x / 2 - 1] != '1')
		{
			if (map[player->y][player->x / 2 - 1] == '2')
			{
				player->x -= 2;
				printf("\n탈출 성공!\n");
				exit(1);
			}

			player->x -= 2;
		}
				 break;
		case RIGHT: if (map[player->y][player->x / 2 + 1] != '1')
		{
			if (map[player->y][player->x / 2 + 1] == '2')
			{
				player->x += 2;
				printf("\n탈출 성공!\n");
				exit(1);
			}

			player->x += 2;
		}
				  break;
		case UP:  if (map[player->y - 1][player->x / 2] != '1')
		{
			if (map[player->y - 1][player->x / 2] == '2')
			{
				player->y--;
				printf("\n탈출 성공!\n");
				exit(1);
			}

			player->y--;
		}
			   break;
		case DOWN: if (map[player->y + 1][player->x / 2] != '1')
		{
			if (map[player->y + 1][player->x / 2] == '2')
			{
				player->y++;
				printf("\n탈출 성공!\n");
				exit(1);
			}

			player->y++;
		}
				 break;
		}
	}
}

// 키 입력에 따른 플레이어 좌표 이동 함수
void gotoXY(int x, int y)
{
	// x, y 좌표 설정
	COORD position = { x, y };

	// 커서 이동
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

int main()
{
	Player player = { 1, 1, "★" };

	player.x++;

	CreateMaze();

	while (1)
	{
		Renderer();

		Keyboard(maze, &player);

		gotoXY(player.x, player.y);

		printf("%s", player.shape);

		Sleep(100);

		system("cls");
	}


	return 0;
}