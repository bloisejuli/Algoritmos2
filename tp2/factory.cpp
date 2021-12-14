#include "factory.h"

Factory::Factory(string building_type, string material_that_produces, int x_coordinate, int y_coordinate) :
          Building(building_type, material_that_produces, x_coordinate, y_coordinate) {}

int Factory::produce_material() {

  return STEEL_PROVIDED_BY_FACTORY;

}
