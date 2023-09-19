#include "../Headers/ALL.h"

void play(void)
{
    Road *Start = Create_Road();
    Road *Head = Start;

    int i = 1;

    while((Head->Get_Next()) != Start )
    {
        cout << "Cell number " << i << "position " << Head->GetX() << " " << Head-> GetY() << '\n';
        i++;
        Head = Head->Get_Next();
    }
    


}