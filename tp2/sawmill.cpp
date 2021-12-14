#include "sawmill.h"

Sawmill::Sawmill(string building_type, string material_that_produces, int x_coordinate, int y_coordinate) :
          Building(building_type, material_that_produces, x_coordinate, y_coordinate) {}

int Sawmill::produce_material() {

  return WOOD_PROVIDED_BY_SAWMILL;

}
