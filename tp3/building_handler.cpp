#include "building_handler.h"

BuildingHandler::BuildingHandler() {

  buildings = new List<Building>;

}

void BuildingHandler::add_building(string building_type, string material_that_produce, string icon_building, int x_coordinate, int y_coordinate, Player* current_player) {
  Building* new_building = 0;

  if (building_type == FACTORY)
    new_building = new Factory(building_type, material_that_produce, icon_building, x_coordinate, y_coordinate, current_player);

  else if (building_type == MINE)
    new_building = new Mine(building_type, material_that_produce, icon_building, x_coordinate, y_coordinate, current_player);

  else if (building_type == OBELISK)
    new_building = new Obelisk(building_type, material_that_produce, icon_building, x_coordinate, y_coordinate, current_player);

  else if (building_type == POWER_PLANT)
    new_building = new PowerPlant(building_type, material_that_produce, icon_building, x_coordinate, y_coordinate, current_player);

  else if (building_type == SAWMILL)
    new_building = new Sawmill(building_type, material_that_produce, icon_building, x_coordinate, y_coordinate, current_player);

  else if (building_type == SCHOOL)
    new_building = new School(building_type, material_that_produce, icon_building, x_coordinate, y_coordinate, current_player);

  else if (building_type == GOLD_MINE)
    new_building = new GoldMine(building_type, material_that_produce, icon_building, x_coordinate, y_coordinate, current_player);

  buildings->add_node(new_building);
}

bool BuildingHandler::demolish_building(int x_coordinate, int y_coordinate) {
  bool building_demolished = false;
  buildings->reset_current_node();

  while (buildings->get_current_value() != 0 && !building_demolished) {
    if (buildings->get_current_value()->get_x_coordinate() == x_coordinate &&
         buildings->get_current_value()->get_y_coordinate() == y_coordinate) {

      buildings->delete_current_node();
      building_demolished = true;
    }

    if(buildings->get_current_value() != 0)
      buildings->next_node();
  }

  buildings->reset_current_node();

  return building_demolished;
}

void BuildingHandler::show_buildings(Player* current_player, string building_type) {
  string type_being_counted = building_type;
  string coordinates = "";
  int amount_built = 0;

  buildings->reset_current_node();

  while (buildings->get_current_value() != 0) {

    if(buildings->get_current_value()->get_type() == type_being_counted
       && buildings->get_current_value()->get_owner() == current_player) {

      amount_built++;
      coordinates = coordinates + "(" + to_string(buildings->get_current_value()->get_x_coordinate())
                     + ", " + to_string(buildings->get_current_value()->get_y_coordinate()) + ") ";
    }

    buildings->next_node();
  }

  if (amount_built > 0)
        std::cout << left << setw(15) << "Amount of building: " << BOLD_GREEN <<
                   setw(10) << capitalize_word(type_being_counted)  << DEFAULT_COLOR <<
                    setw(4) << "is: " << BOLD_BLUE << amount_built << DEFAULT_COLOR << setw(4) <<
                    " in coordinates: " << BOLD_YELLOW << setw(WIDTH) << coordinates <<  DEFAULT_COLOR <<'\n';
}

int BuildingHandler::get_building_built_amount(string building_type_to_count, int player_id) {
  int building_amount = 0;
  buildings->reset_current_node();

  while (buildings->get_current_value() != 0) {
    if (buildings->get_current_value()->get_type() == building_type_to_count &&
        buildings->get_current_value()->get_owner()->get_id() == player_id) {

      building_amount++;
    }
    buildings->next_node();
  }
  return building_amount;
}

bool BuildingHandler::player_has_building_type(string building_type, Player* player) {
  bool has_at_least_one_building = false;
  buildings->reset_current_node();

  while (buildings->get_current_value() != 0) {
    if (buildings->get_current_value()->get_type() == building_type
        && buildings->get_current_value()->get_owner() == player) {

      has_at_least_one_building = true;
    }
    buildings->next_node();
  }
  return has_at_least_one_building;
}

Building* BuildingHandler::get_building(string building_type, int x_coordinate, int y_coordinate) {
  bool found_building = false;
  Building* wanted_building = 0;

  while (buildings->get_current_value() != 0 && !found_building) {
    if (buildings->get_current_value()->get_type() == building_type
       && buildings->get_current_value()->get_x_coordinate() == x_coordinate
       && buildings->get_current_value()->get_y_coordinate() == y_coordinate) {

      found_building = true;
      wanted_building = buildings->get_current_value();
    }
  }
  return wanted_building;
}

void BuildingHandler::produce_resources(Player* current_player) {
  buildings->reset_current_node();

  while (buildings->get_current_value() != 0) {
    if(buildings->get_current_value()->get_owner() == current_player)
      buildings->get_current_value()->produce_material();

    buildings->next_node();
  }
}

void BuildingHandler::collect_resources(int &stone_collected, int &wood_collected, int &steel_collected,
                                        int &energy_collected, int &gold_collected, Player* current_player) {
  buildings->reset_current_node();

  while (buildings->get_current_value() != 0) {

    if (buildings->get_current_value()->get_material_type() == STONE && buildings->get_current_value()->get_owner() == current_player)
      stone_collected += buildings->get_current_value()->collect_material();

    else if (buildings->get_current_value()->get_material_type() == WOOD && buildings->get_current_value()->get_owner() == current_player)
      wood_collected += buildings->get_current_value()->collect_material();

    else if (buildings->get_current_value()->get_material_type() == STEEL && buildings->get_current_value()->get_owner() == current_player)
      steel_collected += buildings->get_current_value()->collect_material();

    else if (buildings->get_current_value()->get_material_type() == ENERGY && buildings->get_current_value()->get_owner() == current_player)
      energy_collected += buildings->get_current_value()->collect_material();

    else if (buildings->get_current_value()->get_material_type() == GOLD && buildings->get_current_value()->get_owner() == current_player)
      gold_collected += buildings->get_current_value()->collect_material();

    buildings->next_node();
  }
}

bool BuildingHandler::player_has_buildings_to_repair(Player* player) {
  bool damaged_building = false;
  buildings->reset_current_node();

  while (buildings->get_current_value() != 0) {
    if (buildings->get_current_value()->get_owner() == player) {
      announce_damaged_buildings(damaged_building);
      damaged_building = true;
    }

    buildings->next_node();
  }
  return damaged_building;
}

string BuildingHandler::building_data_to_string(string saved_data, int player_id) {
  buildings->reset_current_node();

  while (buildings->get_current_value() != 0) {
    if (buildings->get_current_value()->get_owner()->get_id() == player_id) {
      saved_data = saved_data + buildings->get_current_value()->get_type();
      saved_data = saved_data + " (";
      saved_data = saved_data + to_string(buildings->get_current_value()->get_x_coordinate()) + ", ";
      saved_data = saved_data + to_string(buildings->get_current_value()->get_y_coordinate()) + ") " + '\n';
    }

    buildings->next_node();
  }
  buildings->reset_current_node();

  return saved_data;
}

bool BuildingHandler::announce_damaged_buildings(bool damaged_building) {
  if (buildings->get_current_value()->get_type() == FACTORY) {
    Factory* target_building = dynamic_cast<Factory*> (buildings->get_current_value());

    if (target_building->get_building_state()) {
      damaged_building = true;

      std::cout << "You have a " << BOLD_RED << "damaged " << BOLD_GREEN <<
        capitalize_word(FACTORY) << DEFAULT_COLOR << " in coordinates (" <<
          BOLD_YELLOW <<  target_building->get_x_coordinate() << ", " <<
            target_building->get_y_coordinate() << DEFAULT_COLOR << ")." << '\n';
    }
  }
  else if (buildings->get_current_value()->get_type() == MINE) {
    Mine* target_building = dynamic_cast<Mine*> (buildings->get_current_value());

    if (target_building->get_building_state()) {
      damaged_building = true;

      std::cout << "You have a " << BOLD_RED << "damaged " << BOLD_GREEN <<
        capitalize_word(MINE) << DEFAULT_COLOR << " in coordinates (" <<
          BOLD_YELLOW <<  target_building->get_x_coordinate() << ", " <<
            target_building->get_y_coordinate() << DEFAULT_COLOR << ")." << '\n';
    }
  }
  return damaged_building;
}

BuildingHandler::~BuildingHandler(){
  delete buildings;
}
