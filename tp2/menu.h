#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <fstream>
#include "city.h"
#include "building.h"

using namespace std;

class Menu {

public:

  //PRE:-
  //POS: Shows on screen options menu. 
  void show_menu();

  //PRE: City must be a non-null pointer.
  //POS: Returns false if the user decides to exit and save, and true if they continue playing.
  bool interpretate_user_input(City* city);

private:

  //PRE:-
  //POS: Shows on screen a Cobra car. (reference to Age of Empires II)
  void how_do_you_turn_this_on();

  //PRE:-
  //POS: Asks the user to press enter to return to the menu.
  void press_enter_to_continue();

  //PRE: 'city' must be a valid City class pointer.
  //POS: Asks the user for type of building and coordinates where he wants to build it and then calls 
  //     city method add building.
  void build(City* city);

  //PRE: 'city' must be a valid City class pointer.
  //POS: Asks the user for coordinates of the building and then calls city method to demolish it.
  void demolish(City* city);

  //PRE: 'city' must be a valid City class pointer.
  //POS: Updates the files with the new information from the program.
  void save_data(City* city);

  //PRE: 'city' must be a valid City class pointer.
  //POS: Asks user for a valid x coordinate and returns it.
  int ask_user_x_coordinate(City* city);

  //PRE: 'city' must be a valid City class pointer.
  //POS: Asks user for a valid y coordinate and returns it.
  int ask_user_y_coordinate(City* city);


};


#endif //MENU_H
