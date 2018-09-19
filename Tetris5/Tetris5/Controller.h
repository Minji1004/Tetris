#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "Block.h"

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cstring>
#include "Console_DoubleBuffering.h"
//����� ���� string�� �����ϱ� ����.
#include <sstream>

using namespace std;


#define LEFT 75// ��������Ű
#define RIGHT 77// ��������Ű
#define UP 72// ���ʹ���Ű
#define DOWN 80// �Ʒ�����Ű
#define ROTATER 122//������ ȸ��
#define ROTATEL 120//���� ȸ��
#define SPACE 32//�Ʒ��� ������


int point = 0;
int playtime = 0;


//2�� �迭 �������� ����!
void Boundary()
{
	for (int i = 0; i < WIDTH; i++)
	{
		tetris[0][i] = tetris[HEIGHT - 1][i] = 1;
	}
	for (int j = 1; j < HEIGHT - 1; j++)
	{
		tetris[j][0] = tetris[j][WIDTH - 1] = 1;
	}
}



void Expression(Block& block)
{
	

	//string stream�� �ϴ� ����� �� ����.
	ostringstream s;
	s << "\n\n\n\n\n";
	
	block.Occupied();
	for (int i = 0; i < HEIGHT; i++)
	{
		s<<"          ";
		for (int j = 0; j < WIDTH; j++)
		{
			if (tetris[i][j] == 1)
				s << "��";
			else
				s << ". ";
		}
		s << endl;
	}
	block.Unoccupied();
	s << "\n\n";
	s << "�ð� : " << playtime << endl;
	s << "���� : " << point << endl;

	//stringstream�� �ִ� �� string���� �ٲ�.
	string tetrisString = s.str();
	//string�� char*������ �ٲ� ��
	const char* tetrisCharPtr = tetrisString.c_str();
	//���� ���ۿ� ���
	BufferWrite(0, 0, tetrisCharPtr);
	//���� ȭ�鿡 ���� ���� �ٲ�
	Flipping();
	//���� �����ϰ�
	BufferClear();
}

//����Ű �Է�
void Input(Block& block)
{
	//kbhit Ű�� ���ȴ��� �ȴ��ȴ��� Ȯ�����ִ� �Լ�. �ȴ������� 0, �������� 1�� ��ȯ
	while (_kbhit() != 0)
	{
		int getkey = _getch();
		switch (getkey)
		{
		case LEFT:
			block.Left();
			if (!block.BoundaryCheck())
				block.Right();
			Expression(block);
			break;
		case RIGHT:
			block.Right();
			if (!block.BoundaryCheck())
				block.Left();
			Expression(block);
			break;
		case DOWN:
			block.Down();
			if (!block.BoundaryCheck())
				block.Up();
			Expression(block);
			break;
		case SPACE:
			while (1)
			{
				block.Down();
				if (!block.BoundaryCheck())
				{
					block.Up();
					break;
				}
			}
			Expression(block);
			break;
		case ROTATER:
			block.RotateR();
			if (!block.BoundaryCheck())
				block.RotateL();
			Expression(block);
			break;
		case ROTATEL:
			block.RotateL();
			if (!block.BoundaryCheck())
				block.RotateR();
			Expression(block);
			break;
		default:
			break;
		}
	}
	return;
}

//���ٴ� ����
void GetBonus(Block& block)
{
	for (int i = 1; i < HEIGHT - 1; i++)
	{
		int count = 0;
		for (int j = 1; j < WIDTH - 1; j++)
		{
			if (tetris[i][j] != 1)
				break;
			count++;
		}

		if (count == WIDTH - 2)
		{
			point += 100;
			for (int j = 1; j < WIDTH - 1; j++)
				tetris[i][j] = 0;
			for (int h = i; h > 1; h--)
			{
				//�迭 ���� �Լ�!
				memcpy(tetris[h], tetris[h - 1], sizeof(tetris[i]));
			}
			for (int j = 1; j < WIDTH - 1; j++)
				tetris[1][j] = 0;
			Expression(block);
		}
	}
	return;
}

bool CheckGameOver()
{
	for (int i = 1; i < WIDTH - 1; i++)
		if (tetris[1][i] == 1)
			return true;
	return false;
}
#endif // !__CONTROLLER_H__
