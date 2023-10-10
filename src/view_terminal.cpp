#include <iostream>
#include <string>


#include "view_terminal.h"
#include "date.h"

date SETTING;

using namespace std;

Input_Terminal::Input_Terminal(void) {}


Output_Terminal::Output_Terminal(void) {}

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

    return 0;
}

void Output_Terminal::Draw_Road(int x, int y, string name)
{
    int colour = Get_Colour_Code(name);
    cout << "\033["<< x << ";" << y+SETTING.SIZE_BOARDER << "H";
    cout << "\033[37;" << colour << "m" << " ";
    cout << "\033["<< x << ";" << y+1+SETTING.SIZE_BOARDER << "H";
    cout << "\033[37;" << colour << "m" << " ";
}

void Output_Terminal::Draw_Hero(int x, int y, string action, string name)
{
    int colour = Get_Colour_Code(name);
    cout << "\033[" << x << ";" << y+SETTING.SIZE_BOARDER << "H"; // Перевод курсора
    cout << "\033[37;" << colour << "m";
    if (action == "Go")
    {
        cout << "\U0001F636" << endl; //"\U0001F636" << endl; // Символ героя
    }
    if (action == "Stop")
    {
       cout << " " << endl;
    }
}

void Output_Terminal::Write_Str(string line, int y)
{
    cout << "\033[" << y << ";1H";
    cout << "\033[0m";
    //cout << "\033[0K";
    cout << line << endl;
}