#ifndef GAME
#define GAME

#include "Cell.h"
#include "Creature.h"

class Game
{
    private:
        Hero hero;
        Road* head;
    public:
        Game(Hero, Road*);
        void Play (void);
        int Make_Step(int);
        int Step_Check(int, int, Road*);
        Road* Create_Road(void);
        Road* GetHead(void);
};



#endif