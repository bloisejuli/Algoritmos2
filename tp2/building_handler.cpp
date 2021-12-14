#include "building_handler.h"

BuildingHandler::BuildingHandler() {

  buildings = new List<Building>;

}

void BuildingHandler::add_building(string building_type, string material_that_produce, int x_coordinate, int y_coordinate) {

  Building* new_building = 0;

  if (building_type == FACTORY)
    new_building = new Factory(building_type, material_that_produce, x_coordinate, y_coordinate);

  else if (building_type == MINE)
    new_building = new Mine(building_type, material_that_produce, x_coordinate, y_coordinate);

  else if (building_type == OBELISK)
    new_building = new Obelisk(building_type, material_that_produce, x_coordinate, y_coordinate);

  else if (building_type == POWER_PLANT)
    new_building = new PowerPlant(building_type, material_that_produce, x_coordinate, y_coordinate);

  else if (building_type == SAWMILL)
    new_building = new Sawmill(building_type, material_that_produce, x_coordinate, y_coordinate);

  else if (building_type == SCHOOL)
    new_building = new School(building_type, material_that_produce, x_coordinate, y_coordinate);


  buildings->add_node(new_building);

}

bool BuildingHandler::demolish_building(int x_coordinate, int y_coordinate) {

  buildings->reset_current_node();

  bool building_demolished = false;

  while (buildings->get_current_value() != 0 && building_demolished == false) {

    if (buildings->get_current_value()->get_x_coordinate() == x_coordinate &&
         buildings->get_current_value()->get_y_coordinate() == y_coordinate) {

        buildings->delete_current_node();

        building_demolished = true;

    }

    buildings->next_node();

  }

  buildings->reset_current_node();

  return building_demolished;

}

void BuildingHandler::show_buildings(string building_type, int amount_built) {

  buildings->reset_current_node();
  string coordinates = "";
  string capitalized_building_type = capitalize_word(building_type);
  int building_type_spacing = 17;

  while (buildings->get_current_value() != 0) {

    if (buildings->get_current_value()->get_type() == building_type) {
      coordinates = coordinates + "(" + to_string(buildings->get_current_value()->get_x_coordinate())
                    + ", " + to_string(buildings->get_current_value()->get_y_coordinate())
                    + ") ";

    }

    buildings->next_node();

  }

  if (capitalized_building_type == POWER_PLANT) {

    capitalized_building_type = "Planta eléctrica";
    building_type_spacing = 18;

  }

  std::cout << left << setw(15) << "Amount of building: " << BOLD_GREEN <<
             setw(building_type_spacing) << capitalized_building_type  << DEFAULT_COLOR <<
              setw(4) << "is: " << BOLD_BLUE << amount_built << DEFAULT_COLOR << setw(4) <<
              " in coordinates: " << BOLD_YELLOW << setw(WIDTH) << coordinates <<  DEFAULT_COLOR <<'\n';

}

int BuildingHandler::get_building_built_amount(string building_type_to_count) {

  buildings->reset_current_node();

  int building_amount = 0;

  while (buildings->get_current_value() != 0) {

    if (buildings->get_current_value()->get_type() == building_type_to_count)
      building_amount++;

    buildings->next_node();

  }

  return building_amount;

}

Building* BuildingHandler::get_building(string building_type, int x_coordinate, int y_coordinate) {

  while (buildings->get_current_value() != 0) {

    if (buildings->get_current_value()->get_type() == building_type
       && buildings->get_current_value()->get_x_coordinate() == x_coordinate
       && buildings->get_current_value()->get_y_coordinate() == y_coordinate) {

      return buildings->get_current_value();

    }

  }

  return 0;
}

int BuildingHandler::get_resources_amount(string building_type) {

  int total_amount = 0;

  buildings->reset_current_node();

  while (buildings->get_current_value() != 0) {

    if (buildings->get_current_value()->get_type() == building_type)
      total_amount += buildings->get_current_value()->produce_material();

    buildings->next_node();

  }

  return total_amount;

}

string BuildingHandler::get_resources_type(string building_type) {
  
  buildings->reset_current_node();

  while (buildings->get_current_value() != 0) {

    if (buildings->get_current_value()->get_type() == building_type)
      return buildings->get_current_value()->get_material_that_building_produces();

    buildings->next_node();

  }

  return "";
  
}

string BuildingHandler::building_data_to_string() {

  buildings->reset_current_node();

  string building_data;

  while (buildings->get_current_value() != 0) {

    building_data = building_data + buildings->get_current_value()->get_type() + " ";

    if (buildings->get_current_value()->get_type() == POWER_PLANT)
      building_data = building_data + "electrica ";

    building_data = building_data + "(";
    building_data = building_data + to_string(buildings->get_current_value()->get_x_coordinate()) + ", ";
    building_data = building_data + to_string(buildings->get_current_value()->get_y_coordinate()) + ") " + '\n';

    buildings->next_node();

  }

  buildings->reset_current_node();

  return building_data;

}

BuildingHandler::~BuildingHandler(){

  delete buildings;

}
