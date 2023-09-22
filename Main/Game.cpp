#include "../Headers/ALL.h"

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

int Game::Step_Check(int newx, int newy, int roadcount)
{
	if ((newx < 2) || (newy < 2) || (newy > 16) || (newx > 16))
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
		if ((newx == x)	&& (newy == y))
		{
			return 0;
		}
		else
		{
			if (((newx + 1 == x) && (newy == y)) || ((newx - 1 == x) && (newy == y)) || ((newy + 1 == y) && (newx == x)) || ((newy - 1 == y) && (newx == x)))
			{
				adjacentcount += 1;
			}	
		}
		if ((adjacentcount > 1) && !((roadcount == 1) && (adjacentcount == 2)))
		{
			return 0;
		}
 		move = move->Get_Next();
	} 
	return 1;
}

void Game::Create_Road(void)
{
	int x, y, stepx, stepy, side, check, correct_road_check;
	int roadcount = rand()%11+14;
	int error_check = 0;
	if (roadcount % 2 == 1)
	{
		roadcount += 1;
	}
	stepx = stepy = correct_road_check = 0;
	x = (rand() % 14) + 2;
	y = (rand() % 14) + 2;
	Normal_Road *newroad;
	Road* temp;
    string name_road = "Normal_Road";
	start = new Road(x, y, name_road);
	roadcount--;
	do
	{
		head = start;
		do
		{
			if (rand() % 2) 
			{
				stepx = this->Make_Step();
			}
			else
			{
				stepy = this->Make_Step();
			}
			if (this->Step_Check(x+stepx, y+stepy, roadcount) == 1)
			{
				newroad = new Normal_Road(x+stepx, y+stepy, name_road);
				head->Change_Next(newroad);	
				head = head->Get_Next();
				roadcount -= 1;
				x += stepx;
				y += stepy;
				error_check = 0;
			}
			else
			{
				error_check += 1;
			}
			if (error_check > 10)
			{
				break;
			}
			stepx = stepy = 0;
		} while ((roadcount != 0));
		//if (((((newx + 1 == x) && (newy == y)) || ((newx - 1 == x) && (newy == y)) || ((newy + 1 == y) && (newx == x)) || ( (newy - 1 == y) && (newx == x) ) ) ) && (error_check < 10) )
		if ( ( ( abs(head->GetX() - start->GetX()) == 1) && (head->GetY() == start->GetY()) ) || ((abs(head->GetY() - start->GetY()) == 1) && (head->GetX() == start->GetX())))
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
			x = (rand() % 14) + 2;
			y = (rand() % 14) + 2;
			roadcount = rand() % 11 + 14;
			error_check = 0;
			if (roadcount % 2 == 1)
			{
				roadcount += 1;
			}
			start = new Road(x, y, name_road);
			roadcount--;
		}
	} while (correct_road_check != 1);
	
	head -> Change_Next(start);
	head = head->Get_Next();
}
void Game::Play(void)
{

    this->Create_Road();
    int i = 1;
	// debuf print:
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

Game::Game() : hero()
{
	head = nullptr;
	start = nullptr;

}