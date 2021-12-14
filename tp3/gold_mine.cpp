#include "gold_mine.h"

GoldMine::GoldMine(string building_type, string material_that_produces, string icon, int x_coordinate, int y_coordinate, Player* owner) :
          Building(building_type, material_that_produces, icon, x_coordinate, y_coordinate, owner) {}

void GoldMine::produce_material() {

  accumulated_produced_material += GOLD_PROVIDED_BY_GOLD_MINE;

}
