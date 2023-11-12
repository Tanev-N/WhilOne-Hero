#include "../include/cell.h"


Cell::Cell(int _x, int _y, string _name) : x(_x), y(_y), name(std::move(_name)) {}

int Cell::GetX() const
{
    return x;
}
int Cell::GetY() const
{
    return y;
}
string Cell::Get_Name() const
{
    return name;
}
Road::Road(int _x, int _y, const string& _name) : Cell(_x, _y, _name)
{
    if (_name == "Normal")
    {
        Event norml_event("Перед вами пустошь, вы чувствуете, что что-то не так...", "Набравшись силой необычных клеток, бог мира вас отвергает, теперь вы не можете переносить пустошь", 7);
        event = norml_event;
        Boots bts;
        boots = bts;
    }
}


void Cell::set_x(int _x)
{
    x = _x;
}
void Cell::set_y(int _y)
{
    y = _y;
}
void Cell::set_name(const string& _name)
{
    name = _name;
}

void Road::set_boots(const Boots& _item)
{
    boots = _item; 
}

void Road::set_event(const Event& _event)
{
    event = _event;
}

Cell::Cell()
{
    name = "template";
}

Event Road::get_event() const
{
    return event;
}
void Road::ChangeToSpc(vector<Road*> road_types)
{
    int road_num;
    road_num = rand() % road_types.size();
    boots = road_types[road_num]->Get_Boots();
    event = road_types[road_num]->get_event();
    name = road_types[road_num]->Get_Name();
}
Boots Road::Get_Boots() const
{
    return boots;
}

void Road::Play_Event(Hero *hero, Output_Controller output, const game_data& sets)
{
    if (name == "Start")
    {
        int heal_start = 10;
        hero->Heal(heal_start, sets);
        string notif_heal = "Вы прошли круг! Вспоминая дорогу, вам стоновится лучше и вы лечитесь ";
        output.Write_Str_Terminal(notif_heal + to_string(heal_start));
        return;
    }
    if ((hero->GetBoots().Get_Name() == boots.Get_Name()))
    {
        output.Write_Str_Terminal(event.get_good());
        if (name != "Normal")
        {
            string notif_heal = "Вы лечитесь на ";
            output.Write_Str_Terminal(notif_heal + to_string(event.get_changer()));
            hero->Heal(event.get_changer(), sets);
            hero->GetBoots().reduce_durability();

            if (hero->GetBoots().Get_Durability() == 0)
            {
                string notif_break = "Ваши ботинки сломались, к счастью у вас всегда при себе сандали";
                output.Write_Str_Terminal(notif_break);
                Boots bts; 
                hero->ChangeBoots(bts);
            }
        }
    }
    else
    {
        output.Write_Str_Terminal(event.get_bad());
        int damage  = event.get_changer() - hero->GetArmor().Get_Defense();
        if (damage < 0) { damage = 0; }
        string notif_damage = "Вы получаете урон на ";
        output.Write_Str_Terminal(notif_damage + to_string(damage));
        hero->takeDamage(damage);
        hero->GetArmor().reduce_durability();

        if (hero->GetArmor().Get_Durability() == 0)
        {
            string notif_break = "Ваш грудак сломался , другой найдёте, а пока походите в майке";
            output.Write_Str_Terminal(notif_break);
            Armor arm;
            hero->ChangeArmor(arm);
        }
    }
}