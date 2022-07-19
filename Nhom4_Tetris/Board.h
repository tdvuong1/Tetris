#pragma once
#include "Brick.h"
#include "Console.h"
#include <fstream>
using namespace std;

#define Hang		    22
#define Cot		        11
#define Le_trai		    15
#define Le_phai     	49
#define Le_tren		    8
#define Le_duoi  		45

class Board
{
private:
	Brick Board[Hang][Cot]; // khung sẽ la ma tran 22x11
public:

	// ve khung
	void Ve_bang()
	{
		Nocursortype();
		textcolor(BLACK);

		// ve le trai va phai cua khung
		for (int i = Le_trai; i <= Le_phai; i++)
		{
			textcolor(11);
			gotoXY(i, Le_tren);
			cout << 'x';
			gotoXY(i, Le_duoi);
			cout << 'x';
		}
		// ve le tren va duoi cua khung
		for (int i = Le_tren; i <= Le_duoi; i++)
		{
			textcolor(11);
			gotoXY(Le_trai, i);
			std::cout << 'x';
			gotoXY(Le_phai, i);
			std::cout << 'x';
		}
	}
	// in ra những viên gạch
	void DisplayBoard()
	{
		int x = Le_trai + 1;

		for (int i = 4; i < Hang; i++)		// chỉ in ra từ hàng thứ 5 đến hang thứ 22 của bảng
		{
			for (int j = 0; j < Cot; j++)
			{
				if (Board[i][j].Value() != 0)
				{
					textcolor(14);
					Board[i][j].Ve_gach(x + j * B_cot, i * B_hang + 1, 35);
				}
				else
				{
					textcolor(BLACK);
					Board[i][j].Ve_gach(x + j * B_cot, i * B_hang + 1, ' ');
				}
			}
		}
	}
	// cap nhat lai bang khi co hang day gach
	void Update(int row)
	{
		for (int i = row; i > 0; i--)
		{
			for (int j = 0; j < Cot; j++)
			{
				Board[i][j].setValue(Board[i - 1][j].Value());
			}
		}
	}


	// xóa hết dữ liệu trong bảng
	void xoa()
	{
		for (int i = 0; i < Hang; i++)
		{
			for (int j = 0; j < Cot; j++)
			{
				Board[i][j].setValue(0);
			}
		}
	}
	// lấy giá trị viên gạch thứ [row][col] trong bảng
	int getValueBrick(int row, int col)
	{
		return Board[row][col].Value();
	}

	// gán value cho viên gạch thứ [row][col] trong bảng
	void setValueBrick(int row, int col, int value)
	{
		Board[row][col].setValue(value);
	}



};
