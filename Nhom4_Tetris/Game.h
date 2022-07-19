
#include <iostream>
#include "Console.h"
#include "Board.h"
#include "Block.h"
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <string>
#include <fstream>
using namespace std;

class Game
{
	Board	Board;
	Block* currBlock, * nextBlock;
public:
	int Menu()            // in ra man hinh dau
	{
		textcolor(14);

		int mode = 1;
		char c = 175;           // ky tu >>
		gotoXY(50, 20);
		cout << "NEW GAME";
		gotoXY(50, 22);
		cout << "QUIT";
		gotoXY(40, 30);
		cout << "Nhap W va S de di chuyen len xuong";
		gotoXY(47, 32);
		cout << "Enter de lua chon ";
		Nocursortype();

		while (1)
		{
			textcolor(LIGHTYELLOW);
			if (mode == 1)
			{
				gotoXY(45, 20);
				cout << c;
				gotoXY(45, 22);
				cout << ' ';
			}
			else if (mode == 2)
			{
				gotoXY(45, 20);
				cout << ' ';
				gotoXY(45, 22);
				cout << c;
			}
			char d;

			d = _getch();
			if ((d == 'W' || d == 'w') && mode > 1)        // nhan W hoac w thi kí tu >> se dich len 1 don vi
			{
				mode--;
			}
			else if ((d == 'S' || d == 's') && mode < 2)      // nhan S hoac s thi ki tu >> dich xuong 1 don vi 
			{
				mode++;
			}
			else if (d == 13) {    // nhan enter thì tra ve type
				return mode;
			}
		}
	}

	void InputName()         // nhap ten
	{
		string name;
		do
		{
			clrscr();
			char c = 175;
			textcolor(LIGHTYELLOW);
			gotoXY(50, 20);
			cout << "Your name : ";
			gotoXY(40, 22);
			cout << c;
			textcolor(LIGHTWHITE);
			gotoXY(44, 22);
			getline(cin, name);
		} while (name.size() == 0);
	}
	void Introduce()          // gioi thieu cac phim dieu khien game
	{
		clrscr();
		Board.Ve_bang();
		textcolor(LIGHTGREEN);
		int x = Le_phai + 9;
		int y = Le_tren + 12 * B_hang;

		gotoXY(x - 3, y - 4);
		cout << "Are you ready ?";
		Sleep(2000);
		gotoXY(x - 3, y - 4);
		cout << "!!!!! START !!!!!";
		Sleep(1000);

		x = Le_phai + 3;
		y = Le_tren + 11 * B_hang;

		textcolor(LIGHTGREEN);
		gotoXY(x, y);
		cout << "  A   : Move Left";
		gotoXY(x, y + 2);
		cout << "  S   : Move Down";
		gotoXY(x, y + 4);
		cout << "  D   : Move Right";
		gotoXY(x, y + 6);
		cout << "  W   : Rotate";
		gotoXY(x, y + 8);
		cout << "  R   : Restart";
		gotoXY(x, y + 10);
		cout << " Esc  : Quit";
	}
	int PlayGame(int mode)
	{


		int res;	             // kết quả cuối cùng
		clock_t Start, End;
		char c;

		srand(time(0));
		currBlock = new Block;
		nextBlock = new Block;

		currBlock->Random();
		nextBlock->Random();
		do
		{
			if (currBlock->GetOrdFb() >= 4) // con tro currBlock trỏ tới vị trí ham getOrdFb
			{
				currBlock->Ve_khoi();
			}
			Start = clock();
			do
			{
				if (_kbhit())
				{
					c = toupper(_getch());         // kiem tra phim nhap
					currBlock->xoa_khoi();
					switch (c)
					{
					case 'W':
						currBlock->xoay(Board);

						break;
					case 'A':
						currBlock->Dich_trai(Board);
						break;
					case 'D':
						currBlock->Dich_phai(Board);
						break;
					case 'S':
						currBlock->Dich_xuong(Board);
						break;
					case 'R':
						if (this->Bang_YesNo(Le_trai + 6, Le_tren + 5, " Restart ? "))    // goi bang restart
						{
							Board.xoa();
							Board.DisplayBoard();
							delete currBlock;
							currBlock = new Block;
							currBlock->Random();

						}
						else
						{
							this->Xoa_bang_YesNo(Le_trai + 6, Le_tren + 5);
						}
						break;
					case 27:  // Esc                                                          // goi bang quit game
						if (this->Bang_YesNo(Le_trai + 6, Le_tren + 5, "Quit game ? "))
						{
							this->Xoa_bang_YesNo(Le_trai + 6, Le_tren + 5);
							clrscr();
							return res = 0;
						}
						else
						{
							this->Xoa_bang_YesNo(Le_trai + 6, Le_tren + 5);
						}
						break;
					}
					currBlock->Ve_khoi();
				}
				End = clock();
			} while (float(End - Start) / CLOCKS_PER_SEC < 0.3);


			if (currBlock->Dich_xuong(Board) == false) //ko di chuyen xuong dc
			{
				currBlock->Gan_gia_tri_cho_bang(Board);
				Board.DisplayBoard();
				res = currBlock->CheckGame(Board);
				if (res == -1)
					break;
				delete currBlock;
				currBlock = nextBlock;
				nextBlock = new Block;
				nextBlock->Random();

			}
			else
			{
				currBlock->SetOrdFb(currBlock->GetOrdFb() - 1); // xoa bong cua khoi gach
				currBlock->xoa_khoi();
				currBlock->SetOrdFb(currBlock->GetOrdFb() + 1);   // ve lai khoi gach o vi tri tiep theo
				currBlock->Ve_khoi();
			}

		} while (1);
	}

	void EndGame(int res)
	{
		textcolor(LIGHTYELLOW);
		gotoXY(Le_phai + 9 - 3, Le_tren + 12 * B_hang + 3);
		if (res == -1)
		{
			clrscr();
			cout << "Game over !!!!!";
		}
		else if (res == 0)
			cout << "See you again !!!!";
		Sleep(1000);
	}
	int Bang_YesNo(int tung, int hoanh, string S)
	{

		textcolor(LIGHTWHITE);
		gotoXY(tung + 8, hoanh + 2);
		cout << S;
		for (int i = 0; i < 24; i++)
		{
			gotoXY(tung + i, hoanh);
			cout << 'x';
			gotoXY(tung + i, hoanh + 6);
			cout << 'x';
		}
		for (int i = 0; i <= 6; i++)
		{
			gotoXY(tung, hoanh + i);
			cout << 'x';
			gotoXY(tung + 24, hoanh + i);
			cout << 'x';
		}
		Nocursortype();
		int check = 1;
		char c;
		while (1)
		{
			if (_kbhit())
			{
				c = _getch();
				if (c == 13)
					return check;
			}
			if (check == 1)
			{
				textcolor(LIGHTYELLOW);
				gotoXY(tung + 6, hoanh + 4);
				cout << "YES";
				textcolor(LIGHTWHITE);
				gotoXY(tung + 16, hoanh + 4);
				cout << "NO";
			}
			else
			{
				textcolor(LIGHTWHITE);
				gotoXY(tung + 6, hoanh + 4);
				cout << "YES";
				textcolor(LIGHTYELLOW);
				gotoXY(tung + 16, hoanh + 4);
				cout << "NO";
			}

			if (GetAsyncKeyState(VK_RIGHT))
			{
				check = 0;
			}

			if (GetAsyncKeyState(VK_LEFT))
			{
				check = 1;
			}
		}

	}

	void Xoa_bang_YesNo(int abs, int ord)
	{
		for (int i = 0; i <= 6; i++)
		{
			for (int j = 0; j <= 24; j++)
			{
				gotoXY(abs + j, ord + i);
				cout << " ";
			}
		}
	}
};


