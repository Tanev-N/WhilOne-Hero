#ifndef EVENT
#define EVENT

#include "basic_library.h"

class Event
{
    private:
        string text;
        int changerHp;
    public:
        Event(string, int);
        string GetText(void);
        int GetChanger(void);
};

#endif