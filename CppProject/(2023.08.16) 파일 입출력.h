#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

void ReadTextFile(const char* fileName)
{
	FILE* readFile = fopen(fileName, "r");

	char buffer[10000] = { 0, };

	// fread()
	// ù ��° �Ű����� : ũ�⸦ ������ �迭�� ����Ű�� �������Դϴ�.
	// �� ���� �Ű����� : �о���� ������ ũ���̸�, ������ ����Ʈ�Դϴ�.
	// �� ��° �Ű����� : �о���� ���ҵ��� ������ �� ������ ũ���Դϴ�.
	// �� ��° �Ű����� : �����͸� �Է¹��� ��Ʈ���� FILE ��ü�� ����Ű�� �������Դϴ�.
	fread(buffer, 1, 10000, readFile);
	printf("%s", buffer);

	fclose(readFile);
}

int main()
{
#pragma region ���� �����
	// ���� ��� ��ġ(��ũ)�� ���� �����͸�
	// �о���ų� �����ϴ� �����Դϴ�.

	// fopen("���� �̸�", "���� ���");
	// "w" : ���� ����
	// FILE* filePtr = fopen("data.txt", "w");
	// 
	// char content[] = "Content";
	// 
	// fputs(content, filePtr);
	// 
	// FILE* fileReader = fopen("data.txt", "r");
	// 
	// fgets(content, sizeof(content), fileReader);
	// printf("%s\n", content);
	// 
	// fclose(fileReader); // ���� �ݾ��ֱ�

#pragma endregion

	// ReadTextFile("Resources/dragon.txt");

	while (1)
	{
		ReadTextFile("Resources/data.txt");

		system("cls");
	}

	return 0;
}