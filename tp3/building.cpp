#include "building.h"

Building::Building(string building_type, string material_that_produces, string icon_building, int x_coordinate, int y_coordinate, Player* owner) {
  this->building_type = building_type;
  this->material_that_produces = material_that_produces;
  this->icon_building = icon_building;
  this->x_coordinate = x_coordinate;
  this->y_coordinate = y_coordinate;
  this->accumulated_produced_material = 0;
  this->owner = owner;
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

void Building::produce_material() {}

int Building::collect_material() {
  int amount_produced = accumulated_produced_material;
  accumulated_produced_material = 0;

  return amount_produced;
}

string Building::get_material_type() {
  return material_that_produces;
}

string Building::get_icon_building() {
  return icon_building;
}

Player* Building::get_owner() {
  return owner;
}
