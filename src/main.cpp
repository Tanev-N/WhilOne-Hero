#include "../include/game.h"

int main()
{
	srand(time(nullptr));
	string level_1 = "../configs/level_1.txt";
	Game whileOne(level_1);
	whileOne.Play();

	return 0;
}