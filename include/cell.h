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
        void set_name(string);
        string Get_Name(void);
};


class Road : public Cell 
{ 
    protected:
        Boots boots; // Vector<Item*> items
        Road* next;
        Event event;
    public:
        Road(int , int , string); 
        Road() : Cell() { next = nullptr ;}
        void Change_Next(Road*);
        Road* Get_Next(void);
        void ChangeToSpc(vector<Road*>);
        Boots Get_Boots();
        void Play_Event(Hero*, Output_Controller, game_data);
        void set_boots(Boots);
        void set_event(Event);
        int get_weight(string);
        Event get_event();
};

#endif