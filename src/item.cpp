#include "../include/item.h"



Item::Item() : type("Default") {}
Item::Item(string _type) : type(_type) {}

string Item::Get_Type()
{
    return type;
}

Equipment::Equipment(string _type , int _durab ) : Item(_type), durability(_durab) {}
Equipment::Equipment() : Item("Default"), durability(-1) {}

int Equipment::Get_Durability() const
{
    return durability;
}

Armor::Armor(string _type, int _durab = -1, int _def = 0) : Equipment(_type, _durab), defense(_def) {}
Armor::Armor() : Equipment("Default", -1), defense(0) {}

int Armor::Get_Defense() const
{
    return defense;
}

Boots::Boots(string _type , int _durab = -1, string _name = "Sandals") : Equipment(_type, _durab), name(_name){}
Boots::Boots() : Equipment("Default", -1), name("Sandals") {}

string Boots::Get_Name()
{
    return name;
}

int Item::get_weight()
{
    map<string, int> types_weight = {       {"common",  100},
                                            {"rare",   33},
                                            {"epic", 18},
                                            {"legendary",   8},
                                            {"unique",   4},
                                            {"holy",  2},


                                            {"evently", 15}
    };
    return  types_weight.find(type)->second;

}

void Equipment::reduce_durability()
{
    durability--;
}
