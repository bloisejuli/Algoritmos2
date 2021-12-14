#include "player.h"

int Player::number_of_players = 0;

Player::Player() {
  resources = new List<Material>;
  number_of_players++;
  id = number_of_players;
  gold_collected = 0;
  bombs_bought = 0;
  bombs_used = 0;
  x_coordinate = 0;
  y_coordinate = 0;

  if(number_of_players == PLAYER_1)
    icon = PLAYER_1_ICON;

  else if (number_of_players == PLAYER_2)
    icon = PLAYER_2_ICON;
}

void Player::add_resource(string resource, int quantity) {
  //resources->add_resource(resource, quantity);
  Material* new_resource = new Material(resource, quantity);
  resources->add_node(new_resource);
}

//PRE: -
//POS: Shows on screen the resources and their quantity.
void Player::show_resources() {
    resources->reset_current_node();

    while (resources->get_current_value() != 0) {
        string material = resources->get_current_value()->get_material();
        string capitalized_material = capitalize_word(material);
        string material_color = get_material_color(material);

        std::cout << left << setw(WIDTH) << "Material: " << material_color <<
                  setw(WIDTH) << capitalized_material << DEFAULT_COLOR
                  << setw(WIDTH) << " Quantity: " << BOLD_BLUE << setw(WIDTH) <<
                  resources->get_current_value()->get_quantity() << DEFAULT_COLOR << '\n';

        resources->next_node();
    }
}

//PRE: 'resource' must be a valid resource name.
//POS: Replaces the quantity of target resource to 'new_quantity'.
void Player::set_resource_amount(string resource_to_modify, int new_quantity) {
    resources->reset_current_node();

    while (resources->get_current_value() != 0) {
        if (resources->get_current_value()->get_material() == resource_to_modify)
            resources->get_current_value()->set_quantity(new_quantity);

        resources->next_node();
    }
}

//PRE: 'target_resource' must be a resource valid.
//POS: Returns the quantity of target resource.
int Player::get_resource_amount(string target_resource) {
  resources->reset_current_node();

  while (resources->get_current_value() != 0) {
      if (resources->get_current_value()->get_material() == target_resource)
          return resources->get_current_value()->get_quantity();

      resources->next_node();
  }

  return -1;
}

void Player::set_x_coordinate(int new_x_coordinate) {
  this->x_coordinate = new_x_coordinate;
}

int Player::get_x_coordinate() {
  return x_coordinate;
}

void Player::set_y_coordinate(int new_y_coordinate) {
  this->y_coordinate = new_y_coordinate;
}

int Player::get_y_coordinate() {
  return y_coordinate;
}


string Player::resources_type_data_to_string() {
    resources->reset_current_node();
    resources->next_node();

    string resource;

    while (resources->get_current_value() != 0) {
      //resource = resource + resources->get_string_resource() + " ";
        resource = resource + resources->get_current_value()->get_material() + " ";
      resources->next_node();

    }

    return resource;
}

string Player::resources_amount_data_to_string() {
    resources->reset_current_node();
    resources->next_node();

    string resource;

    while (resources->get_current_value() != 0) {
        resource = resource + to_string(resources->get_current_value()->get_quantity()) + " ";
        resources->next_node();
    }

    return resource;
}

void Player::deduct_building_cost(int stone_cost, int wood_cost, int steel_cost) {
  set_resource_amount(STONE, get_resource_amount(STONE) - stone_cost);
  set_resource_amount(WOOD, get_resource_amount(WOOD) - wood_cost);
  set_resource_amount(STEEL, get_resource_amount(STEEL) - steel_cost);
}

void Player::refund_building_cost(int stone_cost, int wood_cost, int steel_cost) {
  set_resource_amount(STONE, get_resource_amount(STONE) + stone_cost / 2);
  set_resource_amount(WOOD, get_resource_amount(WOOD) + wood_cost / 2);
  set_resource_amount(STEEL, get_resource_amount(STEEL) + steel_cost / 2);
}

void Player::buy_bombs(int amount_of_bombs, int bombs_cost) {
  set_resource_amount(GOLD, get_resource_amount(GOLD) - bombs_cost);
  set_resource_amount(BOMB, get_resource_amount(BOMB) + amount_of_bombs);
  bombs_bought += amount_of_bombs;
}

void Player::use_bomb() {
  set_resource_amount(BOMB, get_resource_amount(BOMB) - 1);
  bombs_used += 1;
}

void Player::collect_resources(int stone_collected, int wood_collected, int steel_collected,
                        int energy_collected, int gold_collected) {

  set_resource_amount(STONE, get_resource_amount(STONE) + stone_collected );
  set_resource_amount(WOOD, get_resource_amount(WOOD) + wood_collected);
  set_resource_amount(STEEL, get_resource_amount(STEEL) + steel_collected);
  set_resource_amount(ENERGY, get_resource_amount(ENERGY) + energy_collected);
  set_resource_amount(GOLD, get_resource_amount(GOLD) + gold_collected);

  this->gold_collected += gold_collected;
}

void Player::recharge_energy() {
  if (get_resource_amount(ENERGY) + ENERGY_RECOVERED_AT_END_OF_TURN > MAX_ENERGY)
    set_resource_amount(ENERGY, MAX_ENERGY);

  else
    set_resource_amount(ENERGY, get_resource_amount(ENERGY) + ENERGY_RECOVERED_AT_END_OF_TURN);
}

void Player::deduct_energy(int energy_deducted) {
  set_resource_amount(ENERGY, get_resource_amount(ENERGY) - energy_deducted);
}

int Player::get_id() {
  return id;
}

string Player::get_icon() {
  return icon;
}

// void Player::show_objectives() { //TODO erase this
//   for(int i = 0; i < AMOUNT_OF_PLAYER_OBJECTIVES; i++) {
//     std::cout << id << ",  Objective: " << i << " is num " << objectives[i] << '\n' << '\n';
//   }
// }

void Player::set_objectives(int* new_objectives) {
  for (int i = 0; i < AMOUNT_OF_PLAYER_OBJECTIVES; i++) {
    this->objectives[i] = new_objectives[i];
  }
}

int* Player::get_objectives() {
  return objectives;
}

int Player::get_gold_collected() {
  return gold_collected;
}

int Player::get_bombs_used() {
  return bombs_used;
}

int Player::get_bombs_bought() {
  return bombs_bought;
}

Player::~Player() {

  delete resources;

}
