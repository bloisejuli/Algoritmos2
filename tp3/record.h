#ifndef RECORD_HANDLER_H
#define RECORD_HANDLER_H
#include "binary_search_tree.h"

using namespace std;



class Record {

private:
  // List<BuildingRecord>* record;
  BinarySearchTree* record;

public:

  //PRE:-
  //POS: Creates a record object, with an empty list.
  Record();

  //PRE:-
  //POS: Destroy Record object and calls the destructor of the list.
  ~Record();

  //PRE: -
  //POS: Creates a new BuildingRecord object with the attributes received by parameter and adds a it to the list.
  void add_building(string building_type, int stone_cost, int wood_cost,
                        int steel_cost, int max_building_quantity);

  //PRE: 'building_type' must be a valid type.
  //POS: Changes the building amount for the building in amount + 'modifier'.
  void modify_building_amount(string building_type, int modifier, int player_id);

  //PRE: -
  //POS: Shows on screen all building information.
  void show_record(int user_stone, int user_wood, int user_steel, int player_id);

  //PRE: 'buildin_type' must be a valid type.
  //POS: Returns the stone cost of the building type.
  int get_stone_cost(string building_type);

  //PRE: 'buildin_type' must be a valid type.
  //POS: Returns the wood cost of the building type.
  int get_wood_cost(string building_type);

  //PRE: 'buildin_type' must be a valid type.
  //POS: Returns the steel cost of the building type.
  int get_steel_cost(string building_type);

  //PRE: -
  //POS: If 'building_type' is in "edificio.txt" returns true, otherwise returns false.
  bool validate_building_type(string building_type);

  //PRE: 'buildin_type' must be a valid type.
  //POS: If amount_of_buildings_built + 1 <= max_quantity returns true, otherwise returns false.
  bool validate_building_amount(string building_type, int player_id);

  //PRE: 'buildin_type' must be a valid type.
  //POS: If you have the amount of material needed to build it returns true, otherwise returns false.
  bool validate_material_requirement(string building_type, int stone_amount,
                                      int wood_amount, int steel_amount);

  void modify_building_costs(string building_type);

  int get_building_max_amount(string building_type);

  //PRE:-
  //POS: Returns all the buildings built in the format of 'ubicaciones.txt'.
  string record_data_to_string();

private:
  string validate_new_material_cost(string new_cost);

};

#endif
