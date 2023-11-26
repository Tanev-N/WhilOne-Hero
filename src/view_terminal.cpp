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

const char* Output_Terminal::Get_Monster_Icon(string enemy) // Из монстра в букву, выводимую на экран
{
    map<string, const char*> map_of_enemies_icons = {{"bandit", "\U0001F92C"}, {"wolf", "\U0001F43A"}, {"spider", "\U0001F577"}, {"slime", "\U0001F922"}, {"dragon", "\U0001F432"}, {"lava_elemental", "\U0001F621"},
                                              {"kraken", "\U0001F419"} , {"medusa", "\U0001F40D"},  {"monkey", "\U0001F435"} , {"treant", "\U0001F333"} , {"zombie", "\U0001F635"},  {"ghost", "\U0001F47B"}};
    return  map_of_enemies_icons.find(enemy)->second;


}


void Output_Terminal::Draw_Monster(int x, int y, const string& name, const string& enemy)
{
    int colour = Get_Colour_Code(name);
    const char* symbol = Get_Monster_Icon(enemy);
    cout << "\033[" << x << ";" << y+settings.SIZE_BOARDER << "H";
    cout << "\033[37;" << colour << "m";
    cout << symbol;
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