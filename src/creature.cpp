#include "../include/creature.h"


Creature::Creature(int _hp): hp(_hp) {}
Creature::Creature() = default;

Hero::Hero() : bts(), arm() {} //TODO replace MAX_HP

void Creature::Set_hp(int _hp)
{
    hp = _hp;
}


void Hero::ChangeBoots(Boots &_bts)
{
    bts = _bts;
}

void Hero::ChangeArmor(Armor &_arm)
{
    arm = _arm;
}

Boots& Hero::GetBoots()
{
    return bts;
}

Armor& Hero::GetArmor()
{
    return arm;
}


void Creature::takeDamage(int dam)
{
    hp -= dam;
}
void Creature::Heal(int heal, const game_data& set)
{
    if(hp+heal > set.MAX_HP)
    {
        hp = set.MAX_HP;
    }
    else
    {
        hp+=heal;
    }
}

int Creature::Get_Hp() const
{
    return hp;
}