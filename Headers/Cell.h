#ifndef CELL
#define CELL

#include "basic_library.h"
#include "controller.h"
#include "item.h"
#include "creature.h"
#include "event.h"

class Cell
{
    protected:
        string name; 
        int x, y;
    public:    
        Cell(int, int, string);
        int GetX();
        int GetY();
        string Get_Name(void);
};


class Road : public Cell 
{ 
    protected:
        Item item;
        Road* next;
    public:
        Road(int , int , string);
        void Change_Next(Road*);
        Road* Get_Next(void);
};

class Normal_Road : public Road
{
        public:
            Normal_Road(int, int, string);
            void ChangeToSpc();
            void Drop_item(Hero&);
};

class Special_Road : public Road
{
    protected:
        Event event;
    public:
        Special_Road(int, int, string, Event[]);
        void PlayEvent(Hero&);
        void Drop_item(Hero&);
};

#endif