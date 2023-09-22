#ifndef ITEM
#define ITEM

#include "basic_library.h"
#include "Controller.h"

class Item
{
    protected:
        string type;
    public:
        Item(string);
        Item();
        string Get_Type(void);
};

class Equipment: public Item
{
    protected:
        int durability;
    public:
        Equipment(string, int);
        Equipment();
        int Get_Durability(void);

};

class Armor : public Equipment
{
    private:
        int defense;
    public:
        Armor(string , int, int);
        Armor();
        int Get_Defense(void);

};

class Boots : public Equipment
{
    private:
        string name;
    public:
        Boots(string , int ,  string);
        Boots();
        string Get_Name(void);

};

#endif