#ifndef CITY_H
#define CITY_H
#include "map.h"
#include "record.h"
#include "building_handler.h"
#include "empty_passable_tiles.h"
using namespace std;


class City {
private:

  BuildingHandler* buildings;
  Record* record;
  Map* city_map;
  EmptyPassableTiles* passable_tiles;
  List<string>* building_types;

public:

  // PRE: -
  // POS: Creates a City object.
  City();

  // PRE: -
  // POS: Destroys City object and calls the destructor of its attributes.
  ~City();


//--------------------------Material Management---------------------------------

  //PRE: 'current_player' must be a valid player.
  //POS: current_player buildings spawn resources.
  void produce_resources(Player* current_player);

  //PRE: -
  //POS: Collects materials produced by the constructed buildings, increasing the amount on the MaterialHandler.
  void collect_resources(int &stone_collected,int &wood_collected,int &steel_collected,
                                int &energy_collected, int &gold_collected, Player* current_player);

  //PRE: -
  //POS: Randomly generates a material type and a random amount of it, and puts in on the map.
  void material_rain();

  //PRE: -
  //POS: Returns the 'material_type' costs of 'building_type'.
  int get_material_cost(string building_type, string material_type);

  //PRE: 'material_type' must be a valid material. 'x_coordinate' and 'y_coordinate' must be valid map coordinates.
  //POS: Returns true if there are not empty tiles, false otherwise.
  void place_material_on_map(string material_type, int x_coordinate, int y_coordinate);


//-----------------------------Building Management------------------------------

  //PRE: 'current_player' must be a valid player.
  //POS: Validates that the building its allowed to be built, if it is calls the methods deduct_building_cost
  //     and add_building, otherwise print an error message.
  bool add_building(string building_type, int x_coordinate, int y_coordinate,
                     bool loading_from_txt, int player_stone, int player_wood, int player_steel, Player* current_player);

  //PRE: -
  //POS: Demolishes the Building at given coordinates and refunds half of its costs.
  bool demolish_building(int x_coordinate, int y_coordinate, int player_id);

  //PRE: 'x_coordinate' and 'y_coordinate' must be valid map coordinates. 'player_id' must be a valid player
  //POS: Eliminate the player's building at the corresponding coordinates.
  void destroy_building(int x_coordinate, int y_coordinate, int player_id);

  //PRE: 'current_player' a valid player
  //POS: Shows on screen amount and coordinates of the buildings built.
  void show_buildings(Player* current_player);

  //PRE: -
  //POS: If 'building_type' is in "edificio.txt" returns true, otherwise returns false.
  bool validate_building_type(string type_to_check);

  //PRE: -
  //POS: Returns true if 'building_type' is a valid building, false otherwise.
  bool player_has_building_type(string building_type, Player* player);

  //PRE: 'player' must be a valid player.
  //POS: Returns true if the player has a building to repair, false otherwise.
  bool player_has_buildings_to_repair(Player* player);

  //PRE: 'player_id' must be a valid player.
  //POS: Returns true if the amount of schools built equals the maximum number of schools allowed, false otherwise.
  bool player_built_max_amount_school(int player_id);

//-----------------------------Record Management--------------------------------

  // PRE: The amount of built buildings from file edificios.txt must be a-
  //      interger > 0 to assure the correct functioning of- the rest of the program and stone_cost,
  //      wood_cost, steel_cost, max_building_quantity all must be > 0.
  // POS: Adds the Building caracteristics in the Record.
  void add_building(string building_type, int stone_cost, int wood_cost, int steel_cost, int max_building_quantity);

  //PRE: 'building_types' mmust be a valid building.
  //POS: Adds new building to the list.
  void add_building_type(string building_types);

  // PRE: -
  // POS: Shows on screen all buildings information and the materials.
  void show_record(int user_stone, int user_wood, int user_steel, int player_id);

  //PRE: 'building_type' must be a valid building.
  //POS: Modifies the cost of construction of the building.
  void modify_building_costs(string building_type);

  //PRE:-
  //POS: Returns all the buildings built in the format of 'ubicaciones.txt'.
  string record_data_to_string();

//-------------------------------Map Management---------------------------------

  //PRE: 'row' >= 0 and 'columns' >= 0.
  //POS: Create a new map object.
  void generate_map(int rows, int columns);

  //PRE: 'tile_type' must be a LAKE, TERRAIN or ROAD. 'x_coordinate' and 'y_coordinate'
  //     must be valid map coordinates.
  //POS: Loads 'city_map' with tiles and if tile is ROAD it also loads it in 'passable_tiles'.
  void add_tile(char tile_type, int x_coordinate, int y_coordinate);

  //PRE: 'x_coordinate' and 'y_coordinate' must be valid map coordinates.
  //POS: Shows on screen the tile type and if its empty or the content.
  void consult_tile(int x_coordinate, int y_coordinate, Player* player_1, Player* player_2);

  //PRE: -
  //POS: Returns the map rows.
  int get_max_rows();

  //PRE: -
  //POS: Returns the map columns.
  int get_max_columns();

  //PRE: -
  //POS: Prints the map.
  void show_map(bool legend_visibility, int player_id);

  //PRE: 'x_coordinate' and 'y_coordinate' must be valid map coordinates.
  //POS: Returns the building type.
  string get_target_building_type(int x_coordinate, int y_coordinate);

  //PRE: 'x_coordinate' and 'y_coordinate' must be valid map coordinates.
  //POS: Returns true if the consulted tile is a buildable tile.
  bool tile_buildable(int x_coordinate, int y_coordinate);

  //PRE: 'x_coordinate' and 'y_coordinate' must be valid map coordinates.
  //POS: Returns true if tile has building, false otherwise.
  bool tile_has_building(int x_coordinate, int y_coordinate);

  //PRE: 'x_coordinate' and 'y_coordinate' must be valid map coordinates.
  //POS: Returns true if tile has repairable building, flase otherwise.
  bool tile_has_repairable_building(int x_coordinate, int y_coordinate);

  //PRE: 'x_coordinate' and 'y_coordinate' must be valid map coordinates.
  //POS: Returns Player owner of the building.
  Player* get_building_owner(int x_coordinate, int y_coordinate);

  //PRE: 'x_coordinate' and 'y_coordinate' must be valid map coordinates.
  //POS: Returns true if destroy building, false otherwise.
  bool attack_building(int x_coordinate, int y_coordinate);

  //PRE: 'x_coordinate' and 'y_coordinate' must be valid map coordinates.
  //POS: Returns true if the buildin is repaired, false otherwise.
  bool repair_building(int x_coordinate, int y_coordinate);

  //PRE: -
  //POS: Return true if player is correctly spawn, false otherwise.
  bool spawn_player(Player* player, int x_coordinate, int y_coordinate);

  //PRE: -
  //POS: Moves Player on the map
  void move_player(Player* player, int energy_cost, stack<Vertex> vertex_traversed);

  //PRE: -
  //POS: Returns true if the tile is traversable tile.
  bool traversable_tile(int x_coordinate, int y_coordinate);

  //PRE: -
  //POS: Returns all the buildings built in the format of 'ubicaciones.txt'.
  string elements_data_to_string();


private:

//----------------------------Material Management-------------------------------

  void show_material_rain_announcement( int amount_droped, string material_type);

  Material* generate_material(string material_type);

  //PRE: 'material_type' must be a valid material.
  //POS: Returns true if there are not empty tiles, false otherwise.
  bool place_material_on_map(int amount_of_drops, string material_type);

//----------------------------Building Management-------------------------------

  //PRE: -
  //POS: Adds a new Building and adds it to the BuildingHandler and then makes the tile, in the map with said
  //     coordinates, to point to the new Building.
  void add_building(string building_type, string material_that_produces, string icon_building, int x_coordinate, int y_coordinate, Player* current_player);

  //PRE: -
  //POS: Prints a message on the screen according to the error when trying to build a new Building.
  void print_error_message(bool valid_type, bool valid_amount, bool enough_materials,
                            bool valid_tile, bool empty_tile, bool loading_from_txt,
                            string building_type, int x_coordinate, int y_coordinate);

  //PRE: -
  //POS: Shows on screen a message whether the building was demolished or not.
  void announce_when_a_building_is_demolished(bool building_demolished, bool valid_tile, bool empty_tile,
                                              string building_type, int x_coordinate, int y_coordinate);

  //PRE:
  //POS: Shows on screen a message whether the building was built or not.
  void announce_when_a_building_is_built(bool user_confirmed, string building_type);

  //PRE: 'building_type' must be a valid building
  //POS: Returns what type of material produces 'building_type'.
  string get_resource_that_building_produces(string building_type);

  //PRE: 'building_type' must be a valid building
  //POS: returns the icon corresponding to 'building_type'
  string get_building_icon(string building_type);

};

#endif//CITY_H
