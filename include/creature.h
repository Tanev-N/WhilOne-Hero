#ifndef CREATURE
#define CREATURE

#include "item.h"


class Creature
{
    protected:
        int hp;
    public:
        Creature(int);
        void takeDamege(int);
        void Heal(int);
        int Get_Hp(void);
        void Set_hp(int);
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