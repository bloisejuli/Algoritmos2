#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include "bstnode.h"

class BinarySearchTree {

private:
  BstNode* root;

public:
  //PRE:
  //POS: Creates Binary Search Tree
  BinarySearchTree();

  //PRE:-
  //POS: Destroys Binary Search Tree 
  ~BinarySearchTree();

  //PRE: All parameters must be valid.
  //POS: Creates a new Building and inserts it into the Binary Search Tree.
  void insert(string building_type, int stone_cost, int wood_cost, int steel_cost, 
              int max_building_quantity);
	
  //PRE: -
  //POS: Returns the associated node with 'building_type'  
  BstNode* search_node(string building_type);

  //PRE: -
  //POS: Returns true if 'building_type' is a valid type or false otherwise.
  bool validate_building_type(string building_type);

  //PRE: 'player_id' must be a valid player.
  //POS: Returns true if building amount is a valid quantity or false otherwise.
  bool validate_building_amount(string building_type, int player_id);

  //PRE: -
  //POS: Returns true if materials requirements are enough, false otherwise.
  bool validate_material_requirement(string building_type, int stone_amount,
                                      int wood_amount, int steel_amount);

  //PRE: -
  //POS: Modifies building stone cost.
  void modify_building_stone_cost(string building_type, int new_stone_cost);

  //PRE: -
  //POS: Modifies building wood cost.
  void modify_building_wood_cost(string building_type, int new_wood_cost);

  //PRE: -
  //POS: Modifies building steel cost.
  void modify_building_steel_cost(string building_type, int new_steel_cost);

  //PRE: -
  //POS: Modifies buildings built amount.
  void modify_built_amount(string building_type, int modifier, int player_id);

  //PRE: -
  //POS: Returns building stone cost.
  int get_building_stone_cost(string building_type);

  //PRE: -
  //POS: Returns building wood cost.
  int get_building_wood_cost(string building_type);

  //PRE: -
  //POS: Returns building steel cost.
  int get_building_steel_cost(string building_type);

  //PRE: -
  //POS: Returns building builts amount.
  int get_building_built_amount(string building_type, int player_id);

  //PRE: - 
  //POS: Returns building builts max amount.
  int get_building_max_amount(string building_type);

  //PRE: -
  //POS: Prints buildings recipes. 
  void show_builings(int stone_amount, int wood_amount, int steel_amount, int player_id);

  //PRE: -
  //POS: Returns all the buildings built in the format of 'edificios.txt'.
  string building_data_to_string();


private:
  //PRE: -
  //POS: Creates a new Building and inserts it into the Binary Search Tree.
  BstNode* insert(BstNode* root, BuildingRecord* building);

  //PRE: -
  //POS: Returns the associated node with 'building_type'  
  BuildingRecord* search_building(BstNode* node, string building_type);
	
  //PRE: -
  //POS: Returns the associated node with 'building_type'  
  BstNode* search_node(BstNode* node, string building_type);

  //PRE: -
  //POS: Returns true if 'building_type' is a valid type or false otherwise.
  bool validate_building_type(BstNode* node, string building_type);
	
  //PRE: 'player_id' must be a valid player.
  //POS: Returns true if building amount is a valid quantity or false otherwise.
  bool validate_building_amount(BstNode* node, string building_type, int player_id);
	
  //PRE: -
  //POS: Returns true if materials requirements are enough, false otherwise.
  bool validate_material_requirement(BstNode* node, string building_type, int stone_amount,
                                      int wood_amount, int steel_amount);

  //PRE: -
  //POS: Prints buildings recipes. 
  void show_builings(BstNode* node, int stone_amount, int wood_amount, int steel_amount, int player_id);

  //PRE: -
  //POS: Returns all the buildings built in the format of 'edificios.txt'.
  void building_data_to_string(BstNode* node, string &data);

  //PRE: -
  //POS: Returns null pointer and the Binary Search Tree is eliminated.
  BstNode* erase_tree(BstNode* node);
};

#endif //BINARY_SEARCH_TREE_H
