#include "passable_tile.h"

PassableTile::PassableTile () {
  
  material_contained = 0;

}

void PassableTile::add_material(Material* material) {

  material_contained = material;

}

void PassableTile::remove_material() {

  delete material_contained;
  material_contained = 0;

}

void PassableTile::show() {

  cout << "Consulted tile is " << BOLD_BLUE << PASSABLE << DEFAULT_COLOR << " and is ";

   if (tile_empty())
       cout << BOLD_GREEN << state_of_tile() << DEFAULT_COLOR << '\n';

   else
       cout << BOLD_RED << state_of_tile() << DEFAULT_COLOR << ", it contains a: " <<
                BOLD_GREEN << material_contained->get_material() << DEFAULT_COLOR << '\n';

}

string PassableTile::get_value() {

  return material_contained->get_material();

}

bool PassableTile::tile_empty() {

  if (material_contained == 0)
    return true;

  return false;

}

string PassableTile::state_of_tile() {

  if (tile_empty())
    return EMPTY;

  return OCCUPIED;

}

string PassableTile::get_tile_class() {

  return PASSABLE;

}

PassableTile::~PassableTile() {
  
  if (material_contained != 0)
    delete material_contained;

}
