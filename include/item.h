#ifndef ITEM
#define ITEM

#include <iostream>
#include <string>
#include <map>

using namespace std;

class Item
{
    protected:
        string type;
        string name;
    public:
        Item(string, string);
        Item();
        string Get_Type();
        int get_weight();
        string Get_Name();
};

class Equipment: public Item
{
    protected:
        int durability;
    public:
        Equipment(string, string, int);
        Equipment();
        int Get_Durability() const;
        void reduce_durability();

};

class Armor : public Equipment
{
    private:
        int defense;
    public:
        Armor(string, string, int, int);
        Armor();
        int Get_Defense() const;

};

class Boots : public Equipment
{
    public:
        Boots(string, string, int);
        Boots();

};

class Weapon : public Equipment
{
    private:
        int attack;
        int speed;
    public:
        Weapon(string, string, int, int, int);
        Weapon();
        int Get_Attack();
        int Get_Speed();
};


#endif