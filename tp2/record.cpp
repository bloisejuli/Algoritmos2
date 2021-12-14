#include "record.h"

Record::Record() {

  record = new List<BuildingRecord>;

}

void Record::add_building(string building_type, int stone_cost, int wood_cost,
                           int steel_cost, int max_building_quantity) {

    BuildingRecord* new_building = new BuildingRecord{building_type, stone_cost,
                                  wood_cost, steel_cost, 0, max_building_quantity};

    record->add_node(new_building);

}

void Record::modify_building_amount(string building_type, int modifier) {

  record->reset_current_node();

  while (record->get_current_value() != 0) {

    if (record->get_current_value()->building_type == building_type)
      record->get_current_value()->built_amount += modifier;

    record->next_node();

  }

    record->reset_current_node();

}

int Record::get_building_amount(string building_type) {

  record->reset_current_node();

  while (record->get_current_value() != 0) {

    if (record->get_current_value()->building_type == building_type)
      return record->get_current_value()->built_amount;

    record->next_node();

  }

  record->reset_current_node();

  return 0;

}

void Record::show_record(int user_stone, int user_wood, int user_steel) {

  std::cout << "All the types of buildings are:" << '\n';

  std::cout << "(Names in "<< BOLD_GREEN << "green" << DEFAULT_COLOR
             << " are buildings you can build, " << BOLD_RED << "red"
              << DEFAULT_COLOR << " are the one you can't)" << '\n' << '\n';

  bool enough_materials = false;
  bool valid_amount = false;

  Node<BuildingRecord>* aux_node = record->get_first_node();

  while (aux_node != 0) {

    string capitalized_building_type = capitalize_word(aux_node->get_value()->building_type);

    int amount_of_buildings_built = get_building_amount(aux_node->get_value()->building_type);

    enough_materials = validate_material_requirement(aux_node->get_value()->building_type,
                                                      user_stone, user_wood, user_steel);

    valid_amount = validate_building_amount(aux_node->get_value()->building_type,
                                                  amount_of_buildings_built);

    if (capitalized_building_type == POWER_PLANT)
      capitalized_building_type = "Planta eléctrica";

    if (enough_materials && valid_amount)
      std::cout << DEFAULT_COLOR << "Building:                " << BOLD_GREEN << capitalized_building_type << '\n';

    else
      std::cout << DEFAULT_COLOR << "Building:                " << BOLD_RED << capitalized_building_type << '\n';

    std::cout << DEFAULT_COLOR << "Stone cost:              " << BOLD_BLACK  << aux_node->get_value()->stone_cost << '\n';
    std::cout << DEFAULT_COLOR << "Wood cost:               " << BOLD_GREEN << aux_node->get_value()->wood_cost << '\n';
    std::cout << DEFAULT_COLOR << "Steel cost:              " << BOLD_CYAN  << aux_node->get_value()->steel_cost << '\n';
    std::cout << DEFAULT_COLOR << "Amount of buildigns:     " << BOLD_BLUE  << amount_of_buildings_built << '\n';
    std::cout << DEFAULT_COLOR << "Amount allowed to build: " << BOLD_RED << aux_node->get_value()->max_quantity - amount_of_buildings_built << '\n';
    std::cout << "\n" << BOLD_VIOLET << DIVISORY_LINE << DEFAULT_COLOR << "\n" << "\n";

    aux_node = aux_node->get_next_node();

  }

}

string Record::get_current_building_type() {

  if (!record->current_node_null()) {

    string building_type = record->get_current_value()->building_type;

    return building_type;

  }

  return "0";

}

int Record::get_stone_cost(string building_type) {

  record->reset_current_node();

  while (record->get_current_value() != 0) {

    if (record->get_current_value()->building_type == building_type)
      return record->get_current_value()->stone_cost;

    record->next_node();

  }

  record->reset_current_node();

  return 0;

}

int Record::get_wood_cost(string building_type) {

  record->reset_current_node();

  while (record->get_current_value() != 0) {

    if (record->get_current_value()->building_type == building_type)
      return record->get_current_value()->wood_cost;

    record->next_node();

  }

  record->reset_current_node();

  return 0;

}

int Record::get_steel_cost(string building_type) {

  record->reset_current_node();

  while (record->get_current_value() != 0) {

    if (record->get_current_value()->building_type == building_type)
      return record->get_current_value()->steel_cost;

    record->next_node();

  }

  record->reset_current_node();

  return 0;

}

bool Record::validate_building_type(string building_type) {

  bool valid_type = false;

  record->reset_current_node();

  while (!valid_type && record->get_current_value() != 0) {

    if (record->get_current_value()->building_type == building_type)
      valid_type = true;

    record->next_node();

  }

  record->reset_current_node();

  return valid_type;

}

bool Record::validate_building_amount(string building_type, int amount_of_buildings_built) {

  record->reset_current_node();

  bool valid_amount = false;

  while (!valid_amount && record->get_current_value() != 0) {

    if (record->get_current_value()->building_type == building_type
        && amount_of_buildings_built + 1 <= record->get_current_value()->max_quantity)
      valid_amount = true;

    record->next_node();

  }

  record->reset_current_node();

  return valid_amount;

}

bool Record::validate_material_requirement(string building_type, int stone_amount,
                                            int wood_amount, int steel_amount) {

  record->reset_current_node();

  bool enough_materials = false;

  while (!enough_materials && record->get_current_value() != 0) {

    if (record->get_current_value()->building_type == building_type
        && record->get_current_value()->stone_cost <= stone_amount
        && record->get_current_value()->wood_cost <= wood_amount
        && record->get_current_value()->steel_cost <= steel_amount)
        {

          enough_materials = true;

    }

    record->next_node();

  }

  record->reset_current_node();

  return enough_materials;

}

void Record::reset_current_node() {

  record->reset_current_node();

}

void Record::next_node() {

  record->next_node();

}

Record::~Record() {

  delete record;

}
