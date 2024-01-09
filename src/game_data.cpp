#include "../include/game_data.h"

game_data::game_data() {
    MIN_LEN_ROAD = 25;
    MAX_LEN_ROAD = 45;
    SIZE_BOARDER = 20;
    ROW_COUNT = 5;
    MAX_HP = 100;
    names_of_game_settings = {"#MIN_LEN_ROAD", "#MAX_LEN_ROAD", "#SIZE_BOARDER", "#ROW_COUNT", "#MAX_HP"};
}


void game_data::Change_Max_Hp(int hp)
{
    MAX_HP = MAX_HP += hp;
}