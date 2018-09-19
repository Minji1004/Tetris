#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <cstdlib>
#include <ctime>

#define WIDTH 12
#define HEIGHT 24
#define centerY 1
#define centerX (WIDTH/2)-1

int tetris[HEIGHT][WIDTH];

namespace Blocks {
	enum blockName { Square = 0, L1 = 1, L2 = 2, T = 3, S1 = 4, S2 = 5, Stick = 6 };
}

typedef struct _point
{
	int x;
	int y;
}Point;

class Block
{
	Point ptr[4];
public:
	Block()
	{
		srand(time(NULL));
		int random = rand() % 7;

		switch (random)
		{
			//ptr[0]이 회전 중심
		case Blocks::Square:
			ptr[0] = { centerX, centerY + 1 };
			ptr[1] = { centerX, centerY };
			ptr[2] = { centerX + 1, centerY };
			ptr[3] = { centerX + 1, centerY + 1 };
			break;
		case Blocks::L1:
			ptr[0] = { centerX, centerY + 1 };
			ptr[1] = { centerX, centerY };
			ptr[2] = { centerX - 1, centerY + 1 };
			ptr[3] = { centerX - 2, centerY + 1 };
			break;
		case Blocks::L2:
			ptr[0] = { centerX, centerY + 1 };
			ptr[1] = { centerX, centerY };
			ptr[2] = { centerX + 1, centerY + 1 };
			ptr[3] = { centerX + 2, centerY + 1 };
			break;
		case Blocks::T:
			ptr[0] = { centerX, centerY + 1 };
			ptr[1] = { centerX, centerY };
			ptr[2] = { centerX - 1, centerY + 1 };
			ptr[3] = { centerX + 1, centerY + 1 };
			break;
		case Blocks::S1:
			ptr[0] = { centerX, centerY };
			ptr[1] = { centerX - 1, centerY };
			ptr[2] = { centerX, centerY + 1 };
			ptr[3] = { centerX + 1, centerY + 1 };
			break;
		case Blocks::S2:
			ptr[0] = { centerX, centerY };
			ptr[1] = { centerX + 1, centerY };
			ptr[2] = { centerX, centerY + 1 };
			ptr[3] = { centerX - 1, centerY + 1 };
			break;
		case Blocks::Stick:
			ptr[0] = { centerX, centerY + 1 };
			ptr[1] = { centerX, centerY };
			ptr[2] = { centerX, centerY + 2 };
			ptr[3] = { centerX, centerY + 3 };
			break;
		}

	}
	void Occupied()
	{
		for (int i = 0; i < 4; i++)
			tetris[ptr[i].y][ptr[i].x] = 1;
	}
	void Unoccupied()
	{
		for (int i = 0; i < 4; i++)
			tetris[ptr[i].y][ptr[i].x] = 0;
	}
	void Up()
	{
		for (int i = 0; i < 4; i++)
			ptr[i].y -= 1;
	}
	void Down()
	{
		for (int i = 0; i < 4; i++)
			ptr[i].y += 1;
	}
	void Left()
	{
		for (int i = 0; i < 4; i++)
			ptr[i].x -= 1;
	}
	void Right()
	{
		for (int i = 0; i < 4; i++)
			ptr[i].x += 1;
	}
	void RotateR()
	{
		for (int i = 1; i < 4; i++)
		{
			ptr[i].x -= ptr[0].x;
			ptr[i].y -= ptr[0].y;
			int temp = ptr[i].x;
			ptr[i].x = -1 * ptr[i].y;
			ptr[i].y = temp;
			ptr[i].x += ptr[0].x;
			ptr[i].y += ptr[0].y;
		}

	}
	void RotateL()
	{
		for (int i = 1; i < 4; i++)
		{
			ptr[i].x -= ptr[0].x;
			ptr[i].y -= ptr[0].y;
			int temp = ptr[i].x;
			ptr[i].x = ptr[i].y;
			ptr[i].y = -1 * temp;
			ptr[i].x += ptr[0].x;
			ptr[i].y += ptr[0].y;
		}

	}
	bool BoundaryCheck()
	{
		for (int i = 0; i < 4; i++)
			if (tetris[ptr[i].y][ptr[i].x] == 1)
				return false;

		return true;
	}

};

#endif