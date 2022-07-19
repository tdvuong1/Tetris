#pragma once

#include <iostream>
#include "console.h"
using namespace std;

#define B_hang 2
#define B_cot 3
class Brick
{
private:
	int matrix[B_hang][B_cot];
	int value;		// bằng 0 là ô gạch trống, != 0 có tồn tại viên gạch
public:
	Brick()
	{
		value = 0;
	}

	// get value
	int Value()
	{
		return value;
	}

	void setValue(int v)
	{
		value = v;
	}
	void Ve_gach(int tung_do, int hoanh_do, char c) // ham in ra mot vien gach
	{
		gotoXY(tung_do, hoanh_do);
		for (int i = 0; i < B_hang; i++)
		{
			for (int j = 0; j < B_cot; j++)
			{
				cout << c;
			}
			hoanh_do += 1;
			gotoXY(tung_do, hoanh_do);  /*in ra vien gach co dang ccc
																  ccc*/
		}
	}
};

