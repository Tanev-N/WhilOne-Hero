
#include "../include/controller.h"



void Input_Controller::set_settings(const game_data& _settings)
{
    settings = _settings;
}

void Output_Controller::set_settings(const game_data& _settings)
{
    settings = _settings;
}

Input_Controller::Input_Controller() : input_t(){}

Output_Controller::Output_Controller() : out_t(){}

Input_Controller::Input_Controller(const game_data& _settings) : input_t(_settings)
{
    settings = _settings;
}

Output_Controller::Output_Controller(const game_data& _settings) : out_t(_settings)
{
    settings = _settings;
}

void Output_Controller::Draw_Path_Terminal(list<Road>::const_iterator it_begin, list<Road>::const_iterator it_end)
{
    int direction = 0; // используется как смещение по оси y в терминал, т.к клетка сдвоенная 
    list<Road>::const_iterator next_it;
    for (auto i = it_begin; i != it_end; ++i)
    {
        out_t.Draw_Road((*i).GetX(), ((*i).GetY()) - direction , (*i).Get_Name());
        next_it = i;
        ++next_it;
        direction += ((*i).GetY() ) - ((*next_it).GetY());
    }
    cout << "\033[0m";
}


template<typename T>
void pop_front(vector<T>& v)
{
    if (v.size() > 0) {
        v.erase(v.begin());
    }
}


void Output_Controller::Write_Str_Terminal(string new_line)
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





void Output_Controller::Draw_Road_Terminal(Road Cell)
{
    out_t.Draw_Road(Cell.GetX(), Cell.GetY(), Cell.Get_Name());
}

void Output_Controller::Draw_Hero_Terminal(list<Road> &path, list<Road>::const_iterator it,  string action)
{
    static int direction = 0; //используется как смещение по оси y в терминал, т.к клетка сдвоенная
    if (action == "Go")
    {
        out_t.Draw_Hero((*it).GetX(), ((*it).GetY()) - direction, action, (*it).Get_Name());
    }
    else if (action == "Stop")
    {
        auto next_it = it;
        ++next_it;
        if (next_it == path.end())
        {
            next_it = path.begin();
        }
        out_t.Draw_Hero((*it).GetX(), ((*it).GetY()) - direction, action, (*it).Get_Name());
        direction += ((*it).GetY()) - ((*next_it).GetY());
    }
    
}

void Output_Controller::Draw_Monster_Terminal(list<Road>::const_iterator it, int direction)
{
    out_t.Draw_Monster((*it).GetX(), ((*it).GetY()) - direction, (*it).Get_Name(), (*it).Get_Monster().Get_Name());

}





 int Input_Controller::In_Terminal()
 {
    char key = input_t.Get_Key();
    if (key == 'Y' || key == 'y')
    {
        return 1;
    }
    else if (key == 'N' || key == 'n')
    {
        return 0;
    }
    else
    {
        return 255; // incorrect input, 255 is'n using
    }
 }
///