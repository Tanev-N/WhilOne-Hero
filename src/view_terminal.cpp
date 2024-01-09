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

int Output_Terminal::Get_Colour_Code(const string& type) // Из типа дороги в код её цвета
{
    map<string, int> color_cell = {       {"Normal",  47},
                                          {"Start",   43},
                                          {"Volcano", 41},
                                          {"Ocean",   44},
                                          {"Curse",   45},
                                          {"Jungle",  42},
                                          {"Frozen_lake",  46},
                                          {"Cemetery", 100},
                                          {"Hell", 101},
                                          {"Swamp", 102},
                                          {"Desert", 103},
                                          {"Deadly_river", 104},
                                          {"Magic_forest", 105},
                                          {"Highlands", 106}
    };
    return  color_cell.find(type)->second;
}

const char* Output_Terminal::Get_Entity_Icon(const string& enemy) // Из монстра в букву, выводимую на экран
{
    map<string, const char*> map_of_enemies_icons = {{"bandit", "\U0001F92C"},
                                                     {"hero", "\U0001F636"},
                                                     {"wolf", "\U0001F43A"},
                                                     {"spider", "\U0001F577"},
                                                     {"slime", "\U0001F922"},
                                                     {"dragon", "\U0001F432"},
                                                     {"lava_elemental", "\U0001F621"},
                                                     {"kraken", "\U0001F419"} ,
                                                     {"blowfish", "\U0001F421"},
                                                     {"monkey", "\U0001F435"} ,
                                                     {"treant", "\U0001F333"} ,
                                                     {"zombie", "\U0001F9DF"},
                                                     {"ghost", "\U0001F47B"},
                                                     {"demon", "\U0001F47F"},
                                                     {"skeleton", "\U0001F480"},
                                                     {"ogre", "\U0001F479"},
                                                     {"vampire", "\U0001F9DB"},
                                                     {"merman", "\U0001F9DC"},
                                                     {"elf", "\U0001F9DD"},
                                                     {"genie", "\U0001F9DE"},
                                                     {"mage", "\U0001F9D9"},
                                                     {"fairy", "\U0001F9DA"},
                                                     {"unicorn", "\U0001F984"},
                                                     {"bear", "\U0001F43B"},
                                                     {"penguin", "\U0001F427"},
                                                     {"snowman", "\U00002603"},
                                                     {"alien", "\U0001F47D"},
                                                     {"magic_elemental", "\U0001F47E"},
                                                     {"goblin", "\U0001F47A"},
                                                     {"ice_elemental", "\U0001F976"},
                                                     {"crocodile", "\U0001F40A"},
                                                     {"T-Rex", "\U0001F996"},
                                                     {"shark", "\U0001F988"},
                                                     {"ninja", "\U0001F977"},
                                                     {"snake", "\U0001F40D"},
                                                     {"hit", "\U0001F4A5"}

    };
    auto it_icon = map_of_enemies_icons.find(enemy);
    if (it_icon == map_of_enemies_icons.end())
    {
        return "нет иконки моба";
    }
    else
    {
        return map_of_enemies_icons.find(enemy)->second;
    }
}


void Output_Terminal::Draw_Entity(int x, int y, const string& name, const string& ent)
{
    int colour = Get_Colour_Code(name);
    const char* symbol = Get_Entity_Icon(ent);
    cout << "\033[" << x << ";" << y+settings.SIZE_BOARDER << "H";
    cout << "\033[37;" << colour << "m";
    cout << symbol;
}


void Output_Terminal::Clear_Road(int x, int y)
{
    int colour = 40;
    cout << "\033["<< x << ";" << y+settings.SIZE_BOARDER << "H";
    cout << "\033[37;" << colour << "m" << " ";
    cout << " ";
    cout << "\033["<< x << ";" << y+1+settings.SIZE_BOARDER << "H";
    cout << "\033[37;" << colour << "m" << " ";
    cout << " ";
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