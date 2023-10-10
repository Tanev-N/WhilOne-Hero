#include "creature.h"


Creature::Creature(int _hp): hp(_hp) {}

Hero::Hero() : Creature(100), bts(), arm() {} //TODO replace MAX_HP

void Creature::Set_hp(int _hp)
{
    hp = _hp;
}


void Hero::ChangeBoots(Boots& _bts)
{
    bts = _bts;
}

void Hero::ChangeArmor(Armor& _arm)
{
    arm = _arm;
}

Boots& Hero::GetBoots(void)
{
    return bts;
}

Armor& Hero::GetArmor(void)
{
    return arm;
}