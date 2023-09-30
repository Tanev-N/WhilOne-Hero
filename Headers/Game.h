#ifndef GAME
#define GAME

#include "cell.h"
#include "creature.h"

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
        
};



#endif