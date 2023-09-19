#include "../Headers/ALL.h"


Item::Item(string _type) : type(_type) {}

string Item::Get_Type(void)
{
    return type;
}

Equipment::Equipment(string _type, int _durab) : Item(_type), durability(_durab) {}

int Equipment::Get_Durability(void)
{
    return durability;
}

Armor::Armor(string, int, int) : 