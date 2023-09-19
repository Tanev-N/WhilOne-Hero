#include "../Headers/ALL.h"

int Make_Step(int Cord)
{
	int Step;
	Step = rand() % 2;
    	if (Step == 0)
    	{
		Cord += 1;
    	}
	else
	{
		Cord -= 1;
	}
    	return (Cord);
}

int Step_Check(int Newx, int Newy, Road *Start)
{
	Road *Move = Start;
	int x, y, AdjacentCount;
	AdjacentCount = 0;
	do
	{
		x = Move->GetX();
		y = Move->GetY();	
		if ((Newx == x)	&& (Newy == y))
		{
			return 0;
		}
		else
		{
			if ((Newx + 1 == x) || (Newx - 1 == x) || (Newy + 1 == y) || (Newx - 1 == y))
			{
				AdjacentCount += 1;
			}	
		}
		if (AdjacentCount != 1)
		{
			return 0;
		}
	} while	((Move->Get_Next()) != NULL);
	return 1;
}

Road* Create_Road(void)
{
	int x, y, Stepx, Stepy, Side, Check, CorrectRoadCheck;
	int RoadCount = rand() % 11 + 14;
	if (RoadCount % 2 == 1)
	{
		RoadCount += 1;
	}
	x = y = Stepx = Stepy = CorrectRoadCheck = 0;
	Normal_Road *NewRoad;
    string name_road = "Normal_Road";
	Road *Start = new Road(x,y,name_road);
	Road *Head = Start;
	do
	{
		Head = Start;
		do
		{
			if (rand() % 2) 
			{
				Stepx = Make_Step(x);
			}
			else
			{
				Stepy = Make_Step(y);
			}
			if (Step_Check(x+Stepx, y+Stepy, Start) == 1)
			{
				NewRoad = new Normal_Road(x+Stepx, y+Stepy, name_road);
				Head->Change_Next(NewRoad);	
				Head = NewRoad;
				RoadCount -= 1;
			}
			Stepx = Stepy = 0;
		} while (RoadCount != 0);
		if ((abs(Head->GetX() - Start->GetX()) == 1) || (abs(Head->GetY() - Start->GetY()) == 1))
		{
			CorrectRoadCheck = 1;
		}
	} while (CorrectRoadCheck != 1);
	
}
