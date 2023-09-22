#ifndef CREATURE
#define CREATURE

#include "basic_library.h"
#include "Item.h"

class Creature
{
    protected:
        int hp;
    public:
        Creature(int);
        void takeDamege(int);
        void Heal(int);
        int GetHp(void);
};

class Hero : public Creature
{
    private:
        Boots bts;
        Armor arm;
    public:
        Hero();
        Hero(Boots, Armor);
        void ChangeBoots(Boots&);
        void ChangeArmor(Armor&);
        Boots& GetBoots(void);
        Armor& GetArmor(void);
        
};

#endif