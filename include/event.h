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
        Event(string, string, int);
        string get_good();
        string get_bad();
        int get_changer();
        void set_good(string);
        void set_bad(string);
        void set_changer(int);
        int get_weight(string);
};

#endif