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
        //Input_Controller input;  ADD default constructor 
        //Output_Controller out;   ADD default constructor 
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
        //virtual void Drop_item(Hero&) {};
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