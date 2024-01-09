#include "../include/item.h"



Item::Item() : type("Default"), name("Ничего") {}
Item::Item(string _type, string _name) : type(_type), name(_name) {}

string Item::Get_Type()
{
    return type;
}

string Item::Get_Name()
{
    return name;
}

Equipment::Equipment(string _type , string _name, int _durab ) : Item(_type, _name), durability(_durab) {}
Equipment::Equipment() : Item("Default", "Ничего"), durability(-1) {}

int Equipment::Get_Durability() const
{
    return durability;
}

Armor::Armor(string _type, string _name, int _durab = -1, int _def = 0) : Equipment(_type, _name, _durab), defense(_def) {}
Armor::Armor() : Equipment("Default", "Майка", -1), defense(0) {}

int Armor::Get_Defense() const
{
    return defense;
}

Weapon::Weapon(string _type, string _name, int _durab = -1, int _atk = 0, int _spd = 0) : Equipment(_type, _name, _durab), attack(_atk), speed(_spd) {}
Weapon::Weapon() : Equipment("Default", "Кулаки", -1), attack(1), speed(6) {}

int Weapon::Get_Attack()
{
    return attack;
}

int Weapon::Get_Speed()
{
    return speed;
}

Boots::Boots(string _type , string _name, int _durab = -1) : Equipment(_type, _name, _durab) {}
Boots::Boots() : Equipment("Default", "Сандали", -1)  {}

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

