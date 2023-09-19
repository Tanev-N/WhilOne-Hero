#ifndef CELL
#define CELL

#include "basic_library.h"
#include "Item.h"
#include "Controller.h"
#include "Creature.h"
#include "Event.h"

class Cell
{
    protected:
        string name; 
        Input_Controller input;
        Output_Controller out;
        int x, y;
        int GetX();
        int GetY();
    public:
        Cell(int, int, string);
        string Get_Name(void);
};


class Road : public Cell 
{ 
    protected:
        Item item;
        Road* *next;
    public:
        Road(int , int );
        Road* Get_Next();
        void Change_Next(Road*);
        virtual void Drop_item(Hero&) = 0;
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
        Event event[];
    public:
        Special_Road(int, int, string, Event[]);
        void PlayEvent(Hero&);
        void Drop_item(Hero&);
};

#endif