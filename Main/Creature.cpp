#include "../Headers/all.h"
//Creature::Creature(int _hp = 100) : hp(_hp) {}

Creature::Creature(int _hp): hp(_hp) {}
Hero::Hero() : Creature(HERO_HP), bts(), arm() {}