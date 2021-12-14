#ifndef EMPTY_PASSABLE_TILES_H
#define EMPTY_PASSABLE_TILES_H

#include "list.h"
#include <stdlib.h>
#include <time.h>

struct EmptyTile {
  int x_coordinate = 0;
  int y_coordinate = 0;
};

class EmptyPassableTiles{

private:
  List<EmptyTile>* passable_tiles;
  int total_of_tiles;

public:

  //PRE: -
  //POS: Creates a EmptyPassableTiles object,  with a list of EmptyTile
  //     and initializes 'total_of_tiles' = 0.
  EmptyPassableTiles();

  //PRE: -
  //POS: Destroys EmptyPassableTiles object and calls the destructor of the list.
  ~EmptyPassableTiles();

  //PRE: -
  //POS: Creates a new EmptyTile, adds it to the list and total_of_tiles++.
  void add_empty_tile(int x_coordinate, int y_coordinate);

  //PRE: -
  //POS: Returns 'total_of_tiles' == 0.
  bool not_empty_tiles();

  //PRE: -
  //POS: Picks a random passable tile of the list, if the list is empty returns false.
  bool select_random_tile();

  //PRE: -
  //POS: Returns x coordinate of passable tile.
  int get_target_tile_x_coordinate();

  //PRE: -
  //POS: Returns y coordinate of passable tile.
  int get_target_tile_y_coordinate();

  //PRE: -
  //POS: Removes tile from the list and total_of_tiles--.
  void delete_target_tile();

  //PRE: -
  //POS: Removes the tile from the list that has the coordinates received by parameter.
  void search_tile(int x_coordinate, int y_coordinate);

};

#endif //EMPTY_PASSABLE_TILES_H
