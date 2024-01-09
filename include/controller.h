#ifndef CONTROLLER
#define CONTROLLER

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include <thread>


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
        explicit Input_Controller(const game_data&);
        int In_Terminal();
        void set_settings(const game_data&);
};

class Output_Controller
{
    private:
        Output_Terminal out_t;
        game_data settings;
    public:
        Output_Controller();
        explicit Output_Controller(const game_data&);
        void Draw_Path_Terminal(list<Road>::const_iterator, list<Road>::const_iterator);
        void Undraw_Path_Terminal(list<Road>::const_iterator, list<Road>::const_iterator);
        void Draw_Hero_Terminal(list<Road>&, list<Road>::const_iterator, string);
        void Write_Str_Terminal(string);
        void set_settings(const game_data&);
        void Draw_Monster_Terminal(list<Road>::const_iterator, int );
        void Draw_Entity_Terminal(list<Road>::const_iterator, int);
        void clear_controller();
        void Clear_Cell_Terminal(int, int);
        void Colour_Entity_Terminal(int, int, string, string);
        void Draw_Monsters_Terminal(list<Road>::const_iterator, list<Road>::const_iterator);
};

#endif
