#ifndef CONTROLLER
#define CONTROLLER

class Road;


#include "cell.h"
#include "basic_library.h"
#include "view_Terminal.h"



class Input_Controller
{
    private:

        Input_Terminal input_t;
    public:
        Input_Controller(void);
        char Trigger_In_Terminal(char*);
};

class Output_Controller
{
    private:
        Output_Terminal out_t;
    public:
        Output_Controller(void);
        void Trigger_Draw_Start_Road_Terminal(Road*);
        void Trigger_Draw_Road_Terminal(Road*);
        void Trigger_Draw_Hero_Terminal(Road*, const string&);
        void Trigger_Write_Str_Terminal(string);
};

#endif
