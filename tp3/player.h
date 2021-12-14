#ifndef PLAYER_H
#define PLAYER_H

#include "list.h"
#include "material.h"

class Player {

private:
  List<Material>*  resources;
  int x_coordinate;
  int y_coordinate;
  int id;
  string icon;
  int objectives[AMOUNT_OF_PLAYER_OBJECTIVES];
  int gold_collected;
  int bombs_bought;
  int bombs_used;
  static int number_of_players;

public:
  Player();

  ~Player();

  void add_resource(string resource, int quantity);

  //PRE: -
  //POS: Shows on screen the resources and their quantity.
  void show_resources();

  //PRE: 'resource' must be a valid resource name.
  //POS: Replaces the quantity of target resource to 'new_quantity'.
  void set_resource_amount(string resource_to_modify, int new_quantity);

  //PRE: 'target_resource' must be a resource valid.
  //POS: Returns the quantity of target resource.
  int get_resource_amount(string target_resource);

  string resources_type_data_to_string();

  string resources_amount_data_to_string();

  void set_x_coordinate(int new_x_coordinate);

  int get_x_coordinate();

  void set_y_coordinate(int new_y_coordinate);

  int get_y_coordinate();

  void deduct_building_cost(int stone_cost, int wood_cost, int steel_cost);

  void refund_building_cost(int stone_cost, int wood_cost, int steel_cost);

  void buy_bombs(int amount_of_bombs, int bombs_cost);

  void use_bomb();

  void collect_resources(int stone_collected, int wood_collected, int steel_collected,
                          int energy_collected, int gold_collected);

  void recharge_energy();

  void deduct_energy(int energy_deducted);

  int get_id();

  string get_icon();

  // void show_objectives(); //TODO erase this

  void set_objectives(int* new_objectives);

  int* get_objectives();

  int get_gold_collected();

  int get_bombs_used();

  int get_bombs_bought();

};

#endif //PLAYER_H
