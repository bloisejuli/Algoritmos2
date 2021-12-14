#ifndef BUILDING_H
#define BUILDING_H
#include <iostream>
#include <fstream>
#include "constants.h"
#include "player.h"
using namespace std;

class Building{
protected:
  string building_type;
  string material_that_produces;
  string icon_building;
  int accumulated_produced_material;
  int x_coordinate;
  int y_coordinate;
  Player* owner;

public:
  //PRE: -
  //POS: Creates Building object initializing its attributes with the values ​​received by parameter.
  Building(string building_type, string material_that_produces, string icon_building, int x_coordinate, int y_coordinate, Player* owner);

  //PRE:-
  //POS: Destroys Building.
  virtual ~Building() {};

  //PRE:-
  //POS: Returns building_type.
  string get_type();

  //PRE:-
  //POS: Returns 'x_coordinate'.
  int get_x_coordinate();

  //PRE: -
  //POS: Returns 'y_coordinate'.
  int get_y_coordinate();

  //PRE: -
  //POS: -
  virtual void produce_material();

  //PRE: -
  //POS: Returns amount produced.
  int collect_material();

  //PRE: -
  //POS: Returns 'material_that_produces'.
  string get_material_type();

  //PRE: -
  //POS: Returns 'icon_building'.
  string get_icon_building();

  //PRE: -
  //POS: Returns 'owner'.
  Player* get_owner();

};

#endif //BUILDING_H
