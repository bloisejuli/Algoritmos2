#ifndef CITY_H
#define CITY_H
#include "map.h"
#include "record.h"
#include "building_handler.h"
#include "material_handler.h"
#include "empty_passable_tiles.h"
using namespace std;


class City {
private:

  BuildingHandler* buildings;
  MaterialHandler* materials;
  Record* record;
  Map* city_map;
  EmptyPassableTiles* passable_tiles;

public:

  // PRE: -
  // POS: Creates a City object.
  City();

  // PRE: -
  // POS: Destroys City object and calls the destructor of its attributes.
  ~City();


//--------------------------Material Management---------------------------------

  //PRE: -
  //POS: Creates a new Material object and adds it to the MaterialHandler.
  void add_material(string new_material, int quantity);

  //PRE: -
  //POS: Shows on screen the materials and their quantity.
  void show_materials();

  //PRE: -
  //POS: Collects materials produced by the constructed buildings, increasing the amount on the MaterialHandler.
  void collect_resources();

  //PRE: -
  //POS: Randomly generates a material type and a random amount of it, and puts in on the map.
  void material_rain();

  //PRE: -
  //POS: Returns all the materials in the format of 'materiales.txt'.
  string materials_data_to_string();

  //PRE: -
  //POS: Adds a Material in a PassableTile with said coordinates.
  void add_material_to_tile(string material_type, int x_coordinate, int y_coordinate);


//-----------------------------Building Management------------------------------

  //PRE: the amount of built buildings from file edificios.txt must be a-
  //      interger > 0 to assure the correct functioning of- the rest of the program.
  //POS: Validates that the building its allowed to be built, if it is calls the methods deduct_building_cost
  //     and add_building, otherwise print an error message.
  void add_building(string building_type, int x_coordinate, int y_coordinate, bool loading_from_txt);

  //PRE: -
  //POS: Demolishes the Building at given coordinates and refunds half of its costs.
  void demolish_building(int x_coordinate, int y_coordinate);

  //PRE: -
  //POS: Shows on screen amount and coordinates of the buildings built.
  void show_buildings();

  //PRE: -
  //POS: If 'building_type' is in "edificio.txt" returns true, otherwise returns false.
  bool validate_building_type(string type_to_check);

//-----------------------------Record Management--------------------------------

  // PRE: The amount of built buildings from file edificios.txt must be a-
  //      interger > 0 to assure the correct functioning of- the rest of the program and stone_cost,
  //      wood_cost, steel_cost, max_building_quantity all must be > 0.
  // POS: Adds the Building caracteristics in the Record.
  void add_building(string building_type, int stone_cost, int wood_cost,
                    int steel_cost, int max_building_quantity);

  // PRE: -
  // POS: Shows on screen all buildings information and the materials.
  void show_record();

  //PRE: -
  //POS: Returns all the buildings built in the format of 'ubicaciones.txt'.
  string building_data_to_string();


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
  void consult_tile(int x_coordinate, int y_coordinate);

  //PRE: -
  //POS: Returns the map rows.
  int get_max_rows();

  //PRE: -
  //POS: Returns the map columns.
  int get_max_columns();

  //PRE: -
  //POS: Prints the map.
  void show_map();


private:

//----------------------------Material Management-------------------------------

  //PRE: -
  //POS: Changes the quantity of the Material with "material_name" = "material_to_modify"
  //      to "new_quantity".
  void set_material_amount(string material_to_modify, int new_quantity);

  // //PRE: -
  // //POS: Returns the quantity of the material that has its name = 'material_name_to_obtain'.
  int get_material_amount(string material_name_to_obtain);

  //PRE: 'building_type' must be a valid building.'user_stone', 'user_wood' and 'user_steel' all
  //      must be greater than or equal to the cost of construction of the building.
  //POS: Deducts the cost of the building from the total of materials.
  void deduct_building_cost(int user_stone, int user_wood, int user_steel, string building_type);

  //PRE: 'building_type' must be a valid type.
  //POS: Refunds the building costs / 2.
  void refund_building_cost(string building_type);


//----------------------------Building Management-------------------------------

  //PRE: -
  //POS: Adds a new Building and adds it to the BuildingHandler and then makes the tile, in the map with said
  //     coordinates, to point to the new Building.
  void add_building(string building_type, string material_that_produces, int x_coordinate, int y_coordinate);

  //PRE: -
  //POS: Prints a message on the screen according to the error when trying to build a new Building.
  void print_error_message(bool valid_type, bool valid_amount, bool enough_materials,
                            bool valid_tile, bool empty_tile, bool loading_from_txt,
                            string building_type, int x_coordinate, int y_coordinate);

  //PRE: -
  //POS: Returns what type of material produces 'building_type'.
  string get_resource_that_building_produces(string building_type);

};

#endif//CITY_H
