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
	if ((new_x < 2) || (new_y < 4) || (new_y > SIZE_BOARDER) || (new_x > SIZE_BOARDER)) // Out of bounds check
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

void Game::Create_Path() 
{
	int x, y, step_x, step_y, correct_road_check;
	int road_len;
	int error_counter; // Var on cheak impossible way 


	step_x = step_y = correct_road_check = 0;
    string name_road = "Normal";
	string start_name = "Start";


	do
	{
		x = (rand() % SIZE_BOARDER) + 2; // Coordinates of start road
		y = (rand() % SIZE_BOARDER) + 2;

		road_len = rand() % (MAX_LEN_ROAD - MIN_LEN_ROAD) + MIN_LEN_ROAD;

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
}

int Game::Get_Size_Row()
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	return(w.ws_col);
}

int Game::Get_Size_Column()
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	return(w.ws_col);
}

void Game::Change_Screen_Size(int y, int x)
{
	struct winsize w;
	w.ws_col = y;
	w.ws_row = x;
	ioctl(0, TIOCSWINSZ, &w);
	return();
}

int Game::Screen_Size_Check()
{
	int row, column;
	row = Get_Size_Row();
	column = Get_Size_Column();
	if ((row < 20) && (column < 40))
	{
		return(0);
	}
	return(1);
}


void Game::Play()
{
    this->Create_Path(); 

	string go = "Go";
	string stop = "Stop";

	cout << "\033[2J"; // Clear display
	Change_Screen_Size(60, 40);
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
		if (Screen_Size_Check() == 0)
		{
			break;
		}
	}
	int i = 1;
    while(head->Get_Next() != start )
   {
        cout << "Cell number " << i << " position " << head->GetX() << " " << head->GetY() << endl;
        i++;
       head = head->Get_Next();
    }
	cout << "Cell number " << i << " position " << head->GetX() << " " << head->GetY() << endl;
	head = head->Get_Next();
	Delete_Path()
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