#ifndef EVENT
#define EVENT

#include <iostream>
#include <string>

using namespace std;

class Event
{
    private:
        string good;
        string bad;
        int changer_hp;
    public:
        Event();
        Event(const string&, const string&, int);
        string get_good() const;
        string get_bad() const;
        int get_changer() const;
};

#endif