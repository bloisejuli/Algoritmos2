#ifndef BUILDING_HANDLER_H
#define BUILDING_HANDLER_H
#include "list.h"
#include "building.h"
#include "factory.h"
#include "mine.h"
#include "obelisk.h"
#include "power_plant.h"
#include "sawmill.h"
#include "school.h"
#include "gold_mine.h"

using namespace std;

class BuildingHandler {

private:
  List<Building>* buildings;

public:
  //PRE:-
  //POS: Creates a BuildingHandler object, with an empty list.
  BuildingHandler();

  //PRE:-
  //POS: Destroys BuildingHandler object and calls the destructor of the list.
  ~BuildingHandler();

  //PRE: 'building_type' must be a valid building type. 'material_that_produce' must be a valid material type.
  //     'x_coordinate' and 'y_coordinate' must be valid map coordinates.
  //POS: Creates a new Building object and adds it to the list.
  void add_building(string building_type, string material_that_produce, string icon_building, int x_coordinate, int y_coordinate, Player* current_player);

  //PRE: 'x_coordinate' and 'y_coordinate' must be valid map coordinates.
  //POS: Deletes the building in said coordinates and returns true or false otherwise.
  bool demolish_building(int x_coordinate, int y_coordinate);

  //PRE: 'building_type' must be a valid type.
  //POS: Shows on screen amount and coordinates of the buildings built.
  void show_buildings(Player* current_player, string building_type);

  //PRE: 'building_type_to_count' must be a valid type.
  //POS: Returns the amount of buildings built of the consulted type.
  int get_building_built_amount(string building_type_to_count, int player_id);

  //PRE: 'building_type' must be a valid building type.
  //POS: Returns true if player has at least one such 'building_type'.
  bool player_has_building_type(string building_type, Player* player);

  //PRE: 'building_type' must be a valid type. 'x_coordinate' and 'y_coordinate' must be valid map coordinates.
  //POS: Returns a Building pointer pointing to the building with said type and coordinates.
  Building* get_building(string building_type, int x_coordinate, int y_coordinate);

  //PRE: 'current_player' must be a valid player.
  //POS: current_player buildings spawn resources.
  void produce_resources(Player* current_player);

  //PRE: 'building_type' must be a valid type.
  //POS: Returns the amount of material that said type of building produces.
  void collect_resources(int &stone_collected, int &wood_collected, int &steel_collected,
                         int &energy_collected, int &gold_collected, Player* current_player);


  //PRE: 'player' must be a valid player.
  //POS: Retruns true if player has a damaged buildings, false otherwise.  
  bool player_has_buildings_to_repair(Player* player);

  //PRE:-
  //POS: Returns all the buildings built in the format of 'ubicaciones.txt'.
  string building_data_to_string(string saved_data, int player_id);

private:
  //PRE: Damaged building has to be a Mine or a Factory.
  //POS: Retruns true if player has damaged a buildings, false otherwise.
  bool announce_damaged_buildings(bool damaged_building);
};

#endif //BUILDING_HANDLER_H
