#include "factory.h"

Factory::Factory(string building_type, string material_that_produces, string icon, int x_coordinate, int y_coordinate, Player* owner) :
          Building(building_type, material_that_produces, icon, x_coordinate, y_coordinate, owner) {

  damaged = false;

}


void Factory::produce_material() {

  accumulated_produced_material += STEEL_PROVIDED_BY_FACTORY;

}

void Factory::damage_building() {

  damaged = true;

}

void Factory::repair_building() {

  damaged = false;

}

bool Factory::get_building_state() {

  return damaged;

}
