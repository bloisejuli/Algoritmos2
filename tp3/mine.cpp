#include "mine.h"

Mine::Mine(string building_type, string material_that_produces, string icon, int x_coordinate, int y_coordinate, Player* owner) :
          Building(building_type, material_that_produces, icon, x_coordinate, y_coordinate, owner) {

  damaged = false;

}

void Mine::produce_material() {

  accumulated_produced_material += STONE_PROVIDED_BY_MINE;

}

void Mine::damage_building() {

  damaged = true;

}

void Mine::repair_building() {

  damaged = false;

}

bool Mine::get_building_state() {

  return damaged;

}
