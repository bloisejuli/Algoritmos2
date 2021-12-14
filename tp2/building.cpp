#include "building.h"

Building::Building(string building_type, string material_that_produces, int x_coordinate, int y_coordinate) {

  this->building_type = building_type;
  this->material_that_produces = material_that_produces;
  this->x_coordinate = x_coordinate;
  this->y_coordinate = y_coordinate;

}

void Building::set_type(string new_type) {

  building_type = new_type;

}

string Building::get_type() { 

  return building_type;

}


int Building::get_x_coordinate() {

  return x_coordinate;

}

int Building::get_y_coordinate() {

  return y_coordinate;

}

int Building::produce_material() {

  return 0;

}

string Building::get_material_that_building_produces() {

  return material_that_produces;
}