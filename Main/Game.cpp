#include "../Headers/ALL.h"

int Game::Make_Step(int cord)
{
	int step;
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

int Game::Step_Check(int newx, int newy)
{
	Road *move = start;
	int x, y, adjacentcount;
	adjacentcount = 0;

	do
	{
		x = move->GetX();
		y = move->GetY();	
		if ((newx == x)	&& (newy == y))
		{
			return 0;
		}
		else
		{
			if ((newx + 1 == x) || (newx - 1 == x) || (newy + 1 == y) || (newx - 1 == y))
			{
				adjacentcount += 1;
			}	
		}
		if (adjacentcount != 1)
		{
			return 0;
		}

	} while	((move->Get_Next()) != nullptr);

	return 1;
}

void Game::Create_Road(void)
{
	int x, y, stepx, stepy, side, check, correct_road_check;
	int roadcount = rand() % 11 + 14;
	if (roadcount % 2 == 1)
	{
		roadcount += 1;
	}
	x = y = stepx = stepy = correct_road_check = 0;
	Normal_Road *newroad;
	Road* temp;
    string name_road = "Normal_Road";
	start = new Road(x, y, name_road);
	head = start;
	do
	{
		head = start;
		do
		{
			if (rand() % 2) 
			{
				stepx = this->Make_Step(x);
			}
			else
			{
				stepy = this->Make_Step(y);
			}
			if (this->Step_Check(x+stepx, y+stepy) == 1)
			{
				newroad = new Normal_Road(x+stepx, y+stepy, name_road);
				head->Change_Next(newroad);	
				head = head->Get_Next();
				roadcount -= 1;
			}
			stepx = stepy = 0;
		} while (roadcount != 0);
		if ((abs(head->GetX() - start->GetX()) == 1) || (abs(head->GetY() - start->GetY()) == 1))
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
		}
	} while (correct_road_check != 1);
	
	head = start;
}
void Game::Play(void)
{

    this->Create_Road();
    int i = 1;

    while(head->Get_Next() != start )
    {
        cout << "Cell number " << i << " position " << head->GetX() << " " << head->GetY() << endl;;
        i++;
        head = head->Get_Next();
    }
	head = head->Get_Next();
    
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