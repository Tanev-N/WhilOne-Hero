#include "../Headers/all.h"

Item::Item() : type("Started") {}
Item::Item(string _type) : type(_type) {}

string Item::Get_Type(void)
{
    return type;
}

Equipment::Equipment(string _type = "Started", int _durab = -1) : Item(_type), durability(_durab) {}
Equipment::Equipment() : Item("Started"), durability(-1) {}

int Equipment::Get_Durability(void)
{
    return durability;
}

Armor::Armor(string _type = "Started", int _durab = -1, int _def = 0) : Equipment(_type, _durab), defense(_def) {}
Armor::Armor() : Equipment("Started", -1), defense(0) {}

int Armor::Get_Defense(void)
{
    return defense;
}

Boots::Boots(string _type = "Started", int _durab = -1, string _name = "None") : Equipment(_type, _durab), name(_name){}
Boots::Boots() : Equipment("Started", -1), name("None") {}

string Boots::Get_Name(void)
{
    return name;
}
