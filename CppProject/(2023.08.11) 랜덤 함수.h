#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int life;
int computer;
int answer;

void Init()
{
	srand(time(NULL));

	life = 5;
	computer = rand() % 50 + 1;
}

void Update()
{
	printf("��ǻ�Ͱ� ������ �ִ� �� : ");

	scanf_s("%d", &answer);
}

void Render()
{
	if (computer == answer)
	{
		printf("\n���ӿ��� �¸��Ͽ����ϴ�.\n");
		exit(1);
	}
	else if (computer > answer)
	{
		printf("\n��ǻ�Ͱ� ������ �ִ� ������ �۽��ϴ�.\n");
		life--;
	}
	else if (computer < answer)
	{
		printf("\n��ǻ�Ͱ� ������ �ִ� ������ Ů�ϴ�.\n");
		life--;
	}

	if (life <= 0)
	{
		printf("\n���ӿ��� �й��Ͽ����ϴ�.\n");
	}
}

int main()
{
#pragma region ���� �Լ�
	// 0 ~ 32767 ������ ���� ���� ��ȯ�ϴ� �Լ��Դϴ�.

	/*
	int seed = 0;

	// 1970�� 1�� 1�� ~
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		seed = rand() % 10 + 1;
		printf("seed�� �� : %d\n", abs(seed));
	}
	*/
#pragma endregion

#pragma region Up And Down

	/*
	int rand_num;
	int input;
	int hp = 5;
	int flag = 1;

	srand(time(NULL));
	rand_num = rand() % 50 + 1;

	while (flag)
	{
		printf("���ڸ� �Է��ϼ��� : ");
		scanf_s("%d", &input);
		printf("\n");

		while (input < 1 || input > 50)
		{
			printf("��ǻ�Ͱ� ���� ���� ���� �� �Դϴ�.\n\n");
			printf("�ٽ� ���ڸ� �Է��ϼ��� : ");
			scanf_s("%d", &input);
			printf("\n");
		}

		if (input == rand_num)
		{
			printf("���ӿ��� �¸��Ͽ����ϴ�.\n\n");
			flag = 0;
			break;
		}

		if (input > rand_num)
		{
			printf("���� ��ǻ�Ͱ� ������ �ִ� ������ Ů�ϴ�.\n");
			hp--;
			printf("���� ���� ü�� : %d\n\n", hp);
		}
		else
		{
			printf("���� ��ǻ�Ͱ� ������ �ִ� ������ �۽��ϴ�.\n\n");
			hp--;
			printf("���� ���� ü�� : %d\n\n", hp);
		}

		if (hp <= 0)
		{
			printf("���ӿ��� �й��Ͽ����ϴ�.\n");
			flag = 0;
		}
	}
	*/

	// ���� ������ �ʱ�ȭ
	Init();

	while (life > 0)
	{
		// ���� ������Ʈ �Լ�
		Update();

		// ���� ������ �Լ� 
		Render();
	}

#pragma endregion

	return 0;
}