#ifndef BSTNODE_H
#define BSTNODE_H

#include <iostream>
#include <fstream>
#include <string>
#include "constants.h"
#include "utils.h"

using namespace std;

struct BuildingRecord{
  string building_type;
  int stone_cost = 0;
  int wood_cost = 0;
  int steel_cost = 0;
  int built_amount_player_1 = 0;
  int built_amount_player_2 = 0;
  int max_quantity = 0;
};

class BstNode{

private:
	BuildingRecord* building;

public:
	BstNode* right;
	BstNode* left;

  //PRE: -
  //POS: Creates a BstNode.
	BstNode(BuildingRecord* building);

  //PRE: -
  //POS: Destroys BstNode.
	~BstNode();

  //PRE: -
  //POS: Returns building.
	BuildingRecord* get_building();

  //PRE: - 
  //POS: Returns building type.
	string get_building_type();


  //PRE: -
  //POS: Returns true if building amount is a valid quantity or false otherwise.
  bool max_quantity_built(int player_id);

  //PRE: -
  //POS: Returns true if materials requirements are enough, false otherwise.
  bool validate_material_requirement(int stone_amount, int wood_amount, int steel_amount);

  //PRE: -
  //POS: Modifies building stone cost.
  void modify_stone_cost(int new_stone_cost);

  //PRE: -
  //POS: Modifies building wood cost.
  void modify_wood_cost(int new_wood_cost);
  
  //PRE: -
  //POS: Modifies building steel cost.
  void modify_steel_cost(int new_steel_cost);

  //PRE: -
  //POS: Modifies buildings built amount.
  void modify_built_amount(int new_amount_built, int player_id);

  //PRE: -
  //POS: Returns building stone cost.
  int get_stone_cost();

  //PRE: -
  //POS: Returns building wood cost.
	int get_wood_cost();

  //PRE: -
  //POS: Returns building steel cost.
	int get_steel_cost();

  //PRE: -
  //POS: Returns the number of buildings built by the player.
  int get_built_amount(int player_id);

  //PRE: -
  //POS: Returns building builts max amount.
  int get_max_amount();

  //PRE: -
  //POS: Returns the building information.
  void show_builing(int stone_amount, int wood_amount, int steel_amount, int player_id);

  //PRE: -
  //POS: Modifies 'data' with the information of all the buildings in the format of 'edificios.txt'.
  void save_building_data(string &data);
};

#endif //BSTNODE_H
