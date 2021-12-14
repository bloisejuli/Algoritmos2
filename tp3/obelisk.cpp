#include "obelisk.h"

Obelisk::Obelisk(string building_type, string material_that_produces, string icon, int x_coordinate, int y_coordinate, Player* owner) :
          Building(building_type, material_that_produces, icon, x_coordinate, y_coordinate, owner) {}
