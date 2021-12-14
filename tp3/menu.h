#ifndef MENU_H
#define MENU_H
#include "utils.h"

using namespace std;

class Menu {

public:
  //PRE: -
  //POS: Shows on screen game options menu.
  void show_new_game_menu();

  //PRE: -
  //POS: Shows on screen game options menu.
  void show_game_menu(int player_number, int player_energy);

  //PRE: -
  //POS: Asks the user to press enter to return to the menu.
  void press_enter_to_continue(bool not_previous_input);

  //PRE: -
  //POS: Asks user to press enter to end game.
  void press_enter_to_end_game();
};

#endif //MENU_H
