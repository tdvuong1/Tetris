#pragma once
#include "Brick.h"
#include "Board.h"
#include <vector>
#include <time.h>
using namespace std;

class Block {
private:

	vector<vector<Brick>> block;
	int rowBlock;			// số hàng khối gạch
	int colBlock;			// số cột khối gạch
	int Tung_do_dau;		// tung độ viên gạch đầu tiên
	int Hoanh_do_dau;		// hoành độ viên gạch đầu tiên

public:

	int GetAbsFb()
	{
		return Tung_do_dau;//trả về tung độ
	}
	void SetAbsFb(int x)
	{
		Tung_do_dau = x;//lấy giá trị tung độ
	}
	int GetOrdFb()
	{
		return Hoanh_do_dau;//trả về hoành độ
	}
	void SetOrdFb(int y)
	{
		Hoanh_do_dau = y;//lấy giá trị hoành độ
	}
	Block()
	{
		rowBlock = colBlock = 2;//mặt định block ban đầu là hình vuông
		Hoanh_do_dau = 0;//vị trí xuất phát ban đầu sẽ ở góc
		Tung_do_dau = 5;

		block.resize(rowBlock);//gán số hàng của block
		for (int i = 0; i < rowBlock; ++i)
			block.at(i).resize(colBlock);//gán số cột của block đối với tùng hàng

		block.at(0).at(0).setValue(6);//gán giá trị cho block mặt định là 6, mục đích khi truyền cho textcolor thì sẽ cho ra 1 màu và nó sẽ phân biệt giữa các block
		block.at(0).at(1).setValue(6);
		block.at(1).at(0).setValue(6);
		block.at(1).at(1).setValue(6);
	}
	~Block() {}
	void Random()
	{
		int type;
		srand(time(NULL));
		type = 1 + rand() % 4;
		switch (type)
		{
		case 4: // gạch chữ L, 4 hàng 1 cột
			rowBlock = 4;
			colBlock = 1;
			Hoanh_do_dau = 0;
			Tung_do_dau = 5;
			break;

		case 3: // gach hình vuông
			rowBlock = colBlock = 2;
			Hoanh_do_dau = 0;
			Tung_do_dau = 5;
			break;
		default:
			rowBlock = 2;
			colBlock = 3;
			Hoanh_do_dau = 0;
			Tung_do_dau = 5;
			break;
		}

		block.resize(rowBlock);//thay đổi lại kích thước hàng của block tùy thuộc vào các case ở trên
		for (int i = 0; i < rowBlock; ++i)
			block.at(i).resize(colBlock);//thay đổi lại kích thước cột của block tùy thuộc vào các case ở trên


		switch (type)
		{
		case 4://gach chữ I
		{
			block.at(0).at(0).setValue(type);
			block.at(1).at(0).setValue(type);
			block.at(2).at(0).setValue(type);
			block.at(3).at(0).setValue(type);
			break;
		}

		case 3:	// gạch hình vuông
		{
			block.at(0).at(0).setValue(type); // gán giá trị cho block mặt định là 6, mục đích khi truyền cho textcolor thì sẽ cho ra 1 màu và nó sẽ phân biệt giữa các block
			block.at(0).at(1).setValue(type);
			block.at(1).at(0).setValue(type);
			block.at(1).at(1).setValue(type);
			break;
		}

		case 2: // gạch chữ J
		{
			block.at(0).at(0).setValue(type);
			block.at(0).at(1).setValue(type);
			block.at(0).at(2).setValue(type);
			block.at(1).at(2).setValue(type);
			block.at(1).at(0).setValue(0);
			block.at(1).at(1).setValue(0);
			break;
		}
		case 1:	// gạch chữ L
		{
			block.at(0).at(0).setValue(type);
			block.at(0).at(1).setValue(type);
			block.at(0).at(2).setValue(type);
			block.at(1).at(0).setValue(type);
			block.at(1).at(1).setValue(0);
			block.at(1).at(2).setValue(0);
			break;
		}

		}

	}
	void Ve_khoi()
	{
		int x = Le_trai + 1 + Tung_do_dau * B_cot;
		int y = Hoanh_do_dau * B_hang + 1;
		for (int i = 0; i < rowBlock; i++)
		{
			for (int j = 0; j < colBlock; j++)
			{
				if (block.at(i).at(j).Value() != 0 && (Hoanh_do_dau + i) >= 4)//nếu đúng có giá trị và hoành độ >= thì gán màu cho chúng
				{
					textcolor(block.at(i).at(j).Value());
					block.at(i).at(j).Ve_gach(x + j * B_cot, y + i * B_hang, 35);//vẽ từng brick thành 1 block theo vị trí i, j
				}
			}
		}
	}
	void xoa_khoi()
	{
		int x = Le_trai + 1 + Tung_do_dau * B_cot;
		int y = Hoanh_do_dau * B_hang + 1;
		for (int i = 0; i < rowBlock; i++)
		{
			for (int j = 0; j < colBlock; j++)
			{
				if (block.at(i).at(j).Value() != 0 && (Hoanh_do_dau + i) >= 4)//nếu đúng có giá trị và hoành độ >= thì gán ký tự space
				{
					block.at(i).at(j).Ve_gach(x + j * B_cot, y + i * B_hang, ' ');
				}
			}
		}
	}
	bool Kiem_tra(int row, int col)     // kiem tra khoi co nam trong bang khong
	{
		return (row >= 0 && row < Hang&& col >= 0 && col < Cot);
	}

	bool Kiem_tra_trai(int row, int col, Board& board)
	{
		if (Kiem_tra(row, col) && col > 0 && board.getValueBrick(row, col - 1) == 0)//kiểm tra block có trong board hay không, nếu cột lớn hơn không mới có thể dịch sang trái, kiểm tra bên trái còn brick nào khác không
			return true;
		return false;
	}

	bool Kiem_tra_phai(int row, int col, Board& board)
	{
		if (Kiem_tra(row, col) && col < Cot - 1 && board.getValueBrick(row, col + 1) == 0)
			return true;
		return false;
	}
	bool Kiem_tra_duoi(int row, int col, Board& board)
	{
		if (Kiem_tra(row, col) && row < Hang - 1 && board.getValueBrick(row + 1, col) == 0)
			return true;
		return false;
	}

	bool Dich_trai(Board& board)
	{
		for (int i = 0; i < rowBlock; i++)
		{
			for (int j = 0; j < colBlock; j++)
			{
				if (block[i][j].Value() != 0)
				{
					if (Kiem_tra_trai(Hoanh_do_dau + i, Tung_do_dau + j, board) == false)
						return false;
				}
			}
		}
		Tung_do_dau -= 1;
		return true;
	}
	bool Dich_phai(Board& board)
	{
		for (int i = 0; i < rowBlock; i++)
		{
			for (int j = 0; j < colBlock; j++)
			{
				if (block[i][j].Value() != 0)
				{
					if (Kiem_tra_phai(Hoanh_do_dau + i, Tung_do_dau + j, board) == false)
						return false;
				}
			}
		}
		Tung_do_dau += 1;
		return true;
	}

	bool Dich_xuong(Board& board)
	{
		for (int i = 0; i < rowBlock; i++)
		{
			for (int j = 0; j < colBlock; j++)
			{
				if (block[i][j].Value() != 0)
				{
					if (Kiem_tra_duoi(Hoanh_do_dau + i, Tung_do_dau + j, board) == false)
						return false;
				}
			}
		}
		Hoanh_do_dau += 1;
		return true;
	}

	bool xoay(Board& board)
	{
		if (block.at(0).at(0).Value() == 6)		// gạch hình vuông khỏi xoay
			return false;
		int tempRow = colBlock;
		int tempCol = rowBlock;

		//Kiem tra co th xoay hay khong
		for (int i = 0; i < tempRow; i++)
		{
			for (int j = 0; j < tempCol; j++)
			{
				if (!Kiem_tra(Hoanh_do_dau + i, Tung_do_dau + j) ||
					board.getValueBrick(Hoanh_do_dau + i, Tung_do_dau + j) != 0)//kiểm tra nếu không nằm trong board hoặc có brick tại vị trí board đó là không xoay
					return false;
			}
		}

		// xoay được
		vector<vector<Brick>> temp(this->block); // sao chép dữ liệu hiện tại qua temp

		// cập nhật lại kích thước
		colBlock = tempCol;
		rowBlock = tempRow;
		block.resize(rowBlock);
		for (int i = 0; i < rowBlock; i++)
		{
			this->block.at(i).resize(colBlock);
		}

		//gán lại dữ liệu khi xoay
		for (int i = 0; i < colBlock; i++)
		{
			for (int j = 0; j < rowBlock; j++)
			{
				block[j][colBlock - 1 - i].setValue(temp[i][j].Value());
			}
		}
		return true;

	}
	// gán giá trị cho bảng khi không còn rơi xuông đưuọc nữa

	void Gan_gia_tri_cho_bang(Board& board)
	{
		for (int i = 0; i < rowBlock; i++)
		{
			for (int j = 0; j < colBlock; j++)
			{
				if (block[i][j].Value() != 0)
				{
					board.setValueBrick(Hoanh_do_dau + i, Tung_do_dau + j, block[i][j].Value());
				}
			}
		}
	}
	int CheckGame(Board& board)
	{
		int i, j, count;
		i = rowBlock - 1;// cho 1 biến chạy từ vị trí row lớn nhất lùi về 0

		if (Hoanh_do_dau < 4)
			return -1;	//Gameover

		int Full = 0;
		do
		{
			count = 0;
			for (j = 0; j < Cot; j++)
			{
				if (board.getValueBrick(Hoanh_do_dau + i, j) != 0)//kiểm tra giá trị brick của board có hay không
					count++;
			}

			if (count == Cot)
			{
				board.Update(Hoanh_do_dau + i);//nếu bằng số cột của board thì update
				Full++;
			}
			else
			{
				i = i - 1;//tiếp tục lùi
			}
		} while (i >= 0);
		if (Full >= 1)
		{
			Sleep(300);
			board.DisplayBoard();//in ra lại màn hình
		}
		return 2;	//continue
	}
};