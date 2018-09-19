#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "Block.h"

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cstring>
#include "Console_DoubleBuffering.h"
//출력할 것을 string에 저장하기 위함.
#include <sstream>

using namespace std;


#define LEFT 75// 좌측방향키
#define RIGHT 77// 우측방향키
#define UP 72// 위쪽방향키
#define DOWN 80// 아래방향키
#define ROTATER 122//오른쪽 회전
#define ROTATEL 120//왼쪽 회전
#define SPACE 32//아래로 빠르게


int point = 0;
int playtime = 0;


//2차 배열 포인터형 주의!
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
	

	//string stream에 일단 출력할 걸 저장.
	ostringstream s;
	s << "\n\n\n\n\n";
	
	block.Occupied();
	for (int i = 0; i < HEIGHT; i++)
	{
		s<<"          ";
		for (int j = 0; j < WIDTH; j++)
		{
			if (tetris[i][j] == 1)
				s << "□";
			else
				s << ". ";
		}
		s << endl;
	}
	block.Unoccupied();
	s << "\n\n";
	s << "시간 : " << playtime << endl;
	s << "점수 : " << point << endl;

	//stringstream에 있는 걸 string으로 바꿈.
	string tetrisString = s.str();
	//string을 char*형으로 바꿔 줌
	const char* tetrisCharPtr = tetrisString.c_str();
	//더블 버퍼에 출력
	BufferWrite(0, 0, tetrisCharPtr);
	//버퍼 화면에 띄우고 버퍼 바꿈
	Flipping();
	//버퍼 깨끗하게
	BufferClear();
}

//방향키 입력
void Input(Block& block)
{
	//kbhit 키가 눌렸는지 안눌렸는지 확인해주는 함수. 안눌렸으면 0, 눌렸으면 1을 반환
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

//한줄다 모임
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
				//배열 복사 함수!
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
