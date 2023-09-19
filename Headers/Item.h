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
        string Get_Type(void);
};

class Equipment: public Item
{
    protected:
        int durability;
    public:
        Equipment(string, int);
        int Get_Durability(void);

};

class Armor : public Equipment
{
    private:
        int defense;
    public:
        Armor(string, int, int);
        int Get_Defense(void);

};

class Boots : public Equipment
{
    private:
        string name;
    public:
        Boots(int, string, string);
        string Get_Name(void);

};

#endif