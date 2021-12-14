#include "record.h"

Record::Record() {

  record = new BinarySearchTree;

}

void Record::add_building(string building_type, int stone_cost, int wood_cost,
                           int steel_cost, int max_building_quantity) {

    record->insert(building_type, stone_cost, wood_cost, steel_cost, max_building_quantity);

}

void Record::modify_building_amount(string building_type, int modifier, int player_id) {

  record->modify_built_amount(building_type, modifier, player_id);

}

void Record::show_record(int user_stone, int user_wood, int user_steel, int player_id) {

  std::cout << "All the types of buildings are:" << '\n';

  std::cout << "(Names in "<< BOLD_GREEN << "green" << DEFAULT_COLOR
             << " are buildings you can build, " << BOLD_RED << "red"
              << DEFAULT_COLOR << " are the one you can't)" << '\n' << '\n';

  record->show_builings(user_stone, user_wood, user_steel, player_id);

}


int Record::get_stone_cost(string building_type) {

  return record->get_building_stone_cost(building_type);

}

int Record::get_wood_cost(string building_type) {

  return record->get_building_wood_cost(building_type);

}

int Record::get_steel_cost(string building_type) {

  return record->get_building_steel_cost(building_type);

}

bool Record::validate_building_type(string building_type) {

  return record->validate_building_type(building_type);

}

bool Record::validate_building_amount(string building_type, int player_id) {

  return record->validate_building_amount(building_type, player_id);

}

bool Record::validate_material_requirement(string building_type, int stone_amount,
                                            int wood_amount, int steel_amount) {

  return record->validate_material_requirement(building_type, stone_amount,
                                                wood_amount, steel_amount);

}

void Record::modify_building_costs(string building_type) {

  string new_cost;

  std::cout << "Building: " << BOLD_GREEN << building_type << DEFAULT_COLOR << ", current " <<
        BOLD_BLACK << "stone " << DEFAULT_COLOR << "cost is: "  << BOLD_BLUE <<
         record->get_building_stone_cost(building_type) << DEFAULT_COLOR << '\n';

  std::cout << "Enter " << BOLD_BLUE << "new cost" << DEFAULT_COLOR << ": or " <<
        BOLD_GREEN << "'skip'" << DEFAULT_COLOR << " to keep the current value: ";



  std::cin >> new_cost;

  //hacer una validacion aca con skip
  new_cost = validate_new_material_cost(new_cost);

  if (new_cost != "skip")
    record->modify_building_stone_cost(building_type, stoi(new_cost));

  std::cout << "Building: " << BOLD_GREEN << building_type << DEFAULT_COLOR << ", current " <<
        BOLD_GREEN << "wood " << DEFAULT_COLOR << "cost is: "  << BOLD_BLUE <<
         record->get_building_wood_cost(building_type) << DEFAULT_COLOR << '\n';

  std::cout << "Enter " << BOLD_BLUE << "new cost" << DEFAULT_COLOR << ": or " <<
        BOLD_GREEN << "'skip'" << DEFAULT_COLOR << " to keep the current value: ";

  std::cin >> new_cost;

  new_cost = validate_new_material_cost(new_cost);

  if (new_cost != "skip")
    record->modify_building_wood_cost(building_type, stoi(new_cost));

  std::cout << "Building: " << BOLD_GREEN << building_type << DEFAULT_COLOR << ", current " <<
        BOLD_CYAN << "steel " << DEFAULT_COLOR << "cost is: "  << BOLD_BLUE <<
         record->get_building_steel_cost(building_type) << DEFAULT_COLOR << '\n';

 std::cout << "Enter " << BOLD_BLUE << "new cost" << DEFAULT_COLOR << ": or " <<
       BOLD_GREEN << "'skip'" << DEFAULT_COLOR << " to keep the current value: ";

  std::cin >> new_cost;

  new_cost = validate_new_material_cost(new_cost);

  if (new_cost != "skip")
    record->modify_building_steel_cost(building_type, stoi(new_cost));

}

int Record::get_building_max_amount(string building_type) {
  return record->get_building_max_amount(building_type);
}

string Record::validate_new_material_cost(string new_cost) {

  while (!is_numeric(new_cost) || (stoll(new_cost) < 1 || stoll(new_cost) > 50000) ) {

    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR
          << "Invalid option, please enter " << BOLD_CYAN <<
           "a number between 1 and 50000" << DEFAULT_COLOR << " or just enter " <<
             BOLD_GREEN << "'skip'" << DEFAULT_COLOR << ": ";

    std::cin >> new_cost;

  }

  return new_cost;

}

string Record::record_data_to_string() {

  return record->building_data_to_string();;

}

Record::~Record() {

  delete record;

}
