#ifndef __CONSOLE_DOUBLE_BUFFERING_H__
#define __CONSOLE_DOUBLE_BUFFERING_H__

#include <windows.h>

static int nBufferIndex;
static HANDLE hBuffer[2];

void CreateBuffer()
{
	CONSOLE_CURSOR_INFO cci;
	COORD size = { 80, 25 };
	SMALL_RECT rect;

	rect.Left = 0;
	rect.Right = 80 - 1;
	rect.Top = 0;
	rect.Bottom = 25 - 1;

	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(hBuffer[0], size);
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);
	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(hBuffer[1], size);
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);

	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hBuffer[0], &cci);
	SetConsoleCursorInfo(hBuffer[1], &cci);
}

void BufferWrite(int x, int y, const char *string)
{
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(hBuffer[nBufferIndex], CursorPosition);
	WriteFile(hBuffer[nBufferIndex], string, strlen(string), &dw, NULL);
}

void Flipping()
{
	Sleep(33);
	SetConsoleActiveScreenBuffer(hBuffer[nBufferIndex]);
	nBufferIndex = !nBufferIndex;
}

void BufferClear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(hBuffer[nBufferIndex], ' ', 80 * 25, Coor, &dw);
}

void Release()
{
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}

#endif