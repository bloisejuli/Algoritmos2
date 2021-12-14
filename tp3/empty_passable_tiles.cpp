#include "empty_passable_tiles.h"

EmptyPassableTiles::EmptyPassableTiles() {
  passable_tiles = new List<EmptyTile>;
  total_of_tiles = 0;
}

void EmptyPassableTiles::add_empty_tile(int x_coordinate, int y_coordinate) {
  EmptyTile* new_tile = new EmptyTile{x_coordinate, y_coordinate};
  passable_tiles->add_node(new_tile);
  total_of_tiles++;
}

bool EmptyPassableTiles::not_empty_tiles() {
  return total_of_tiles == 0;
}

bool EmptyPassableTiles::select_random_tile() {
  if (total_of_tiles > 0) {
    int random_tile = rand() % total_of_tiles;
    passable_tiles->reset_current_node();

    for (int i = 0; i < random_tile; i++) {
      passable_tiles->next_node();
    }
    return true;
  }
  return false;
}

int EmptyPassableTiles::get_target_tile_x_coordinate() {
  return passable_tiles->get_current_value()->x_coordinate;
}

int EmptyPassableTiles::get_target_tile_y_coordinate() {
    return passable_tiles->get_current_value()->y_coordinate;
}

void EmptyPassableTiles::delete_target_tile() {
  passable_tiles->delete_current_node();
  total_of_tiles--;

}

void EmptyPassableTiles::search_tile(int x_coordinate, int y_coordinate) {
  bool tile_found = false;
  passable_tiles->reset_current_node();

  while (!not_empty_tiles() && !tile_found) {
    if (passable_tiles->get_current_value()->x_coordinate == x_coordinate &&
         passable_tiles->get_current_value()->y_coordinate == y_coordinate) {

        passable_tiles->delete_current_node();
        total_of_tiles--;
        tile_found = true;
    }
    passable_tiles->next_node();
  }
}

EmptyPassableTiles::~EmptyPassableTiles() {
  delete passable_tiles;
}
