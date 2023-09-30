#include <utility>

#include "../Headers/all.h"

Cell::Cell(int _x, int _y, string _name) : x(_x), y(_y), name(std::move(_name)) {}

int Cell::GetX() const
{
    return x;
}
int Cell::GetY() const
{
    return y;
}
string Cell::Get_Name()
{
    return name;
}
Road::Road(int _x, int _y, string _name) : Cell(_x, _y, std::move(_name)), item()
{
    next = nullptr;
}

 Road* Road::Get_Next()
 {
    return next;
 }

void Road::Change_Next(Road* next_road)
{
    next = next_road;
}
