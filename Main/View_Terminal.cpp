#include "../Headers/all.h"

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
    cout << "\033["<< x << ";" << y << "H";
    cout << "\033[30;" << colour << "m" << " ";
    cout << "\033["<< x << ";" << y+1 << "H";
    cout << "\033[30;" << colour << "m" << " ";
}

void Output_Terminal::Draw_Hero(int x, int y, string action, string name)
{
    int colour = Get_Colour_Code(name);
    if (action == "Go")
    {
        cout << "\033[" << x << ";" << y << "H"; // Перевод курсора
        cout << "\033[30;" << colour << "m";
        cout << "\U0001F636" << endl; //"\U0001F636" << endl; // Символ героя
    }
    if (action == "Stop")
    {
       cout << "\033[" << x << ";" << y << "H";
       cout << " " << endl;
    }
}


void Write_Str(string line, int y)
{
    cout << "\033[" << y << ";1H";
    cout << line;
}