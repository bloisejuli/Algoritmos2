#ifndef BUILDABLE_TILE_H
#define BUILDABLE_TILE_H

#include "tile.h"
#include "building.h"

class BuildableTile : public Tile {
private:
    Building* building_contained;

public:

  //PRE:-
  //POS: Creates a BuildableTile object and points the pointer 'building_contained' to null   
  BuildableTile();

  //PRE:-
  //POS: Assigns 'building' to 'building_contained'.
  void add_building(Building* building);

  //PRE:-
  //POS: Points pointer 'building_contained' to null. 
  void remove_building();

  //PRE:-
  //POS: Informs on screen what type of tile is the one being consulted and if it is empty, otherwise 
  //     it shows building type that it contains.
  void show();

  //PRE:-
  //POS: Returns 'building_contained' == 0.
  bool tile_empty();

  //PRE:-
  //POS: Returns 'EMPTY' if 'building_contained' is empty or 'OCCUPIED' if not.
  string state_of_tile();

  //PRE:-
  //POS: Returns the building type contained in the tile.
  string get_value();

  //PRE:-
  //POS: Returns 'BULDABLE'.
  string get_tile_class();

};

#endif //BUILDABLE_TILE_H
