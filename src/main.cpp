#include "../include/game.h"

int main() {
    
    srand(time(nullptr));

    string level_1 = "../configs/level_1.txt";
    string level_2 = "../configs/level_2.txt";
    string level_3 = "../configs/level_3.txt";

    list<string> levels = {level_1, level_2, level_3};

    string player_name;
    cout << "Введите имя пользователя: ";
    cin >> player_name;

    int number_level = 1;

    fstream player_save;
    player_save.open("../saves/" + player_name + ".txt");
    if (!player_save.is_open())
    {
        for(auto &i : levels)
        {
            Game whileOne_level(i, number_level);
            if (whileOne_level.Play("../saves/" + player_name + ".txt", true) == 0)
            {
                break;
            }
            cout.clear();
            cout << "\033[2J\033[1;1H";
            number_level++;
        }
    }
    else
    {
        string word;
        int levels_complete;
        player_save >> word;
        levels_complete = stoi(word);

        auto p = levels.begin();
        for(int i = 1; i < levels_complete; i++)
        {
            p++;
        }
        player_save >> word;
        bool flag_new_player;
        if (word == "new")
        {
            flag_new_player = true;
        } else
        {
            flag_new_player = false;
        }
        for(auto i = levels_complete;  i < levels.size(); i++)
        {
            Game whileOne_level(*p, i);
            if (whileOne_level.Play("../saves/" + player_name + ".txt", flag_new_player) == 0)
            {

                whileOne_level.output_lose();
                return 1;
            }
            flag_new_player = true;
            cout << "\033[2J\033[1;1H";
            p++;
        }
    }
    player_save.close();


	return 0;
}