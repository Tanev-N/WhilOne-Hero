#ifndef TERMINAL
#define TERMINAL

#include <iostream>
#include <string>

using namespace std;

#include "game_data.h"

class Input_Terminal
{
    private:
        game_data settings;
    public:
        Input_Terminal();
        explicit Input_Terminal(game_data);
        char Get_Key();
};

class Output_Terminal
{
    private:
        game_data settings;
    public:
        Output_Terminal();
        explicit Output_Terminal(game_data);
        void Draw_Road(int, int, string);
        void Write_Str(string, int);
        void Draw_Hero(int , int , string, string);
        int Get_Colour_Code(string);
        
        
};

#endif