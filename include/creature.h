#ifndef CREATURE
#define CREATURE

#include <fstream>
#include "item.h"
#include "game_data.h"

class Creature
{
protected:
    int hp;
    int exp;
    int atk;
    int att_delay;
    int def;
public:
    Creature();
    explicit Creature(int, int, int, int, int);
    void takeDamage(int);
    void Heal(int, const game_data&);
    int Get_Hp() const;
    int Get_Exp();
    int Get_Attack();
    int attack_delay();
    int Get_Defense();
    void Set_hp(int);
};


class Hero : public Creature
{
private:
    int level;
    Boots bts;
    Armor arm;
    Weapon weap;
public:
    Hero();
    void ChangeBoots(Boots&);
    void ChangeArmor(Armor&);
    void ChangeWeapon(Weapon&);
    Boots& GetBoots();
    Armor& GetArmor();
    Weapon& GetWeapon();
    int Get_level();
    void load_hero(ifstream*);
    void Level_Up(game_data&);
};

class Monster : public Creature
{
protected:
    string name;
    string type;
    string phrase;
public:
    Monster();
    Monster(string, string, string, int, int, int, int, int);
    string Get_Name() const;
    string Get_Type();
    string Get_Phrase();
};


#endif