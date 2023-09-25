#include "../Headers/all.h"

Input_Controller::Input_Controller(void) : input_t() {}









Output_Controller::Output_Controller(void) : out_t() {}

void Output_Controller::Trigger_Draw_Start_Road_Terminal(Road* Start)
{
    Road* Curr = Start;
    int direction = 0;

    do 
    {
        out_t.Draw_Road(Curr -> GetX(), (Curr -> GetY()) - direction , Curr -> Get_Name());
        direction += ( Curr -> GetY() ) - ((Curr->Get_Next())->GetY());
        Curr = Curr -> Get_Next();
    } while (Curr -> Get_Next() != Start);
    out_t.Draw_Road(Curr -> GetX(), Curr -> GetY() - direction, Curr -> Get_Name());
}


void Output_Controller::Trigger_Draw_Road_Terminal(Road* Cell)
{
    out_t.Draw_Road(Cell -> GetX(), Cell -> GetY(), Cell -> Get_Name());
}

void Output_Controller::Trigger_Draw_Hero_Terminal(Road* cell, string action)
{
    out_t.Draw_Hero(cell -> GetX(), cell -> GetY(), action, cell->Get_Name());
}



///