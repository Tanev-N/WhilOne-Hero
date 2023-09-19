#include "../Headers/ALL.h"

Cell::Cell(int _x, int _y, string _name) : x(_x), y(_y), name(_name) {}   

int Cell::GetX()
{
    return x;
}
int Cell::GetY()
{
    return y;
}

Road::Road(int _x, int _y, string _name) : Cell(_x, _y, _name) 
{
    item = "None";
    next = NULL;
} 

