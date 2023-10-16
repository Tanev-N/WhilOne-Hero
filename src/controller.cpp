
#include "../include/controller.h"



void Input_Controller::set_settings(game_data _settings)
{
    settings = _settings;
}

void Output_Controller::set_settings(game_data _settings)
{
    settings = _settings;
}

Input_Controller::Input_Controller() : input_t(){}

Output_Controller::Output_Controller() : out_t(){}

Input_Controller::Input_Controller(game_data _settings) : input_t(_settings)
{
    settings = _settings;
}

Output_Controller::Output_Controller(game_data _settings) : out_t(_settings)
{
    settings = _settings;
}

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
        string empty_str = " ";
        for (int i = 0; i < settings.ROW_COUNT; i++)
        {
            game_text.push_back(empty_str);
        }
    }

    game_text.push_back(new_line);

    for (int i = settings.ROW_COUNT; i >= 0 ; i--)
    {
        out_t.Write_Str(game_text[i], settings.SIZE_BOARDER + 3 + i );
    }

    pop_front(game_text);
}





void Output_Controller::Trigger_Draw_Road_Terminal(Road* Cell)
{
    out_t.Draw_Road(Cell -> GetX(), Cell -> GetY(), Cell -> Get_Name());
}

void Output_Controller::Trigger_Draw_Hero_Terminal(Road* cell,  string action)
{
    static int direction = 0;
    if (action == "Go")
    {
        out_t.Draw_Hero(cell->GetX(), (cell->GetY()) - direction, action, cell->Get_Name());
    }
    else if (action == "Stop")
    {
        out_t.Draw_Hero(cell->GetX(), (cell->GetY()) - direction, action, cell->Get_Name());
        direction += (cell->GetY()) - ((cell->Get_Next())->GetY());
    }
    
}


 char Input_Controller::Trigger_In_Terminal()
 {
    char key = input_t.Get_Key();
    if (key == 'Y' || key == 'N')
    {
        return key;
    }
    else
    {
        cout.clear();
        cout << "Неправильный ввод";
        exit(1);
    }
 }
///