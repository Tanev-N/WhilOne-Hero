#include "../include/creature.h"


Creature::Creature(int _hp, int _exp, int _atk, int _spd, int _def): hp(_hp), exp(_exp), atk(_atk), spd(_spd), def(_def) {}
Creature::Creature() = default;

Hero::Hero() : bts(), arm(), weap() {atk = 1; spd = 1; def = 1; level = 1;} //TODO replace MAX_HP

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

void Hero::load_hero(ifstream *file) {

    string word;

    (*file) >> word; // #Level
    (*file) >> word;  // {
    (*file) >> word; // hero.level
    level = stoi(word);
    (*file) >> word; // }

    (*file) >> word; // #Exp
    (*file) >> word;  // {
    (*file) >> word; // hero.exp
    exp = stoi(word);
    (*file) >> word; // }

    (*file) >> word; // #Hp
    (*file) >> word;  // {
    (*file) >> word; // hero.hp
    hp = (stoi(word));
    (*file) >> word; // }

    (*file) >> word; // #Speed
    (*file) >> word;  // {
    (*file) >> word; // speed
    spd = stoi(word);
    (*file) >> word; // }

    (*file) >> word; // #Attack
    (*file) >> word;  // {
    (*file) >> word; // speed
    atk = stoi(word);
    (*file) >> word; // }



    (*file) >> word; // #Boots
    (*file) >> word; // {
    (*file) >> word; // type
    string  type = word;
    (*file) >> word; // durab
    int durab = stoi(word);
    (*file) >> word;// name
    string name = word;
    Boots bts(type, name, durab);
    ChangeBoots(bts);
    (*file) >> word; // }

    (*file) >> word; // #Chestplate
    (*file) >> word; // {
    (*file) >> name; // name
    (*file) >> word; // defense
    int defense = stoi(word);
    (*file) >> word; // durab
    durab = stoi(word);
    (*file) >> word; // type
    type = word;
    Armor arm(type, name, durab, defense);
    ChangeArmor(arm);
    (*file) >> word; // }


    (*file) >> word; // #Weapons = rarity + name + durability + attack + speed
    (*file) >> word; // {
    (*file) >> word; // type
    string  type_ = word;
    (*file) >> word; // name
    name = word;
    (*file) >> word; // durab
    durab = stoi(word);
    (*file) >> word;// attack
    int attack = stoi(word);
    (*file) >> word;// speed
    int speed = stoi(word);
    Weapon weap(type_, name, durab, attack, speed);
    ChangeWeapon(weap);
    (*file) >> word; // }



}


int Creature::Get_Exp()
{
    return exp;
}

int Creature::Get_Attack()
{
    return atk;
}

int Creature::Get_Speed()
{
    return spd;
}

int Creature::Get_Defense()
{
    return def;
}



void Hero::ChangeBoots(Boots &_bts)
{
    bts = _bts;
}

void Hero::ChangeArmor(Armor &_arm)
{
    arm = _arm;
}

void Hero::ChangeWeapon(Weapon &_weap)
{
    weap = _weap;
}

Boots& Hero::GetBoots()
{
    return bts;
}

Armor& Hero::GetArmor()
{
    return arm;
}

Weapon& Hero::GetWeapon()
{
    return weap;
}

int Hero::Get_level() {
    return level;
}

void Hero::Level_Up(game_data& set)
{
    set.Change_Max_Hp(level*10);
    hp = set.MAX_HP;
    exp = 0;
    atk += 1;
    spd += 1;
    level += 1;
}


Monster::Monster() : name("Empty")
{
    hp = 0;
    atk = 0;
    spd = 0;
    def = 0;
}
Monster::Monster(string _name, string _type, string _phrase, int _hp, int _exp, int _atk, int _spd, int _def) : Creature(_hp, _exp, _atk, _spd, _def), name(_name), type(_type), phrase(_phrase)  {}

string Monster::Get_Phrase()
{
    return phrase;
}



string Monster::Get_Name() const
{
    return name;
}

string Monster::Get_Type()
{
    return type;
}