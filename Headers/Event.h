#ifndef EVENT
#define EVENT

#include "basic_library.h"

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