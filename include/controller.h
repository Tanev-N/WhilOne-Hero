#ifndef CONTROLLER
#define CONTROLLER


#include <iostream>
#include <string>

#include "cell.h"
#include "view_terminal.h"

using namespace std;

class Input_Controller
{
    private:

        Input_Terminal input_t;
    public:
        Input_Controller(void);
        char Trigger_In_Terminal(char);
};

class Output_Controller
{
    private:
        Output_Terminal out_t;
    public:
        Output_Controller(void);
        void Trigger_Draw_Start_Road_Terminal(Road*);
        void Trigger_Draw_Road_Terminal(Road*);
        void Trigger_Draw_Hero_Terminal(Road*, string);
        void Trigger_Write_Str_Terminal(string);
};

#endif
