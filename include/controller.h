#ifndef CONTROLLER
#define CONTROLLER

#include <iostream>
#include <string>
#include <vector>

#include "cell.h"
#include "view_terminal.h"
#include "game_data.h"
class Road;
using namespace std;

class Input_Controller
{
    private:
        Input_Terminal input_t;
        game_data settings;
    public:
        Input_Controller();
        Input_Controller(game_data);
        char Trigger_In_Terminal();
        void set_settings(game_data);
};

class Output_Controller
{
    private:
        Output_Terminal out_t;
        game_data settings;
    public:
        Output_Controller();
        Output_Controller(game_data);
        void Trigger_Draw_Start_Road_Terminal(Road*);
        void Trigger_Draw_Road_Terminal(Road*);
        void Trigger_Draw_Hero_Terminal(Road*, string);
        void Trigger_Write_Str_Terminal(string);
        void set_settings(game_data);
};

#endif
