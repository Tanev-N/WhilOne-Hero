#ifndef GAME
#define GAME

#include "Cell.h"
#include "Creature.h"

class Game
{
    private:
        Hero hero;
        Road* head;
        Road* start;
    public:
        Game();
        void Play (void);
        int Make_Step();
        int Step_Check(int, int, int);
        void Create_Road(void);
        Road* Get_Head(void);
};



#endif