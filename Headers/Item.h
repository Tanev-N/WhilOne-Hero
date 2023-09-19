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
        Equipment(int, string);
        int Get_Durability(void);

};

class Armor : public Equipment
{
    private:
        int defense;
    public:
        Armor(int, int, string);
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