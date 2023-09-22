#include "../Headers/ALL.h"

int Make_Step(int cord)
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

int Step_Check(int newx, int newy, Road *start)
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
	} while	((move->Get_Next()) != NULL);
	return 1;
}

Road* Create_Road(void)
{
	int x, y, stepx, stepy, side, check, correctroadcheck;
	int roadcount = rand() % 11 + 14;
	if (roadcount % 2 == 1)
	{
		roadcount += 1;
	}
	x = y = stepx = stepy = correctroadcheck = 0;
	Normal_Road *newroad;
    string name_road = "Normal_Road";
	Road *start = new Road(x,y,name_road);
	Road *head = start;
	do
	{
		head = start;
		do
		{
			if (rand() % 2) 
			{
				stepx = Make_Step(x);
			}
			else
			{
				stepy = Make_Step(y);
			}
			if (Step_Check(x+stepx, y+stepy, start) == 1)
			{
				newroad = new Normal_Road(x+stepx, y+stepy, name_road);
				head->Change_Next(newroad);	
				head = newroad;
				roadcount -= 1;
			}
			stepx = stepy = 0;
		} while (roadcount != 0);
		if ((abs(head->GetX() - start->GetX()) == 1) || (abs(head->GetY() - start->GetY()) == 1))
		{
			correctroadcheck = 1;
		}
	} while (correctroadcheck != 1);
	
}
