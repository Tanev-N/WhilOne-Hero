# ***WhilOne-Hero***

## Essence of game

  The hero must change all the cells of the road to special ones. In order not to lose before this happens, 
he must collect the armor and weapons he found on the way, which will help him in battles against monsters and when passing
through difficult terrain. When all the cells of the road are changed to special ones on the first
level, the second one begins. After the second, the third. After the third, the game is considered
completed, and the player is the winner.



## Game process

<img src='https://github.com/Tanev-N/WhilOne-Hero/blob/main/docs/game.gif'/>

  At startup, the program starts generating roads according to a predetermined
algorithm and, when it reaches the desired result, displays it on the screen, starting
the direct game. The terminal clears and a map of the area
appears on the top left, below it a message about the circle, the current cell and the event on it. When
the player moves on the map, the sign of the head (hero) will move, when
the cell changes, it will be repainted in the appropriate color on the map.
Ordinary cells have a chance to turn into one of the unusual cells,
which are listed in the corresponding file of the current level. Special
cells have a chance of shoes falling out, which affects the outcome of the event
taking place on them. If the player has them, he restores
his health. If not, he loses it. In addition, 
different weapons drop out on each type of cell and different monsters appear.
If the player has found an item, then he can put it on (if he does not have such a piece
of equipment, if there is, then he can either replace it or not take it at all, prescribing
**Y/N**, respectively.) Items have durability, which, when reaching zero
during a fight or an event on the cage, it will mean a breakdown of equipment.
On the road, when the hero reaches the initial cell,
monsters begin to appear. When meeting a monster on its way, the game character will start a fight with it,
in which the opponents will exchange blows. The
speed of the hero and the monster is responsible for how fast the blow is struck. For the damage done, strength. For preventing damage, protection. 
The characteristics of the hero can increase depending on 4
from the equipment he's wearing. If the hero loses, the program terminates its work. In case of victory, the hero is awarded experience points.
If their sum becomes equal to or greater than a certain number, the hero's level
will increase, and he will fully restore his health.
If the hero's HP drops to 0, then the program ends with an inscription about
the loss, otherwise, if all the cells become unusual, the program moves
to the next level or ends with an inscription about the victory, if the completed
level was the last.

## Installation

```
git clone https://github.com/Tanev-N/WhilOne-Hero
cd build
cmake ..
make
```
<img src='https://github.com/Tanev-N/WhilOne-Hero/blob/main/docs/build.gif'/>

##  Requirements

+ C++ 17
+ Unix
+ Git
