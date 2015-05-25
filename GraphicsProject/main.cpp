#include <iostream>


#include <functional>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>

#define clrscr move_to(0,0)<<color(defColor)<<box(XX-1,YY-1)

#include "GameMaster.h"
#include "w_App.h"

using namespace genv;
const unsigned int X=500, Y=500;
using namespace std;

int main()
{
    GM Game(4,7);
    Game.set_cursor(6);
    Game.drop_chip();
    Game.set_cursor(5);
    Game.drop_chip();
    Game.drop_chip();
    Game.set_cursor(3);
    Game.drop_chip();
    Game.drop_chip();
    Game.drop_chip();
    Game.drop_chip();
    Game.set_cursor(4);
    Game.drop_chip();
    Game.drop_chip();
    Game.set_cursor(1);
    Game.drop_chip();
    Game.set_cursor(4);
    Game.drop_chip();

    Game.print();
    Game.check_win();
    cout<<Game.interrupt;
    return 0;
}
