#include "../include/game.h"

int main()
{
	srand(time(nullptr));
    string level_1 = "../configs/level_1.txt";
    string level_2 = "../configs/level_2.txt";
    string level_3 = "../configs/level_3.txt";
    string player_name;
    cout << "Введите имя пользователя: ";
    cin >> player_name;
    string word;
    int levels_complete;
    fstream player_save("../saves/" + player_name + ".txt");
    //player_save >> word;
    //levels_complete = stoi(word);

	Game whileOne_level_1(level_1);
    whileOne_level_1.Play();

    Game whileOne_level_2(level_2);
    whileOne_level_2.Play();

    Game whileOne_level_3(level_3);
    whileOne_level_3.Play();

	return 0;
}