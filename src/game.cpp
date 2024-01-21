#include "../include/game.h"




int Game::Make_Step()
{
	int step, cord;
	cord = 0;
	step = rand() % 2;
    if (step == 0)
    {
		cord += 1;
    }
	else
	{
		cord -= 1;
	}
    return (cord);
}


int Game::Check_Plus(int x1, int y1, int x2, int y2) 
{
	return (( ( abs(x1 - x2) == 1) && (y1 == y2 )) || ((abs(y1 - y2) == 1 && (x1 == x2)))) ;
}




int Game::Step_Check(int new_x, int new_y, int road_len) 
{
	if ((new_x < 1) || (new_y < 1) || (new_y > settings.SIZE_BOARDER) || (new_x > settings.SIZE_BOARDER)) // Out of bounds check
	{
		return 0;
	}

	auto it = path.begin();
	int x, y, adjacent_count;
	adjacent_count = 0;
	while (it != path.end())
	{
		x = (*it).GetX();
		y = (*it).GetY();	
		if ((new_x == x) && (new_y == y)) // Already existing cell check
		{
			return 0;
		}
		else
		{
			if (Check_Plus(x, y, new_x, new_y))
			{
				adjacent_count += 1;
			}	
		}
		if ((adjacent_count > 1) && !((road_len == 1) && (adjacent_count == 2)))
		{
			return 0;
		}
 		++it;
	} 
	return 1;
}



void Game::Create_Path() 
{
	int x, y, step_x, step_y, correct_road_check;
	int road_len;
	int res_road_len;
	int error_counter; // Var on cheak impossible way 


	step_x = step_y = correct_road_check = 0;

    string name_road = "Normal";
	string start_name = "Start";


	do
	{
		x = (rand() % settings.SIZE_BOARDER) + 1; // Coordinates of start road
		y = (rand() % settings.SIZE_BOARDER) + 1;

		road_len = rand() % (settings.MAX_LEN_ROAD - settings.MIN_LEN_ROAD) + settings.MIN_LEN_ROAD;
		
		error_counter = 0;

		if (road_len % 2 == 1)
		{
			road_len += 1;
		}
		res_road_len = road_len;
		path.push_back(Road(x, y, start_name));
		road_len--;
		do
		{

			if (rand() % 2) // rand coice of coordinate
			{
				step_x = this->Make_Step();
			}
			else
			{
				step_y = this->Make_Step();
			}
			if (this->Step_Check(x+step_x, y+step_y, road_len) == 1)
			{
				path.push_back(Road(x+step_x, y+step_y, name_road));
				road_len -= 1;
				x += step_x;
				y += step_y;
				error_counter = 0;
			}
			else
			{
				error_counter += 1;
			}
			if (error_counter >= 10) // the case when the road blocked its way or got stuck in a corner
			{
				break;
			}
			step_x = step_y = 0;
		} while ((road_len != 0));


		if ( Check_Plus((*path.begin()).GetX(), (*path.begin()).GetY(), (*(--path.end())).GetX(), (*(--path.end())).GetY()) && ( error_counter < 10))
		{
			correct_road_check = 1;
		}
		else
		{
			path.clear();
		}

    for(auto i = ++path.begin(); i != path.end(); ++i)
    {
        (*i).set_monsters(default_monsters);
    }


	} while (correct_road_check != 1);


}


			int Game::Get_Size_Row() const // TODO: cut screen settings into view 
			{
				struct winsize w;
				ioctl(0, TIOCGWINSZ, &w);
				return(w.ws_row);
			}

			int Game::Get_Size_Column() const
			{
				struct winsize w;
				ioctl(0, TIOCGWINSZ, &w);
				return(w.ws_col);
			}

			int Game::Screen_Size_Check()
			{
				int row, column;
				row = Get_Size_Row();
				column = Get_Size_Column();
				if ((row < 30) || (column < 50))
				{
					return(0);
				}
				return(1);
			}

road_status::road_status()
{
	curr_road = 1;
	curr_loop = 1;
	cout_spc_road = 0;
}

int Game::Play(string name_player_file, bool new_player)
{

    if (Screen_Size_Check() == 0) {
        cout.clear();
        exit(1);
    }
	string go = "Go";
	string stop = "Stop";

	int chance_drop = 25;
	int chance_special = 33;
    cout << "\033[2J"; // Clear display
    if (new_player)
    {
        Create_Path();
        rd_status.road_len = path.size();

        output.Draw_Path_Terminal(path.begin(), path.end());
    }
    else
    {
        load_file(name_player_file);
        for( auto &i : path)
        {
            if (i.Get_Name() == "Normal")
            {
                i.set_monsters(default_monsters);
                i.set_weapons(default_weapons);
            }

        }
        cout << "\033[2J"; // Clear display
        output.Draw_Path_Terminal(path.begin(), path.end());
        spawn_monsters();

    }








	chrono::milliseconds delay(800);

	cout << endl;//
	auto it = path.begin();

	while(true) {

        if (Screen_Size_Check() == 0) {
            cout.clear();
            exit(1);
        }




        if ((*it).Get_Monster().Get_Name() != "Empty")
        {
            int battle_result;
            battle_result = Battle((*it).Get_Monster());
            if (battle_result == 0)
            {
                return 0;
            }
            else
            {
                Monster empty;
                (*it).set_monster(empty);
                Battle_End();
                output.Write_Str_Terminal("                                                         ");
                output.Write_Str_Terminal("-------------------------------------------------------");
                output.Write_Str_Terminal("                                                         ");
            }
        }


        output_position();
        output_hero_status();

        string name_road = (*it).Get_Name();

        int temp_special = rand() % 100;

        //Change to Special
        if (name_road == "Normal") {
            if (temp_special < chance_special) {
                rd_status.cout_spc_road++;
                output_notification_about_changed_road();
                (*it).ChangeToSpc(all_roads);
            }
        }
        // Hero to advent
        output.Draw_Hero_Terminal(path, it, go);
        //Check win
        if (rd_status.cout_spc_road == rd_status.road_len - 1) {
            save(name_player_file, "win");
            output.clear_controller();
            return 1;
        }
        output_step(it);

        name_road = (*it).Get_Name();

        //Play event

        if (!((rd_status.curr_loop == 1) && (rd_status.curr_road == 1))) {
            (*it).Play_Event(&hero, output, settings);
        } else {
            output.Write_Str_Terminal("Добро пожаловить в While(1) hero!");
            output.Write_Str_Terminal(
                    "Ваша задача пройти через преграды на пути и превратить все клетки пути в цветные!");
            this_thread::sleep_for(delay);
        }

        //Check lose
        if (hero.Get_Hp() <= 0) {
            output.clear_controller();
            return 0;
        }

        int temp_drop = rand() % 100;

        //Drop Item
        if (name_road == "Normal") {
            if (temp_drop <= chance_drop)
            {
                int arm_wep = rand() % 2;
                if (arm_wep == 0)
                {
                    Armor arm = Drop(default_armor);
                    output_droped_arm(arm);
                    if (ask_question())
                    {
                            hero.ChangeArmor(arm);
                    }
                }
                else
                {
                    Weapon wep = Drop(default_weapons);
                    output_droped_wep(wep);
                    if (ask_question())
                    {
                        hero.ChangeWeapon(wep);
                    }
                }
            }

        }
        else if (name_road != "Start") {
            Boots ev_boots = (*it).Get_Boots();
            if (temp_drop < ev_boots.get_weight()) {
                output_droped_boots(ev_boots);
                if (ask_question()) {
                    hero.ChangeBoots(ev_boots);
                }
            }
        }

        this_thread::sleep_for(delay);

        //Leave Hero
        output.Draw_Hero_Terminal(path, it, stop);


        if (Screen_Size_Check() == 0) {
            return 0;
        }

        rd_status.curr_road++;

        //Next measugment
        output.Write_Str_Terminal("                                                         ");
        output.Write_Str_Terminal("-------------------------------------------------------");
        output.Write_Str_Terminal("                                                         ");


        ++it;
        //Next loop





        if (it == path.end()) {
            it = path.begin();
            output.Write_Str_Terminal("Монстры начинают появляться на дороге...");
            spawn_monsters();
            rd_status.curr_loop++;
            rd_status.curr_road = 1;
            save(name_player_file, "NEXT_LOOP");
        }
    }

	
}



int Game::Battle(Monster enemy)
{
    int enemy_hp = enemy.Get_Hp();
    int enemy_delay = enemy.attack_delay();
    int battle_time =  1;
    int damage;
    Battle_Start(enemy);
    chrono::milliseconds combat_delay(1500);
    while ((enemy_hp > 0) && (hero.Get_Hp() > 0))
    {
        if (Screen_Size_Check() == 0) {
            cout.clear();
            exit(1);
        }

        if ((battle_time % enemy_delay) == 0) // Монстр наносит удар (Его скорость выросла до значения battle_speed)
        {
            if (enemy.Get_Attack() >= (hero.Get_Defense() + hero.GetArmor().Get_Defense()))
            {
                damage = enemy.Get_Attack() - (hero.Get_Defense() + hero.GetArmor().Get_Defense());
            }
            else
            {
                damage = 0;
            }
            hero.takeDamage(damage);
            hero.GetArmor().reduce_durability();
            if (hero.GetArmor().Get_Durability() == 0)
            {
                output.Write_Str_Terminal("Ваша броня сломалась! Приготовьтесь!");
                Armor arm;
                hero.ChangeArmor(arm);
            }
            output.Colour_Entity_Terminal(settings.SIZE_BOARDER/2, (settings.SIZE_BOARDER/2 + 4), "Nothing", "hit");
            output.Write_Str_Terminal(enemy.Get_Name() + " наносит удар! Вы получаете " + to_string(damage) + " урона.");
            this_thread::sleep_for(combat_delay);
            output.Clear_Cell_Terminal(settings.SIZE_BOARDER/2, (settings.SIZE_BOARDER/2 + 3));
        }



        if (( battle_time % (hero.attack_delay() + hero.GetWeapon().attack_delay())) == 0 )
        {
            if ((hero.Get_Attack() + hero.GetWeapon().Get_Attack()) > enemy.Get_Defense())
            {
                damage = (hero.Get_Attack() + hero.GetWeapon().Get_Attack()) - enemy.Get_Defense();
            }
            else
            {
                output.Write_Str_Terminal("Ваша атака слишком слаба..."); // Сообщение о том, что у героя слишком слабая атака. (Наносится один урон)
                damage = 1;
            }
            enemy_hp -= damage;
            hero.GetWeapon().reduce_durability();
            if (hero.GetWeapon().Get_Durability() == 0)
            {
                output.Write_Str_Terminal("Ваше оружие сломалось! Руки героя сжимаются в кулаки...");
                Weapon wep;
                hero.ChangeWeapon(wep);
            }
            output.Colour_Entity_Terminal(settings.SIZE_BOARDER/2, (settings.SIZE_BOARDER/2 + 1), "Nothing", "hit");
            output.Write_Str_Terminal("Вы наносите удар! " + enemy.Get_Name() + " получает " + to_string(damage) + " урона.");
            this_thread::sleep_for(combat_delay);
            output.Clear_Cell_Terminal(settings.SIZE_BOARDER/2, (settings.SIZE_BOARDER/2 + 1));
        }
        battle_time++;

    }
    if (hero.Get_Hp() <= 0)
    {
        return 0;
    }
    else
    {
        output.Write_Str_Terminal("Вы победили! Противник был повержен!");
        int new_exp = hero.Get_Exp() + enemy.Get_Exp();
        if (new_exp >= 100)
        {
            hero.Level_Up(settings);
        }
    }
    Reward();
    return 1;
}





void Game::Battle_Start(Monster enemy)
{
    output.Undraw_Path_Terminal(path.begin(), path.end());
    output.Colour_Entity_Terminal(settings.SIZE_BOARDER/2, (settings.SIZE_BOARDER/2 - 1), "Nothing", "hero");
    output.Colour_Entity_Terminal(settings.SIZE_BOARDER/2, (settings.SIZE_BOARDER/2 + 6), "Nothing", enemy.Get_Name());
    output.Write_Str_Terminal(enemy.Get_Phrase());
}

void Game::Reward()
{
    int loot = rand() % 3;
    switch(loot)
    {
        case 0:
        {
            output.Write_Str_Terminal("Обыскав труп монстра, вы ничего не нашли.");
            break;
        }
        case 1:
        {
            output.Write_Str_Terminal("Обыскав труп монстра, вы находите... броню!");
            Armor arm = Drop(default_armor);
            output_droped_arm(arm);
            if (ask_question())
            {
                hero.ChangeArmor(arm);
            }
            break;
        }
        case 2:
        {
            output.Write_Str_Terminal("Обыскав труп монстра, вы находите... оружие!");
            Weapon wep = Drop(default_weapons);
            output_droped_wep(wep);
            if (ask_question())
            {
                hero.ChangeWeapon(wep);
            }
            break;
        }
    }
}

void Game::Battle_End()
{
    auto it_begin = path.begin();
    auto it_end = path.end();
    output.Clear_Cell_Terminal(settings.SIZE_BOARDER/2, settings.SIZE_BOARDER/2);
    output.Clear_Cell_Terminal(settings.SIZE_BOARDER/2, (settings.SIZE_BOARDER/2 + 1));
    output.Clear_Cell_Terminal(settings.SIZE_BOARDER/2, (settings.SIZE_BOARDER/2 + 2));
    output.Clear_Cell_Terminal(settings.SIZE_BOARDER/2, (settings.SIZE_BOARDER/2 + 3));
    output.Clear_Cell_Terminal(settings.SIZE_BOARDER/2, (settings.SIZE_BOARDER/2 + 4));
    output.Clear_Cell_Terminal(settings.SIZE_BOARDER/2, (settings.SIZE_BOARDER/2 + 5));
    output.Clear_Cell_Terminal(settings.SIZE_BOARDER/2, (settings.SIZE_BOARDER/2 + 6));
    output.Draw_Path_Terminal(it_begin, it_end);
    output.Draw_Monsters_Terminal(it_begin, it_end);
}



void Game::output_droped_wep(Weapon _wep)
{
    string drop_wep = "Вам выпало оружие: " + _wep.Get_Name() + ", atk: " + to_string(_wep.Get_Attack()) + ", att_delay: " + to_string(
            _wep.attack_delay()) + ", dur: " + to_string(_wep.Get_Durability());
    output.Write_Str_Terminal(drop_wep);
}



void Game::output_win()
{
	string win = "Мои поздравления! Вы вспомнили все клетки! Теперь вы сможете найти дорогу домой!";
	string end = "THE END........возможно)";
    cout << "\033[0m";
	cout << "\033[1;1H";
	cout << "\033[2J";
	cout << win << endl;
	cout << end << endl;
}

void Game::output_lose()
{
	cout << "\033[1;1H";
	cout << "\033[2J";
	cout << "Герой не справился с испытанием и умер...." << endl;
}



void Game::output_droped_boots(Boots _bts)
{
	string drop_boots = "Вам выпали ботинки: " + _bts.Get_Name();
	output.Write_Str_Terminal(drop_boots);
}
void Game::output_droped_arm(Armor _arm)
{
	string drop_boots = "Вам выпал грудак, тип: " + _arm.Get_Type() + ",  def:  " + to_string(_arm.Get_Defense());
	output.Write_Str_Terminal(drop_boots);
}



void Game::output_position()
{
	string pos = "Круг " + to_string(rd_status.curr_loop) + " . Клетка " + to_string(rd_status.curr_road) + "/" + to_string(rd_status.road_len); 
	output.Write_Str_Terminal(pos);
}
void Game::output_hero_status()
{
	int hero_hp = hero.Get_Hp();
	string name_boots = hero.GetBoots().Get_Name();
	int boots_dur = hero.GetBoots().Get_Durability();
	int arm_def = hero.GetArmor().Get_Defense();
	int arm_dur = hero.GetArmor().Get_Durability();
	string stats;
	if ((boots_dur < 0) && (arm_dur < 0))
	{
		stats = "HP: " + to_string(hero_hp) + " . Boots: " +  name_boots + ".   Armor,    def:  " + to_string(arm_def) ;
	}
	else if ((boots_dur < 0))
	{
		stats = "HP: " + to_string(hero_hp) + " . Boots: " +  name_boots  + ".   Armor,    def:  " + to_string(arm_def) + ", dur:   " + to_string(arm_dur);
	}
	else if ((arm_dur < 0))
	{
		stats = "HP: " + to_string(hero_hp) + " . Boots: " +  name_boots + ",   dur: "+ to_string(boots_dur) + ".   Armor,    def:  " + to_string(arm_def);
	}
	else
	{
		stats = "HP: " + to_string(hero_hp) + " . Boots: " +  name_boots + ",   dur: "+ to_string(boots_dur) + ".   Armor,    def:  " + to_string(arm_def) + ", dur:   " + to_string(arm_dur);
	}
	output.Write_Str_Terminal(stats);
}
void Game::output_notification_about_changed_road()
{
	string def_smen = "Нормальная дорога изменилась...";
	output.Write_Str_Terminal(def_smen);
}
void Game::output_step(list<Road>::iterator it)
{
	string step = "Вы наступили на " + (*it).Get_Name();
	output.Write_Str_Terminal(step);	
}
        




int Game::get_weight(const string& type)
{
    map<string, int> types_weight = {       {"common",  100},
                                          {"rare",   33},
                                          {"epic", 18},
                                          {"legendary",   8},
                                          {"unique",   4},
                                          {"holy",  2},

                                          {"evently", 15}
    };
    return  types_weight.find(type)->second;
}


void Game::spawn_monsters()
{
    int direction = 0;
    int spawn_chance = 15;
    int curr_chance;
    chrono::milliseconds delay(700);
    for (auto i = path.begin(); i != path.end(); ++i)
    {
        curr_chance = rand()%100;
        if ( (curr_chance < spawn_chance) && (i != path.begin()) )
        {
            vector<Monster> _monsters = (*i).Get_Monsters();
            (*i).set_monster(Drop(_monsters) );
            output.Draw_Monster_Terminal(i, direction);
            cout << flush;
            this_thread::sleep_for(delay);
        }
        auto next_it = i;
        ++next_it;
        if (next_it == path.end())
        {
            next_it = path.begin();
        }
        direction += ((*i).GetY()) - ((*next_it).GetY());
    }
}

template<typename T>
T Game::Drop(vector<T>& default_thing)
{

    int sum_weight = 0;
    map<string, int> count_types;
    string rarity;
    string raritys[] = {"common", "rare", "epic", "legendary", "unique", "holy"};
    for(auto & i : default_thing)
    {
        rarity = i.Get_Type();
        auto rar_c = count_types.find(rarity);
        if (rar_c != count_types.end())
        {
            (rar_c->second)++;
        }
        else
        {
            count_types.emplace(rarity,1);
        }
        sum_weight+=get_weight(i.Get_Type() );
    }
    int chance;
    chance = rand() % sum_weight;
    int j = 0;
    while (chance > 0)
    {
        auto rar_c = count_types.find(raritys[j]);
        if (rar_c != count_types.end())
        {
            int weight_of_rarity = (rar_c->second)*get_weight(raritys[j]);
            chance-=weight_of_rarity;
        }
        j++;
    }
	j--;
	
	int rand_sequr_num = rand()%(count_types.find(raritys[j])->second);

	int k = 0;
	int i = 0;
	while (k < rand_sequr_num)
	{
		if (default_thing[i].Get_Type() == raritys[j])
		{
			k++;
		}
		i++;
	}

    return default_thing[i];

}
int Game::ask_question() // NOLINT(*-no-recursion)
{
	int answer; 
	output.Write_Str_Terminal("Хотите ли надеть? Y/N: ");
	cout << "\033[" << settings.SIZE_BOARDER+settings.ROW_COUNT+3 <<  ";25H";
	answer = input.In_Terminal();
	if (answer == 1)
	{
		return 1;
	}
	else if (answer == 0)
	{
		return 0;
	}
	else
	{
		output.Write_Str_Terminal("Неправильный ввод");
		return ask_question();
	}
}





void Game::check_left_scope(ifstream* fin)
{
	string temp;
	*(fin) >> temp;
	if ( temp != "{" )
	{
		cout << "Не найдена левая закрывающая скобка" << endl;
		exit(1);
	}
}
void Game::fill_game_int_setting(ifstream* fin, string key)
{
	string word;
	(*fin) >> word;
	if (key == "#MAX_HP")
	{
		settings.MAX_HP = stoi(word);
	}
	if (key == "#MIN_LEN_ROAD")
	{
		settings.MIN_LEN_ROAD = stoi(word);
	}
	if (key == "#MAX_LEN_ROAD")
	{
		settings.MAX_LEN_ROAD = stoi(word);
	}
	if (key == "#SIZE_BOARDER")
	{
		settings.SIZE_BOARDER = stoi(word);
	}
	if (key == "#ROW_COUNT")
	{
		settings.ROW_COUNT = stoi(word);
	}
}
void Game::check_right_scope(ifstream* fin)
{
	string temp;
	*(fin) >> temp;
	if ( temp != "}" )
	{
		cout << "Не найдена правая закрывающая скобка" << endl;
		exit(1);
	}
}

void Game::save(string player_file, string action)
{
    ofstream file(player_file);
    string word;
    if (action == "win")
    {
        file << number_level << endl;
        file << "new" << endl;
        file << "#rd_status" << endl;
        file << "{" << endl;
        file << "\t" << "1" << endl;
        file << "\t" << "1" << endl;
        file << "\t" << "0" << endl;
        file << "\t" << "0" << endl;
        file << "}" << endl;
    }
    else
    {
        file << number_level << endl;
        file << "continue" << endl;
        file << "#rd_status" << endl;
        file << "{" << endl;
        file << "\t" << rd_status.curr_road << endl;
        file << "\t" << rd_status.curr_loop << endl;
        file << "\t" << rd_status.cout_spc_road << endl;
        file << "\t" << rd_status.road_len << endl;
        file << "}" << endl;
    }

    file << "#Road" << endl;
    file << "{" << endl;
    for (auto i : path)
    {
        string command_road = "#" + i.Get_Name();
        file << "\t" << command_road << " " <<  i.GetX() << " " << i.GetY() <<  endl;
    }
    file << "}" << endl;

    file << "#Level" << endl;
    file << "{" << endl;
    file << "\t" << hero.Get_level() << endl;
    file << "}" << endl;

    file << "#Exp" << endl;
    file << "{" << endl;
    file << "\t" << hero.Get_Exp() << endl;
    file << "}" << endl;

    file << "#Hp" << endl;
    file << "{" << endl;
    file << "\t" << hero.Get_Hp() << endl;
    file << "}" << endl;

    file << "#Speed" << endl;
    file << "{" << endl;
    file << "\t" << hero.attack_delay() << endl;
    file << "}" << endl;

    file << "#Atack" << endl;
    file << "{" << endl;
    file << "\t" << hero.Get_Attack() << endl;
    file << "}" << endl;

    file << "#Boots" << endl;
    file << "{" << endl;
    file << "\t" <<  ( hero.GetBoots().Get_Type() ) << endl;
    file << "\t" <<  ( hero.GetBoots().Get_Durability() ) << endl;
    file << "\t" <<  ( hero.GetBoots().Get_Name() ) << endl;
    file << "}" << endl;

    file << "#Chestplate" << endl;
    file << "{" << endl;
    file << "\t" << ( hero.GetArmor().Get_Name() ) << endl;
    file << "\t" <<  ( hero.GetArmor().Get_Defense() ) << endl;
    file << "\t" <<  ( hero.GetArmor().Get_Durability() ) << endl;
    file << "\t" <<  ( hero.GetArmor().Get_Type() ) << endl;
    file << "}" << endl;

    file << "#Weapon" << endl;
    file << "{" << endl;
    file << "\t" << ( hero.GetWeapon().Get_Type() ) << endl;
    file << "\t" <<  ( hero.GetWeapon().Get_Name()) << endl;
    file << "\t" <<  ( hero.GetWeapon().Get_Durability() ) << endl;
    file << "\t" <<  ( hero.GetWeapon().Get_Attack() )  << endl;
    file << "\t" << (hero.GetWeapon().attack_delay() ) << endl;
    file << "}" << endl;

    file.close();

}


void Game::load_file(string player_file)
{
    ifstream file(player_file);
    string word;
    file >> word; //number_level
    file >> word; // win or continue
    file >> word; //#rd_status
    file >> word; //{
    file >> word; // rd_status.curr_road
    rd_status.curr_road = stoi(word);
    file >> word; //rd_status.curr_loop
    rd_status.curr_loop = stoi(word);
    file >> word; //rd_status.cout_spc_road
    rd_status.cout_spc_road = stoi(word);
    file >> word; //rd_status.road_len
    rd_status.road_len = stoi(word);
    file >> word; // }

    file >> word; // #Road
    file >> word; // {
    file >> word; // road_name or }
    while (word != "}")
    {
        Road road = *create_road_from_file(word);
        file >> word;
        road.SetX(stoi(word));
        file >> word;
        road.SetY(stoi(word));
        file >> word;
        path.push_back(road);
    }

    hero.load_hero(&file);
    settings.MAX_HP += hero.Get_level()*10;
    file.close();




}



Weapon Game::create_weapon_from_file(string id_weapon)
{
    ifstream ifin("../configs/Items.txt");
    string word;
    search_id(&ifin, id_weapon);
    check_left_scope(&ifin);

    string rarity;
    ifin >> rarity;

    string name;
    ifin >> name;

    int durability;
    ifin >> word;
    durability = stoi(word);

    int attack;
    ifin >> word;
    attack = stoi(word);

    int speed;
    ifin >> word;
    speed = stoi(word);

    check_right_scope(&ifin);
    ifin.close();

    Weapon weap(rarity, name, durability, attack, speed);

    return weap;
}






Road* Game::create_road_from_file(string id_road)
{
	ifstream rfin("../configs/Roads.txt");
	search_id(&rfin, id_road);
	Road* new_type_road = new Road();
    vector<Monster> evently_monster;
    vector<Weapon> evently_weapons;
	check_left_scope(&rfin);

	string word;

	rfin >> word; // name
	new_type_road->set_name(word);

	rfin >> word; // boots
	
	new_type_road->set_boots(create_boots_from_file(word));

    rfin >> word; // weapons



    if (word == "#Weapons")
    {
        check_left_scope(&rfin);
        rfin >> word;
        while( word != "}")
        {
            evently_weapons.push_back(create_weapon_from_file(word));
            rfin >> word;
        }
    }


    rfin >> word;

    if (word == "#Monsters")
    {
        check_left_scope(&rfin);
        rfin >> word;
        while( word != "}")
        {
            evently_monster.push_back(create_monster_from_file(word));
            rfin >> word;
        }
    }
    else
    {
        cerr << "Нет ивентовых монстров" << endl;
        exit(-1);
    }




	rfin.get(); // знак перевода строки 
	rfin.get(); // знак возврата коретки
	rfin.get(); // табуляция

	getline(rfin, word); // good action
	string good = word;

	rfin.get();  // табуляция
	
	getline(rfin, word); // bad action
	string bad = word; 

	rfin >> word; // changer
	int changer = stoi(word);

	Event new_event(good, bad, changer);
	new_type_road->set_event(new_event);
    new_type_road->set_monsters(evently_monster);
	check_right_scope(&rfin);

	rfin.close();

	return new_type_road;
}

void Game::search_id(ifstream* fin, string id)
{
	if (id[0] != '#')
	{
		cout << "Не машиное слово среди аргументов" << endl;
		exit(1);
	}

	string word;
	(*fin) >> word;

	while ((word != id) && !((*fin).eof()))
	{
		(*fin) >> word;
	}

	if (word != id)
	{
		cout << "Не найдено машиное слово внутри файла" << endl;
		exit(1);
	}
}

Boots Game::create_boots_from_file(string id_boots)
{
	ifstream ifin("../configs/Items.txt");
	string word;
	search_id(&ifin, id_boots);
	check_left_scope(&ifin);
  
	string rarity;
	ifin >> rarity;


    string name;
    ifin >> name;

	int durability;

	ifin >> word;
    durability = stoi(word);

	check_right_scope(&ifin);
  
	ifin.close();
	Boots bts(rarity, name, durability);


	return bts;
}

Armor Game::create_armor_from_file(string id_armor)
{
	ifstream ifin("../configs/Items.txt");
	string word;
	search_id(&ifin, id_armor);
	check_left_scope(&ifin);

	string rarity;
	ifin >> rarity;

    string name;
    ifin >> name;

    int durability;

	ifin >> word;
    durability = stoi(word);
	
	int defense;
	ifin >> word;
	defense = stoi(word);

	check_right_scope(&ifin);
	Armor arm(rarity,name, durability, defense);
	ifin.close();

	return arm;
}

Monster Game::create_monster_from_file(string id_monster)
{
    ifstream ifin("../configs/Monsters.txt");
    string word;
    search_id(&ifin, id_monster);
    check_left_scope(&ifin);

    string name;
    ifin >> name;

    string type;
    ifin >> type;
    ifin.get(); // знак перевода строки
    ifin.get(); // знак возврата коретки
    ifin.get(); // табуляция

    getline(ifin, word); // good action
    string phrase = word;

    int hp;
    ifin >> word;
    hp = stoi(word);

    int exp;
    ifin >> word;
    exp = stoi(word);

    int attack;
    ifin >> word;
    attack = stoi(word);

    int speed;
    ifin >> word;
    speed = stoi(word);

    int defense;
    ifin >> word;
    defense = stoi(word);

    check_right_scope(&ifin);
    Monster mnstr(name,type, phrase, hp, exp, attack, speed, defense);

    ifin.close();

    return mnstr;

}


Game::Game(const string& level, int number_lvl) : rd_status()
{
	ifstream fin(level);
	vector<string> names_available_roads;
	if (!fin.is_open())
	{
		cout << "Файл не открылся" << endl;
		exit(1);
	}
    number_level = number_lvl;
	string word, key;
	while (!fin.eof())
	{
		fin >> word;
		if (word[0] == '#')
		{
			for (int i = 0; i < settings.names_of_game_settings.size(); i++) //fill const int in settings
			{
				if (word == settings.names_of_game_settings[i])
				{
					key = word;
					check_left_scope(&fin);
					fill_game_int_setting(&fin, key);
					check_right_scope(&fin);
				}
			}

			if (word == "#ROADS")
			{
				check_left_scope(&fin);
				fin >> word;

				while( word != "}")
				{
					all_roads.push_back(create_road_from_file(word));
					fin >> word;

				}
			}

            if (word == "#WEAPONS")
            {
                check_left_scope(&fin);
                fin >> word;
                while( word != "}")
                {
                    default_weapons.push_back(create_weapon_from_file(word));
                    fin >> word;
                }
            }

			if (word == "#ARMOR")
			{
				check_left_scope(&fin);
				fin >> word;
				while( word != "}")
				{
					default_armor.push_back(create_armor_from_file(word));
					fin >> word;
				}
			}

            if (word == "#MONSTERS")
            {
                check_left_scope(&fin);
                fin >> word;
                while( word != "}")
                {
                    default_monsters.push_back(create_monster_from_file(word));
                    fin >> word;
                }
            }

			
		}
	}


	Armor naked("Default", "Майка", -1, 0);//Create of hero
    Boots sandals("Default", "Сандали", -1);

	hero.Set_hp(settings.MAX_HP);
	hero.ChangeArmor(naked);
	hero.ChangeBoots(sandals);

	input.set_settings(settings);
	output.set_settings(settings);
	
	fin.close();

	if (all_roads.empty())
	{
		cout << "У вас нету ивентовых клеток" << endl;
		exit(1);
	}
	
}