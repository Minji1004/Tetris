#include "Controller.h"

int main(void)
{
	CreateBuffer();
	Boundary();
	Block block;
	bool isActive = true;
	int timecount = 0;
	while (isActive)
	{

		Input(block);
		Expression(block);
		GetBonus(block);
		block.Down();

		if (CheckGameOver())
			isActive = false;

		if (!block.BoundaryCheck())
		{
			block.Up();
			block.Occupied();
			block = Block();
		}

		Sleep(200);
		timecount++;
		if(timecount ==5)
		{ 
			timecount = 0;
			playtime++;
		}
	}	

	cout << "Game over" << endl;
	Release();
	while (1);
	return 0;
}