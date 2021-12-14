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
  void add_building(string building_type, string material_that_produce, int x_coordinate, int y_coordinate);

  //PRE: 'x_coordinate' and 'y_coordinate' must be valid map coordinates.
  //POS: Deletes the building in said coordinates and returns true or false otherwise.
  bool demolish_building(int x_coordinate, int y_coordinate);

  //PRE: 'building_type' must be a valid type.
  //POS: Shows on screen amount and coordinates of the buildings built.
  void show_buildings(string building_type, int amount_built);

  //PRE: 'building_type_to_count' must be a valid type.
  //POS: Returns the amount of buildings built of the consulted type.
  int get_building_built_amount(string building_type_to_count);

  //PRE: 'building_type' must be a valid type. 'x_coordinate' and 'y_coordinate' must be valid map coordinates.
  //POS: Returns a Building pointer pointing to the building with said type and coordinates.
  Building* get_building(string building_type, int x_coordinate, int y_coordinate);

  //PRE: 'building_type' must be a valid type.
  //POS: Returns the amount of material that said type of building produces.
  int get_resources_amount(string building_type);

  //PRE: 'building_type' must be a valid type.
  //POS: Returns material type that said type of building produces.
  string get_resources_type(string building_type);

  //PRE:-
  //POS: Returns all the buildings built in the format of 'ubicaciones.txt'.
  string building_data_to_string();

};

#endif //BUILDING_HANDLER_H
