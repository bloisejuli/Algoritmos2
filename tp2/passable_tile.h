#ifndef PASSABLE_TILE_H
#define PASSABLE_TILE_H

#include "tile.h"
#include "material.h"

class PassableTile : public Tile {
private:
    Material* material_contained;


public:

  //PRE:-
  //POS: Creates a PassableTile object and points the pointer 'material_contained' to null   
  PassableTile();

  //PRE:-
  //POS: Destroys PassableTile object and calls the destructor of the object contained.    
  ~PassableTile();

  //PRE:-
  //POS: Assigns 'material' to 'material_contained'.
  void add_material(Material* material);

  //PRE:-
  //POS: Points pointer 'material_contained' to null. 
  void remove_material();

  //PRE:-
  //POS: Informs on screen what type of tile is the one being consulted and if it is empty, otherwise 
  //     it shows building type that it contains.
  void show();

  //PRE:-
  //POS:  Returns 'material_contained' == 0.
  bool tile_empty();

  //PRE:-
  //POS: Returns 'EMPTY' if 'building_contained' is empty or 'OCCUPIED' if not.
  string state_of_tile();

  //PRE:-
  //POS: Returns the building type contained in the tile.
  string get_value();

  //PRE:-
  //POS: Returns 'PASSABLE'.
  string get_tile_class();

};

#endif // PASSABLE_TILE_H
