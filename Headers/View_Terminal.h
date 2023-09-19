#ifndef TERMINAL
#define TERMINAL

#include "basic_library.h"
#include "Controller.h"

class Input_Terminal
{
    public:
        Input_Terminal(void);
        char Get_Key(void);
};

class Output_Terminal
{
    public:
        Output_Terminal(void);
        void Draw_Road(int, int, string);
        void Write_Str(string);
};

#endif