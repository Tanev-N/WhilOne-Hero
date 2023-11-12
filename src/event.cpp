#include "../include/event.h"

Event::Event()
{
    good = "Default";
    bad = "Default";
    changer_hp = 0;
}
Event::Event(const string& _good, const string& _bad, int _ch)
{
    good = _good;
    bad = _bad;
    changer_hp = _ch;
}

string Event::get_good() const
{
    return good;
}
string Event::get_bad() const
{
    return bad;
}
int Event::get_changer() const
{
    return changer_hp;
}
void Event::set_good(const string& _good)
{
    good = _good;
}
void Event::set_bad(const string& _bad)
{
    bad = _bad;
}
void Event::set_changer(int _chr)
{
    changer_hp = _chr;
}