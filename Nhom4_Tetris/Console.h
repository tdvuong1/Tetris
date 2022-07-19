#pragma once

#include <Windows.h>
#include <iostream>
enum
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	PURPLE,
	GRAY,
	WHITE,
	LIGHTGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTPURPLE,
	LIGHTYELLOW,
	LIGHTWHITE
};
void gotoXY(int x, int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void clrscr()
{
	COORD coord;
	DWORD written;
	CONSOLE_SCREEN_BUFFER_INFO info;

	coord.X = 0;
	coord.Y = 0;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ',
		info.dwSize.X * info.dwSize.Y, coord, &written);
	gotoXY(1, 1);
}

void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}


void Nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

// Hàm thay đổi kích cỡ của khung cmd.
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}