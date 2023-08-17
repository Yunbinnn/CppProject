#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ESCAPE 27

#pragma region 더블 버퍼링


// HANDLE 인덱스에 접근해서 버퍼를 교체시키는 변수
int screenIndex = 0;

// 버퍼의 크기
int width = 100;
int height = 60;

// 버퍼 생성
HANDLE Screen[2];

// [0] : Front Buffer
// [1] : Back Buffer

struct Player
{
	int x;
	int y;
	const char* shape;
};

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

int main()
{
#pragma region 더블 버퍼링

	/*
	char key = 0;

	Player player = { 5, 5, "★" };

	// 1. 버퍼 초기화
	Init();

	while (1)
	{
		if (_kbhit()) // 키보드 입력을 확인하는 함수
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
			case UP: if (player.y <= 0) break;
				player.y--;
				break;
			case LEFT: if (player.x <= 1) break;
				player.x -= 2;
				break;
			case RIGHT:	if (player.x >= 117) break;
				player.x += 2;
				break;
			case DOWN: if (player.y >= 29)break;
				player.y++;
				break;
			}
		}

		ShowBuffer(player.x, player.y, player.shape);

		// 2. 버퍼 교체
		Flipping();

		// 3. 교체된 버퍼의 내용을 삭제합니다.
		Clear();
	}

	// 4. 버퍼를 해제합니다.
	ReleaseScreen();
	*/
#pragma endregion

#pragma region 최대 공약수

	/*
	int x, y;

	int result = 0;
	int result2 = 0;

	printf("정수를 입력하세요. : ");

	scanf_s("%d %d", &x, &y);

	printf("\n");

	for (int i = 1; i <= x && i <= y; i++)
	{
		if (x % i == 0 && y % i == 0)
			result = i;
	}

	printf("%d와 %d의 최대 공약수 : %d\n", x, y, result);

	result2 = (x * y) / result;

	printf("\n%d와 %d의 최대 공배수 : %d\n", x, y, result2);
	*/

#pragma endregion

	return 0;
}