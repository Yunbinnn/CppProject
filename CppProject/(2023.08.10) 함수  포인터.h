#pragma once

#include <stdio.h>
#include <string.h>

#pragma region �Լ�������
// �Լ��� �ּҰ��� �����ϰ� ����ų �� �ִ� �����Դϴ�.

/*
void Delegate()
{
	printf("�븮��~\n");
}

int Add(int x, int y)
{
	return x + y;
}

int Substract(int x, int y)
{
	return x - y;
}

int Multiple(int x, int y)
{
	return x * y;
}

int Divide(int x, int y)
{
	return x / y;
}

void Calculator(int x, int y, int(*cptr) (int, int))
{
	printf("*cptr �Լ��� ��� : %d\n", cptr(x, y));
}
*/
#pragma endregion

int main()
{

#pragma region �Լ� ������ 
	// �Լ� �����ʹ� �Լ��� ��ȯ���� �Ű� ������ Ÿ���� ��ġ�ؾ� �ϸ�,
	// �Լ� �����͸� ����Ͽ� �������� �޸𸮸� �Ҵ��� �� �����ϴ�.

	/*
	void (*fptr) ();

	Calculator(1, 1, Add);
	Calculator(20, 10, Substract);
	Calculator(5, 5, Multiple);
	Calculator(20, 20, Divide);

	fptr = Delegate;

	fptr();
	*/
#pragma endregion

#pragma region �Ҽ� �Ǻ� �˰���

	/*
	int number;
	int count = 0;

	printf("������ �Է��ϼ��� : ");

	scanf_s("%d", &number);

	printf("\n");

	for (int i = 2; i <= number; i++)
	{
		if (number % i == 0)
			count++;
	}

	printf("�Է� ���� �� : %d\n\n", number);

	if (count == 1)
		printf("�Ҽ��Դϴ�.\n");
	else
		printf("�Ҽ��� �ƴմϴ�.\n");
	*/

#pragma endregion

#pragma region ȸ�� �Ǻ� �˰���

	/*
	const char* content = "AABB";

	int flag = 0;
	int length = strlen(content);

	for (int i = 0; i < length / 2; i++)
	{
		if (content[i] == content[length - i - 1])
		{
			flag = 1;
		}
		else
		{
			flag = 0;
			break;
		}
	}

	if (flag == 1)
		printf("ȸ���Դϴ�.\n");
	else
		printf("ȸ���� �ƴմϴ�.\n");
	*/

#pragma endregion

	return 0;
}