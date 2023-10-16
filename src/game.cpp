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

	Road *move = start;
	int x, y, adjacent_count;
	adjacent_count = 0;
	while (move != nullptr)
	{
		x = move->GetX();
		y = move->GetY();	
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
 		move = move->Get_Next();
	} 
	return 1;
}

void Game::Delete_Path()
{
	Road* temp;
	head = start;
	while(head->Get_Next() != nullptr)
	{
		temp =  head->Get_Next();
		delete head;
		head = temp;
	}
	delete head;
}

int Game::Create_Path() 
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
		start = new Road(x, y, start_name);

		road_len--;

		head = start; // Re:Zero

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
				Road *newroad;
				newroad = new Road(x+step_x, y+step_y, name_road);
				head->Change_Next(newroad);	
				head = head->Get_Next();
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


		if ( Check_Plus(start->GetX(), start->GetY(), head->GetX(), head->GetY()) && ( error_counter < 10))
		{
			correct_road_check = 1;
		}
		else
		{
			Delete_Path();
		}


	} while (correct_road_check != 1);
	
	head -> Change_Next(start);
	head = head->Get_Next();

	return res_road_len;
}


			int Game::Get_Size_Row() // TODO: cut screen settings into view 
			{
				struct winsize w;
				ioctl(0, TIOCGWINSZ, &w);
				return(w.ws_row);
			}

			int Game::Get_Size_Column()
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
				if ((row < 20) || (column < 40))
				{
					return(0);
				}
				return(1);
			}


void Game::Play()
{
    rd_status.road_len = Create_Path();
	rd_status.curr_road = 1;
	rd_status.сurr_loop = 0;
	rd_status.cout_cps_road = 0;

	string go = "Go";
	string stop = "Stop";

	int chance_drop = 35;
	int chance_special = 40;

	cout << "\033[2J"; // Clear display

	output.Trigger_Draw_Start_Road_Terminal(start); 
	
	cout << "\033[0m";

	chrono::milliseconds delay(4000);

	cout << endl;//

	while(1)
	{
		string name_road = head->Get_Name();
		int temp_special = rand()%100;
		if (name_road == "Start")
		{
			rd_status.сurr_loop++;
			rd_status.curr_road = 1;
		}
		output_position();
		output_hero_status();
		if (name_road == "Normal")
		{
			if (temp_special < chance_special)
			{
				rd_status.cout_cps_road++;
				output_notification_about_changed_road();
				head->ChangeToSpc(all_roads);
			}
		}
		output.Trigger_Draw_Hero_Terminal(head, go);
		if (rd_status.cout_cps_road == rd_status.road_len-1)
		{
			output_win();
			break;
		}
		output_step();
		
		name_road = head->Get_Name();
		if (!((rd_status.сurr_loop == 1) && (rd_status.curr_road == 1)))
		{
			head->Play_Event(&hero, output, settings);
		}
		
		if (hero.Get_Hp() <= 0 )
		{
			output.Trigger_Write_Str_Terminal("Герой не справился с испытанием и умер....");
			break;
		}
		int temp_drop = rand()%100;
		

		if ( name_road == "Normal")
		{
			if (temp_drop < chance_drop)
			{
				Armor arm = Drop_Armor();
				output_dropt_arm(arm);
				if (ask_question())
				{
					hero.ChangeArmor(arm);
				}
			}
		}
		else if (name_road != "Start")
		{
				Boots ev_boots = head->Get_Boots();
				if (temp_drop < ev_boots.get_weight())
				{
					output_dropd_boots(ev_boots);
					if (ask_question())
					{
						hero.ChangeBoots(ev_boots);
					}
				}
		}
		this_thread::sleep_for(delay);
		

		output.Trigger_Draw_Hero_Terminal(head, stop);
		head = head->Get_Next();
		if (Screen_Size_Check() == 0)
		{
			break;
		}
		rd_status.curr_road++;
		string end_road_action = "----------------------------";
		output.Trigger_Write_Str_Terminal(end_road_action);
		output.Trigger_Write_Str_Terminal("                                                         ");
		}


	Delete_Path();
}


Road* Game::Get_Head()
{
	return head;
}

void Game::output_win()
{
	string win = "Мои поздравления! Вы встромнили все клетки! Теперь вы сможете найти дорогу домой!";
	string end = "THE END........возможно)";
	output.Trigger_Write_Str_Terminal(win);
	output.Trigger_Write_Str_Terminal(end);
	
}
void Game::output_dropd_boots(Boots _bts)
{
	string drop_boots = "Вам выпали ботинки: " + _bts.Get_Name();
	output.Trigger_Write_Str_Terminal(drop_boots);
}
void Game::output_dropt_arm(Armor _arm)
{
	string drop_boots = "Вам выпал грудак, тип: " + _arm.Get_Type() + ",  def:  " + to_string(_arm.Get_Defense());
	output.Trigger_Write_Str_Terminal(drop_boots);
}



void Game::output_position()
{
	string pos = "Круг " + to_string(rd_status.сurr_loop) + " . Клетка " + to_string(rd_status.curr_road) + "/" + to_string(rd_status.road_len); 
	output.Trigger_Write_Str_Terminal(pos);
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
	output.Trigger_Write_Str_Terminal(stats);
}
void Game::output_notification_about_changed_road()
{
	string def_smen = "Нормальная дорога изменилась...";
	output.Trigger_Write_Str_Terminal(def_smen);
}
void Game::output_step()
{
	string step = "Вы наступили на " + head->Get_Name();
	output.Trigger_Write_Str_Terminal(step);	
}
        




int Game::get_weight(string type)
{
    if (type == "common")
    {
        return 100;
    }
    else if (type == "rare")
    {
        return 20;
    }
    else if (type == "evently")
    {
        return 10;
    }

	return 0;
}


Armor Game::Drop_Armor()
{
    int sum_weight = 0;
    map<string, int> count_types;
    string rarity;
    string raritys[] = {"common", "rare"};
    for(int i = 0; i < default_armor.size(); i++)
    {
        rarity = default_armor[i].Get_Type();
        auto rar_c = count_types.find(rarity);
        if (rar_c != count_types.end())
        {
            (rar_c->second)++;
        }
        else
        {
            count_types.emplace(rarity,1);
        }
        sum_weight+=default_armor[i].get_weight();
    }
    int chance = rand()%sum_weight;
    int j = 0;
    while (chance > 0)
    {
        auto rar_c = count_types.find(raritys[j]);
        int weight_of_rarity = (rar_c->second)*get_weight(raritys[j]);
		chance-=weight_of_rarity;
        j++;
    }
	j--;
	
	int rand_sequr_num = rand()%(count_types.find(raritys[j])->second);

	int k = 0;
	int i = 0;
	while (k < rand_sequr_num)
	{
		if (default_armor[i].Get_Type() == raritys[j])
		{
			k++;
		}
		i++;
	}

    return default_armor[i];

}
int Game::ask_question()
{
	string ask = "Хотите ли надеть? Y/N: ";
	char answer; 
	output.Trigger_Write_Str_Terminal(ask);
	cout << "\033[" << settings.SIZE_BOARDER+settings.ROW_COUNT+3 <<  ";25H";
	answer = input.Trigger_In_Terminal();
	if (answer == 'Y')
	{
		return 1;
	}
	else
	{
		return 0;
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


Road* Game::create_road_from_file(string id_road)
{
	ifstream rfin("../configs/Roads.txt");
	search_id(&rfin, id_road);
	Road* new_type_road = new Road();

	check_left_scope(&rfin);

	string word;

	rfin >> word; // name
	new_type_road->set_name(word);

	rfin >> word; // boots
	
	new_type_road->set_boots(create_boots_from_file(word));

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

	int durabiliry;

	ifin >> word;
	durabiliry = stoi(word);
	
	string name;
	ifin >> name;
	
	check_right_scope(&ifin);
  
	ifin.close();
	Boots bts(rarity, durabiliry, name);


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

	int durabiliry;

	ifin >> word;
	durabiliry = stoi(word);
	
	int defense;
	ifin >> word;
	defense = stoi(word);

	check_right_scope(&ifin);
	Armor arm(rarity, durabiliry, defense);
	ifin.close();

	return arm;
}

Game::Game(string level) 
{
	ifstream fin(level);
	vector<string> names_available_roads;
	if (!fin.is_open())
	{
		cout << "Файл не открылся" << endl;
		exit(1);
	}
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


			
		}
	}


	Armor naked("Default", -1, 0);//Create of hero
	Boots sandals("Default", -1, "Sandals");

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
	
	head = nullptr;
	start = nullptr;
}