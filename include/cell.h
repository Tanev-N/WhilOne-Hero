#ifndef CELL
#define CELL


#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "controller.h"
#include "creature.h"
#include "event.h"
#include "item.h"
#include "game_data.h"

class  Output_Controller;
using namespace std;

class Cell
{
    protected:
        string name; 
        int x, y;
    public: 
        Cell();   
        Cell(int, int, string);
        int GetX() const;
        int GetY() const;
        void set_x(int);
        void set_y(int);
        void set_name(const string&);
        string Get_Name() const;
};


class Road : public Cell 
{ 
    protected:
        Boots boots; 
        Event event;
        vector<Monster> monsters;
        Monster enemy;
    public:
        Road(int , int , const string&);
        Road() : Cell() {}
        void ChangeToSpc(vector<Road*>);
        Boots Get_Boots() const;
        vector<Monster> Get_Monsters();
        Monster Get_Monster() const;
        void Play_Event(Hero*, Output_Controller, const game_data&);
        void set_boots(const Boots&);
        void set_event(const Event&);
        void set_monster(Monster);
        void set_monsters(vector<Monster>);
        Event get_event() const;
};

#endif