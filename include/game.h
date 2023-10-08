#ifndef GAME
#define GAME

#include "cell.h"
#include "creature.h"
#include "controller.h"


class Game
{
    private:
        Hero hero;
        Road* head;
        Road* start;
        Input_Controller input;
        Output_Controller output;
    public:
        Game();
        void Play();
        int Make_Step();
        int Step_Check(int, int, int);
        void Create_Path();
        Road* Get_Head();
        int Check_Plus(int, int, int, int);
        void Delete_Path();
        int Get_Size_Row();
        int Get_Size_Column();
        void Change_Screen_Size(int y, int x);
        int Screen_Size_Check();
};



#endif