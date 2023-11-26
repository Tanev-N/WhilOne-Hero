#include "../include/creature.h"


Creature::Creature(int _hp): hp(_hp) {}
Creature::Creature() = default;

Hero::Hero() : bts(), arm() {} //TODO replace MAX_HP

void Creature::Set_hp(int _hp)
{
    hp = _hp;
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





Monster::Monster() : name("Empty")
{
    hp = 0;
    atk = 0;
    spd = 0;
    def = 0;
}
Monster::Monster(string _name, string _type, int _hp, int _atk, int _spd, int _def) : Creature(_hp),  name(_name), type(_type), atk(_atk), spd(_spd), def(_def) {}


int Monster::Get_Attack()
{
    return atk;
}

int Monster::Get_Speed()
{
    return spd;
}

int Monster::Get_Defense()
{
    return def;
}

string Monster::Get_Name()
{
    return name;
}

string Monster::Get_Type()
{
    return type;
}