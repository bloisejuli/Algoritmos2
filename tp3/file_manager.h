#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <iostream>
#include <fstream>
#include "city.h"
#include "player.h"
#include "graph.h"
#include "utils.h"

using namespace std;

class FileManager {

public:

  //PRE: -
  //POS: -
  FileManager();

  //PRE: 'city' must be a valid City pointer.
  //POS: Loads materials from MATERIAL_FILE_ROUTE
  void load_materials(Player* player_1, Player* player_2);

  // void load_default_materials(City* city);
  void load_default_materials(Player* player_1, Player* player_2);

  //PRE: 'city' must be a valid City pointer.
  //POS: Loads buildings from BUILDING_FILE_ROUTE
  void load_buildings_attributes(City* city);

  //PRE: 'city' must be a valid City pointer.
  //POS: Loads buildings and materials from MAP_LOCATIONS_ROUTE and returns true if there wasn't any error,
  //     otherwise returns false.
  bool load_buildings(City* city, Player* player_1, Player* player_2);

  //PRE: 'city' must be a valid City pointer.
  //POS: Loads tiles from MAP_FILE_ROUTE
  void load_tiles(City* city, Graph* graph_player_1, Graph* graph_player_2);
};

#endif //FILE_MANAGER_H
