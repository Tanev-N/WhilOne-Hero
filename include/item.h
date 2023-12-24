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
    public:
        explicit Item(string);
        Item();
        string Get_Type();
        int get_weight();
};

class Equipment: public Item
{
    protected:
        int durability;
    public:
        Equipment(string, int);
        Equipment();
        int Get_Durability() const;
        void reduce_durability();

};

class Armor : public Equipment
{
    private:
        int defense;
    public:
        Armor(string , int, int); 
        Armor();
        int Get_Defense() const;

};

class Boots : public Equipment
{
    private:
        string name;
    public:
        Boots(string , int ,  string);
        Boots();
        string Get_Name();

};

#endif