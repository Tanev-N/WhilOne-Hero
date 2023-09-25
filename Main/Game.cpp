#include "../Headers/all.h"

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
	if ((new_x < 2) || (new_y < 4) || (new_y > 16) || (new_x > 16)) // Out of bounds check
	{
		return 0;
	}

	Road *move = start;
	int x, y, adjacentcount;
	adjacentcount = 0;
	while (move != nullptr)
	{
		x = move->GetX();
		y = move->GetY();	
		if ((new_x == x)&& (new_y == y)) // Already existing cell check
		{
			return 0;
		}
		else
		{
			if (Check_Plus(x, y, new_x, new_y))
			{
				adjacentcount += 1;
			}	
		}
		if ((adjacentcount > 1) && !((road_len == 1) && (adjacentcount == 2)))
		{
			return 0;
		}
 		move = move->Get_Next();
	} 
	return 1;
}

void Game::Create_Road(void) 
{
	int x, y, step_x, step_y, correct_road_check;
	int road_len;
	int error_counter; // Var on cheak impossible way 
	step_x = step_y = correct_road_check = 0;
	
	Road* temp;
    string name_road = "Normal";
	string start_name = "Start";
	do
	{
		x = (rand() % 14) + 2;
		y = (rand() % 14) + 2;
		road_len = rand() % 11 + 14;
		error_counter = 0;
		if (road_len % 2 == 1)
		{
			road_len += 1;
		}
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
				Normal_Road *newroad;
				newroad = new Normal_Road(x+step_x, y+step_y, name_road);
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
			head = start;
			while(head->Get_Next() != nullptr)
			{
				temp =  head->Get_Next();
				delete head;
				head = temp;
			}
			delete head;
		}
	} while (correct_road_check != 1);
	
	head -> Change_Next(start);
	head = head->Get_Next();
}
void Game::Play(void)
{
    this->Create_Road();
	string go = "Go";
	string stop = "Stop";
	cout << "\033[2J"; // Clear display
	cout <<  "\033[Н";
	//cout << "\033[30;46m" << "\033[5;5Н"  << "lol";
	//cout << "\033[30;47m";
	output.Trigger_Draw_Start_Road_Terminal(start);
	cout << "\033[0m";
	chrono::milliseconds delay(1000);
	cout << endl;
	while(1)
	{
		output.Trigger_Draw_Hero_Terminal(head, go);
		this_thread::sleep_for(delay);
		output.Trigger_Draw_Hero_Terminal(head, stop);
		head = head->Get_Next();
	}
	cout << "\n\n\n\n\n\n\n\n\n";
	
	// debuf print:
	int i = 1;
    while(head->Get_Next() != start )
   {
        cout << "Cell number " << i << " position " << head->GetX() << " " << head->GetY() << endl;
        i++;
       head = head->Get_Next();
    }
	cout << "Cell number " << i << " position " << head->GetX() << " " << head->GetY() << endl;
	head = head->Get_Next();
    //end print
}
Road* Game::Get_Head()
{
	return head;
}

Game::Game() : hero(), input(), output()
{
	head = nullptr;
	start = nullptr;

}