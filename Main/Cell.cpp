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

Road::Road(int _x, int _y, string _name) : Cell(_x, _y, _name), item()
{
    next = nullptr;
} 

 Road* Road::Get_Next(void)
 {
    return next;
 }

void Road::Change_Next(Road* next_road)
{
    next = next_road;
}

Normal_Road::Normal_Road(int _x, int _y, string _name) : Road(_x, _y, _name) {}