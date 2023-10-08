#include <iostream>
#include <string>
#include <vector>

#include "controller.h"
#include "setting.h"

using namespace std;

Input_Controller::Input_Controller() : input_t() {}

Output_Controller::Output_Controller() : out_t() {}

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


template<typename T>
void pop_front(vector<T>& v)
{
    if (v.size() > 0) {
        v.erase(v.begin());
    }
}


void Output_Controller::Trigger_Write_Str_Terminal(string new_line)
{
    static vector<string> game_text;
    if (game_text.empty())
    {
        string none = "                                        ";
        for (int i = 0; i < ROW_COUNT; i++)
        {
            game_text.push_back(none);
        }
    }
    game_text.push_back(new_line);
    for (int i = ROW_COUNT-1; i >= 0 ; i--)
    {
        out_t.Write_Str(game_text[i], SIZE_BOARDER + 3 + i );
    }
    pop_front(game_text);
}





void Output_Controller::Trigger_Draw_Road_Terminal(Road* Cell)
{
    out_t.Draw_Road(Cell -> GetX(), Cell -> GetY(), Cell -> Get_Name());
}

void Output_Controller::Trigger_Draw_Hero_Terminal(Road* cell, const string& action)
{
    static int direction = 0;
    if (action == "Go")
    {
        out_t.Draw_Hero(cell->GetX(), (cell->GetY()) - direction, action, cell->Get_Name());
    }
    else
    {
        out_t.Draw_Hero(cell->GetX(), (cell->GetY()) - direction, action, cell->Get_Name());
        direction += (cell->GetY()) - ((cell->Get_Next())->GetY());
    }
    
}



///