#include "../include/view_terminal.h"

Input_Terminal::Input_Terminal(){}


Output_Terminal::Output_Terminal(){}

Input_Terminal::Input_Terminal(game_data _settings)
{
    settings = _settings;
}


Output_Terminal::Output_Terminal(game_data _settings)
{
    settings = _settings;
}

int Output_Terminal::Get_Colour_Code(string type) // Из типа дороги в код её цвета
{
    if (type == "Normal")
    {
        return(47); // Белый цвет
    }
    if (type == "Start")
    {
        return(43); // Жёлтый цвет
    }
    if (type == "Volcano")
    {
        return 41;
    }
    if (type == "Ocean")
    {
        return 46;
    }
    if (type == "Curse")
    {
        return 45;
    }
    if (type == "Jungle")
    {
        return 42;
    }
    return 0;
}

void Output_Terminal::Draw_Road(int x, int y, string name)
{
    int colour = Get_Colour_Code(name);
    cout << "\033["<< x << ";" << y+settings.SIZE_BOARDER << "H";
    cout << "\033[37;" << colour << "m" << " ";
    cout << "\033["<< x << ";" << y+1+settings.SIZE_BOARDER << "H";
    cout << "\033[37;" << colour << "m" << " ";
}

void Output_Terminal::Draw_Hero(int x, int y, string action, string name)
{
    int colour = Get_Colour_Code(name);
    cout << "\033[" << x << ";" << y+settings.SIZE_BOARDER << "H"; // Перевод курсора
    cout << "\033[37;" << colour << "m";
    if (action == "Go")
    {
        cout << "\U0001F636" << endl; //"\U0001F636" << endl; // Символ героя
    }
    if (action == "Stop")
    {
       cout << " " << endl;
       cout << "\033[" << x << ";" << y+settings.SIZE_BOARDER+1 << "H";
       cout << " " << endl;
    }
}

void Output_Terminal::Write_Str(string line, int y)
{
    cout << "\033[" << y << ";1H";
    cout << "\033[0m";
    cout << "\033[K";
    cout << line << endl;
}


char Input_Terminal::Get_Key()
{
    char answer;
    cin >> answer;
    return answer;
}