#ifndef CREATURE
#define CREATURE

#include "item.h"
#include "game_data.h"

class Creature
{
    protected:
        int hp;
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

class Monster : public Creature
{
private:
    string name;
    string type;
    int atk;
    int spd;
    int def;
public:
    Monster();
    Monster(string, string, int, int, int, int);
    string Get_Name();
    string Get_Type();
    int Get_Attack();
    int Get_Speed();
    int Get_Defense();
};


#endif