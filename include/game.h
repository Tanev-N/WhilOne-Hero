#ifndef GAME
#define GAME

#include <vector>
#include <sys/ioctl.h>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <fstream>

#include "cell.h"
#include "creature.h"
#include "controller.h"
#include "game_data.h"

struct road_status
{
    int сurr_loop;
    int curr_road;
    int road_len; 
    int cout_cps_road;
};

class Game 
{
    private:
        road_status rd_status;
        Hero hero;
        vector<Road*> all_roads;
        vector<Armor> default_armor;
        Road* head;
        Road* start;
        Input_Controller input;
        Output_Controller output;
        game_data settings;
    public:
        Game(string);
        void Play();
        int Make_Step();
        int Step_Check(int, int, int);
        int Create_Path();
        Road* Get_Head();
        int Check_Plus(int, int, int, int);
        void Delete_Path();
        int Get_Size_Row();
        int Get_Size_Column();
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
        int get_weight(string);
        void output_position();
        void output_hero_status();
        void output_notification_about_changed_road();
        void output_step();
        void output_win();
        void output_lose();
        void output_dropd_boots(Boots);
        void output_dropt_arm(Armor);
};



#endif