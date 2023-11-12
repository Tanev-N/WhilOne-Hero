#ifndef GAME
#define GAME

#include <vector>
#include <sys/ioctl.h>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <fstream>
#include <list>

#include "cell.h"
#include "creature.h"
#include "controller.h"
#include "game_data.h"

struct road_status
{
    int curr_loop;
    int curr_road;
    int road_len; 
    int cout_spc_road;
    road_status();
};

class Game 
{
    private:
        road_status rd_status;
        Hero hero;
        vector<Road*> all_roads;
        vector<Armor> default_armor;
        list<Road> path;
        Input_Controller input;
        Output_Controller output;
        game_data settings;
    public:
        Game(const string&);
        void Play();
        int Make_Step();
        int Step_Check(int, int, int);
        void Create_Path();
        int Check_Plus(int, int, int, int);
        int Get_Size_Row() const;
        int Get_Size_Column() const;
        int Screen_Size_Check();
        void check_left_scope(ifstream*);
		void fill_game_int_setting(ifstream*, string);
		void check_right_scope(ifstream*);
        Road* create_road_from_file(string);
        Armor create_armor_from_file(string);
        Boots create_boots_from_file(string);
        void search_id(ifstream* , string );
        int ask_question();
        Armor Drop_Armor();
        static int get_weight(const string&) ;
        void output_position();
        void output_hero_status();
        void output_notification_about_changed_road();
        void output_step(list<Road>::iterator);
        void output_win();
        void output_lose();
        void output_droped_boots(Boots);
        void output_droped_arm(Armor);
};



#endif