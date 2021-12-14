#include "game.h"
//#include <ncurses.h>

using namespace std;

int main() {

  system (CLR_SCREEN);

  srand ((unsigned int)time(NULL));

  Game battle_for_the_obelisk;

  battle_for_the_obelisk.start_game();

  return 0;

}
