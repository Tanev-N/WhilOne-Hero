#ifndef CREATURE
#define CREATURE

#include "item.h"
#include "game_data.h"

class Creature
{
    protected:
        int hp{};
    public:
        Creature();
        explicit Creature(int);
        void takeDamage(int);
        void Heal(int, const game_data&);
        int Get_Hp() const;
        void Set_hp(int);
};

class Hero : public Creature
{
    private:
        Boots bts;
        Armor arm;
    public:
        Hero();
        void ChangeBoots(Boots&);
        void ChangeArmor(Armor&);
        Boots& GetBoots();
        Armor& GetArmor();
        
};

#endif