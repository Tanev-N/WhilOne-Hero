#ifndef CELL
#define CELL

using namespace std;

#include <iostream>
#include <string>
#include "creature.h"
#include "event.h"

class Cell
{
    protected:
        string name; 
        int x, y;
    public:    
        Cell(int, int, string);
        int GetX() const;
        int GetY() const;
        string Get_Name(void);
};


class Road : public Cell 
{ 
    protected:
        Item item;
        Road* next;
        Event event;
    public:
        Road(int , int , string);
        void Change_Next(Road*);
        Road* Get_Next(void);
        void ChangeToSpc();
        void Drop_item(Hero&);
        void PlayEvent(Hero&);
};

#endif