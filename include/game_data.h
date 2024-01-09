#ifndef DATE3
#define DATE3

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class game_data
{
    public:
        int MIN_LEN_ROAD;
        int MAX_LEN_ROAD;
        int SIZE_BOARDER;
        int ROW_COUNT;
        int MAX_HP;
        vector<string> names_of_game_settings;
        game_data();
        void Change_Max_Hp(int);
};


#endif