#include "Game.h"

int main()
{
	int mode, res;
	Game x;


	mode = x.Menu();

	if (mode == 2)		// quit
	{
		return 0;
	}

	if (mode == 1)			// new game
	{
		x.InputName();
	}
	x.Introduce();
	res = x.PlayGame(mode);
	x.EndGame(res);
	return 0;
}