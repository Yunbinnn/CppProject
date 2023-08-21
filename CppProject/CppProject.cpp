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

// 버퍼의 크기
int width = 100;
int height = 60;

HANDLE Screen[2];

int screenIndex = 0;

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
		case LEFT: if (map[player->y][player->x / 2 - 1] != '1')
		{
			player->x -= 2;
		}
				 break;
		case RIGHT: if (map[player->y][player->x / 2 + 1] != '1')
		{
			player->x += 2;
		}
				  break;
		case UP:  if (map[player->y - 1][player->x / 2] != '1')
		{
			player->y--;
		}
			   break;
		case DOWN: if (map[player->y + 1][player->x / 2] != '1')
		{
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


	Init();

	while (1)
	{
		Renderer();

		Keyboard(maze, &player);

		printf("%s", player.shape);

		ShowBuffer(player.x, player.y, player.shape);

		// 2. 버퍼 교체
		Flipping();

		// 3. 교체된 버퍼의 내용을 삭제합니다.
		Clear();
	}

	// 4. 버퍼를 해제합니다.
	ReleaseScreen();

	return 0;
}