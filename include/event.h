#ifndef EVENT
#define EVENT

#include <iostream>
#include <string>

using namespace std;

class Event
{
    private:
        string text;
        int changerHp;
    public:
        Event();
        Event(string, int);
        string Get_Text(void);
        int Get_Changer(void);
};

#endif