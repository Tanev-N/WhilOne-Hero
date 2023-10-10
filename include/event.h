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
        int changerHp;
    public:
        Event();
        Event(string, string, int);
        string Get_Text(void);
        int Get_Changer(void);
};

#endif