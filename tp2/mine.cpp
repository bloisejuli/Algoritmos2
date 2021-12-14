#include "mine.h"

Mine::Mine(string building_type, string material_that_produces, int x_coordinate, int y_coordinate) :
          Building(building_type, material_that_produces, x_coordinate, y_coordinate) {}

int Mine::produce_material() {

  return STONE_PROVIDED_BY_MINE;

}
