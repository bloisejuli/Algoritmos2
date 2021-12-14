#ifndef BUILDING_H
#define BUILDING_H
#include <iostream>
#include <fstream>
#include "constants.h"
using namespace std;

class Building{
private:
  string building_type;
  string material_that_produces;
  int x_coordinate;
  int y_coordinate;

public:
  //PRE: -
  //POS: Creates Building object initializing its attributes with the values ​​received by parameter.
  Building(string building_type, string material_that_produces, int x_coordinate, int y_coordinate);

  //PRE:-
  //POS:-
  virtual ~Building() {};

  //PRE: 'new_type' must be a valid type.
  //POS: Assigns building_type to 'new_type'.
  void set_type(string new_type);

  //PRE:-
  //POS: Returns building_type.
  string get_type();

  //PRE:-
  //POS: Returns 'x_coordinate'.
  int get_x_coordinate();

  //PRE:-
  //POS: Returns 'y_coordinate'.
  int get_y_coordinate();

  //PRE:-
  //POS: Returns 0.
  virtual int produce_material();

  //PRE:-
  //POS: Returns 'material_that_produces'.
  string get_material_that_building_produces();

};

#endif //BUILDING_H
