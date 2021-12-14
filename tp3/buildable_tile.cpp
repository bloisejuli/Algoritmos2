#include "buildable_tile.h"

BuildableTile::BuildableTile() {
  player_on_it = 0;
  building_contained = 0;
}

void BuildableTile::add_building(Building* building) {
  building_contained = building;
}

Building* BuildableTile::get_building() {
  return building_contained;
}

void BuildableTile::remove_building() {
  building_contained = 0;
}

void BuildableTile::show(Player* player_1, Player* player_2) { 
  cout << "Consulted tile is " << BOLD_BLUE << BUILDABLE << DEFAULT_COLOR << " and is ";

  if (tile_empty())
   cout << BOLD_GREEN << state_of_tile() << DEFAULT_COLOR << '\n';
  else {
    string building_owner;
    int current_player = building_contained->get_owner()->get_id();

    if (building_contained->get_owner() == player_1)
      building_owner = PLAYER_ONE;

    else if (building_contained->get_owner() == player_2)
      building_owner = PLAYER_TWO;

    cout << BOLD_RED << state_of_tile() << DEFAULT_COLOR << ", contains building: " << BOLD_GREEN <<
            building_contained->get_type() << DEFAULT_COLOR << ", from player: " <<
            get_player_color(current_player) << building_owner << DEFAULT_COLOR << '\n';
  }
}

bool BuildableTile::tile_empty() {
  bool empty_tile = false;

  if(building_contained == 0 && player_on_it == 0)
    empty_tile = true;

  return empty_tile;
}

string BuildableTile::state_of_tile() {
  if (tile_empty())
    return EMPTY;

  return OCCUPIED;
}

string BuildableTile::get_value() {
  if(building_contained != 0)
    return building_contained->get_type();
  else {  
    return "";
  }
}

string BuildableTile::get_tile_class() {
  return BUILDABLE;
}

Player* BuildableTile::get_building_owner() {
  return building_contained->get_owner();
}
