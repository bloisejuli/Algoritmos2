#include "binary_search_tree.h"

BinarySearchTree::BinarySearchTree(){
  root = 0;
}

void BinarySearchTree::insert(string building_type, int stone_cost, int wood_cost,
									   int steel_cost, int max_building_quantity) {

  BuildingRecord* new_building = new BuildingRecord{building_type, stone_cost, wood_cost, 
                                                    steel_cost, 0, 0, max_building_quantity};

  root = insert(this->root, new_building);
}

BstNode* BinarySearchTree::insert(BstNode* node, BuildingRecord* new_building) {

  if (node == 0)
	  node = new BstNode(new_building);
  else if(new_building->building_type.compare(node->get_building_type()) < 0 )
	  node->left = insert(node->left, new_building); //goes left -> recursive call in the left branch
  else
	  node->right = insert(node->right, new_building); //goes right -> recursive call in the right branch

  return node;
}

BuildingRecord* BinarySearchTree::search_building(BstNode* node, string building_type){
  BuildingRecord* building;

  if(node == 0)
	  building = 0;
  else if(node->get_building_type() == building_type)
	  building = node->get_building();
  else if(building_type.compare(node->get_building_type()) < 0)
	  building = search_building(node->left, building_type);
  else
	  building = search_building(node->right, building_type);

  return building;
}

BstNode* BinarySearchTree::search_node(string building_type) {
  BstNode* searched_node = search_node(this->root, building_type);

  if(searched_node == 0)
	  std::cout << "Building: '" << building_type << "' not found."<< '\n';

  return searched_node;
}

BstNode* BinarySearchTree::search_node(BstNode* node, string building_type) {
  BstNode* searched_node;

  if(node == 0)
	  searched_node = 0;
  else if(node->get_building_type() == building_type)
	  searched_node = node;
  else if(building_type.compare(node->get_building_type()) < 0)
	  searched_node = search_node(node->left, building_type);
  else
	  searched_node = search_node(node->right, building_type);
	
  return searched_node;
}

bool BinarySearchTree::validate_building_type(string building_type) {
  return validate_building_type(root, building_type);
}

bool BinarySearchTree::validate_building_type(BstNode* node, string building_type) {
  bool valid_building;

  if(node == 0)
	  valid_building = false;
  else if(node->get_building_type() == building_type)
	  valid_building = true;
  else if(building_type.compare(node->get_building_type()) < 0)
	  valid_building = search_building(node->left, building_type);
  else
	  valid_building = search_building(node->right, building_type);
	
  return valid_building;
}

bool BinarySearchTree::validate_building_amount(string building_type, int player_id) {
  return validate_building_amount(root, building_type, player_id);
}

bool BinarySearchTree::validate_building_amount(BstNode* node, string building_type, int player_id) {
	bool valid_amount;

  if(node == 0)
	  valid_amount = false;
  else if(node->get_building_type() == building_type)
	  valid_amount = node->max_quantity_built(player_id);
  else if(building_type.compare(node->get_building_type()) < 0)
	  valid_amount = validate_building_amount(node->left, building_type, player_id);
  else
	  valid_amount = validate_building_amount(node->right, building_type, player_id);

  return valid_amount;
}

bool BinarySearchTree::validate_material_requirement(string building_type, int stone_amount,
													int wood_amount, int steel_amount) {

  return validate_material_requirement(root, building_type, stone_amount, wood_amount, steel_amount);
}

bool BinarySearchTree::validate_material_requirement(BstNode* node, string building_type, int stone_amount,
													  int wood_amount, int steel_amount) {
  bool enough_materials;

  if (node == 0)
	  enough_materials = false;
  else if (node->get_building_type() == building_type)
	  enough_materials = node->validate_material_requirement(stone_amount, wood_amount, steel_amount);
  else if (building_type.compare(node->get_building_type()) < 0)
	  enough_materials = validate_material_requirement(node->left, building_type, stone_amount, wood_amount, steel_amount);
  else
	  enough_materials = validate_material_requirement(node->right, building_type, stone_amount, wood_amount, steel_amount);

  return enough_materials;
}

void BinarySearchTree::modify_building_stone_cost(string building_type, int new_stone_cost) {
  BstNode* target_node = search_node(building_type);

  if(target_node != 0)
	  target_node->modify_stone_cost(new_stone_cost);
}

void BinarySearchTree::modify_building_wood_cost(string building_type, int new_wood_cost) {
  BstNode* target_node = search_node(building_type);
	
  if(target_node != 0)
	  target_node->modify_wood_cost(new_wood_cost);
}

void BinarySearchTree::modify_building_steel_cost(string building_type, int new_steel_cost) {
  BstNode* target_node = search_node(building_type);

  if(target_node != 0)
	  target_node->modify_steel_cost(new_steel_cost);
}

void BinarySearchTree::modify_built_amount(string building_type, int modifier, int player_id) {
  BstNode* target_node = search_node(building_type);

  if(target_node != 0)
	  target_node->modify_built_amount(modifier, player_id);
}

int BinarySearchTree::get_building_stone_cost(string building_type) {
  BstNode* target_node = search_node(building_type);
  int stone_cost;

  if(target_node != 0)
	  stone_cost =  target_node->get_steel_cost();
  else
	  stone_cost = 0;

  return stone_cost;
}

int BinarySearchTree::get_building_wood_cost(string building_type) {
  BstNode* target_node = search_node(building_type);
  int wood_cost;

  if(target_node != 0)
	  wood_cost =  target_node->get_steel_cost();
  else
	  wood_cost = 0;

  return wood_cost;
}

int BinarySearchTree::get_building_steel_cost(string building_type) {
  BstNode* target_node = search_node(building_type);
  int steel_cost;

  if(target_node != 0)
	  steel_cost =  target_node->get_steel_cost();
  else
	  steel_cost = 0;

  return steel_cost;
}

int BinarySearchTree::get_building_built_amount(string building_type, int player_id) {
  BstNode* target_node = search_node(building_type);
  int amount_built;

  if(target_node != 0)
	  amount_built =  target_node->get_built_amount(player_id);
  else
	  amount_built = 0;

  return amount_built;
}

int BinarySearchTree::get_building_max_amount(string building_type) {
  BstNode* target_node = search_node(building_type);
  int max_amount;

  if(target_node != 0)
	  max_amount =  target_node->get_max_amount();
  else
    max_amount = 0;

  return max_amount;
}

void BinarySearchTree::show_builings(int stone_amount, int wood_amount, int steel_amount, int player_id) {
  show_builings(this->root, stone_amount, wood_amount, steel_amount, player_id);

}

void BinarySearchTree::show_builings(BstNode* node, int stone_amount, int wood_amount, int steel_amount, int player_id) {

  if(node == 0) 
	  return;

  show_builings(node->left, stone_amount, wood_amount, steel_amount, player_id);

  node->show_builing(stone_amount, wood_amount, steel_amount, player_id);

  show_builings(node->right, stone_amount, wood_amount, steel_amount, player_id);
}

string BinarySearchTree::building_data_to_string() {
  string data = "";

  building_data_to_string(root, data);

  return data;

}

void BinarySearchTree::building_data_to_string(BstNode* node, string &data) {

  if(node == 0) 
    return;

  building_data_to_string(node->left, data);

  node->save_building_data(data);

  building_data_to_string(node->right, data);

}

BstNode* BinarySearchTree::erase_tree(BstNode* node) {

  if(node->left != 0)
	  node->left = erase_tree(node->left);

  if(node->right != 0)
	  node->right = erase_tree(node->right);

  if(node->left == 0 && node->right == 0) {
	  delete node;
	  return node = 0;
  }
  return 0;
}

BinarySearchTree::~BinarySearchTree(){
	erase_tree(this->root);
}
