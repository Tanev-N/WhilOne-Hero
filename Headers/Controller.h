#ifndef CONTROLLER
#define CONTROLLER

#include "View_Terminal.h"
#include "basic_library.h"

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
        void Trigger_Draw_Road_Terminal(Road&);
        void Trigger_Write_Str_Terminal(string);
};

#endif
