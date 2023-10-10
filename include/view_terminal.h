#ifndef TERMINAL
#define TERMINAL

#include <iostream>
#include <string>

using namespace std;

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
        void Write_Str(string, int);
        void Draw_Hero(int , int , string, string);
        int Get_Colour_Code(string );
};

#endif