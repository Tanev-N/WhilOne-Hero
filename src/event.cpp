#include "../include/event.h"

Event::Event()
{
    good = "Default";
    bad = "Default";
    changer_hp = 0;
}
Event::Event(string _good, string _bad, int _ch)
{
    good = _good;
    bad = _bad;
    changer_hp = _ch;
}

string Event::get_good()
{
    return good;
}
string Event::get_bad()
{
    return bad;
}
int Event::get_changer()
{
    return changer_hp;
}
void Event::set_good(string _good)
{
    good = _good;
}
void Event::set_bad(string _bad)
{
    bad = _bad;
}
void Event::set_changer(int _chr)
{
    changer_hp = _chr;
}