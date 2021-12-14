#include "bstnode.h"

BstNode::BstNode(BuildingRecord* building) {
  this->building = building;
  this->right = 0;
  this->left = 0;
}

BuildingRecord* BstNode::get_building() {
  return building;
}

string BstNode::get_building_type() {
  return building->building_type;
}

bool BstNode::max_quantity_built(int player_id) {
  
  if(player_id == PLAYER_1)
	return building->built_amount_player_1 != building->max_quantity;
  else
	return building->built_amount_player_2 != building->max_quantity;
}

bool BstNode::validate_material_requirement(int stone_amount, int wood_amount, int steel_amount) {
  bool valid_amount;

  if(get_stone_cost() <= stone_amount && get_wood_cost() <= wood_amount &&
	get_steel_cost() <= steel_amount) {

	valid_amount = true;
  }
  else
	valid_amount = false;

  return valid_amount;
}

void BstNode::modify_stone_cost(int new_stone_cost) {
  building->stone_cost = new_stone_cost;
}

void BstNode::modify_wood_cost(int new_wood_cost) {
  building->wood_cost = new_wood_cost;
}

void BstNode::modify_steel_cost(int new_steel_cost) {
  building->steel_cost = new_steel_cost;
}

void BstNode::modify_built_amount(int new_amount_built, int player_id) {
  if(player_id == PLAYER_1)
	building->built_amount_player_1 += new_amount_built;
  else
	building->built_amount_player_2 += new_amount_built;
}

int BstNode::get_stone_cost() {
  return building->stone_cost;
}

int BstNode::get_wood_cost() {
  return building->wood_cost;
}

int BstNode::get_steel_cost() {
  return building->steel_cost;
}

int BstNode::get_built_amount(int player_id) {
  if (player_id == PLAYER_1)
	return building->built_amount_player_1;
  else
	return building->built_amount_player_2;
}

int BstNode::get_max_amount() {
  return building->max_quantity;
}

void BstNode::show_builing(int stone_amount, int wood_amount, int steel_amount, int player_id) {
  bool buildable_building = false;
  string color_building_type;
  string capitalized_building_type = building->building_type;

  if (player_id != 0) {

	if ( max_quantity_built(player_id) && validate_material_requirement(stone_amount, wood_amount, steel_amount))
	  buildable_building = true;
	}

  if (buildable_building)
	color_building_type = BOLD_GREEN;
  else
	color_building_type = BOLD_RED;

  string buildings_built;

  std::cout << DEFAULT_COLOR << "Building:                " << color_building_type << capitalized_building_type << '\n';
  std::cout << DEFAULT_COLOR << "Stone cost:              " << BOLD_BLACK  << building->stone_cost << '\n';
  std::cout << DEFAULT_COLOR << "Wood cost:               " << BOLD_GREEN << building->wood_cost << '\n';
  std::cout << DEFAULT_COLOR << "Steel cost:              " << BOLD_CYAN  << building->steel_cost << '\n';

  if(player_id == PLAYER_1) {
	std::cout << DEFAULT_COLOR << "Amount of buildigns:     " << BOLD_BLUE  << building->built_amount_player_1 << '\n';
	std::cout << DEFAULT_COLOR << "Amount allowed to build: " << BOLD_RED << building->max_quantity - building->built_amount_player_1 << '\n';
  }
  else if (player_id == PLAYER_2) {
	std::cout << DEFAULT_COLOR << "Amount of buildigns:     " << BOLD_BLUE  << building->built_amount_player_2 << '\n';
	std::cout << DEFAULT_COLOR << "Amount allowed to build: " << BOLD_RED << building->max_quantity - building->built_amount_player_2 << '\n';
  }
  else
	std::cout << DEFAULT_COLOR << "Amount allowed to build: " << BOLD_RED << building->max_quantity << '\n';

  std::cout << "\n" << BOLD_VIOLET << DIVISORY_LINE << DEFAULT_COLOR << "\n" << "\n";
}

void BstNode::save_building_data(string &data) {
  data = data + building->building_type + " ";
  data = data + to_string(building->stone_cost) + " ";
  data = data + to_string(building->wood_cost) + " ";
  data = data + to_string(building->steel_cost) + " ";
  data = data + to_string(building->max_quantity) + '\n';
}

BstNode::~BstNode() {
  delete building;
}