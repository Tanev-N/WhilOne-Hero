#ifndef TERMINAL
#define TERMINAL

#include <iostream>
#include <string>
#include <map>
#include <fcntl.h>
#include <termios.h>

using namespace std;

#include "game_data.h"

class Input_Terminal
{
    private:
        game_data settings;
        struct termios old_console_;
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
        void Clear_Road(int, int);
        void Write_Str(string, int);
        void Draw_Hero(int , int , string, string);
        int Get_Colour_Code(const string&);
        void Draw_Entity(int , int , const string&, const string& );
        const char* Get_Entity_Icon(const string&);
};

#endif