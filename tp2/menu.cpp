#include "menu.h"

using namespace std;

void Menu::show_menu() {

  std::cout << '\n';
  std::cout << "Welcome to " << BOLD_GREEN << "Andypolis Construction Menu"
                                  << DEFAULT_COLOR << ", options are: " << '\n';

  std::cout << BOLD_YELLOW << "[1]" << DEFAULT_COLOR << "  Build building by name." << '\n';
  std::cout << BOLD_YELLOW << "[2]" << DEFAULT_COLOR << "  List the buildings built." << '\n';
  std::cout << BOLD_YELLOW << "[3]" << DEFAULT_COLOR << "  List all buildings." << '\n';
  std::cout << BOLD_YELLOW << "[4]" << DEFAULT_COLOR << "  Demolish a building by coordinates." << '\n';
  std::cout << BOLD_YELLOW << "[5]" << DEFAULT_COLOR << "  Show map." << '\n';
  std::cout << BOLD_YELLOW << "[6]" << DEFAULT_COLOR << "  Consult coordinates." << '\n';
  std::cout << BOLD_YELLOW << "[7]" << DEFAULT_COLOR << "  Show inventory." << '\n';
  std::cout << BOLD_YELLOW << "[8]" << DEFAULT_COLOR << "  Collect resources." << '\n';
  std::cout << BOLD_YELLOW << "[9]" << DEFAULT_COLOR << "  Rain of materials." << '\n';
  std::cout << BOLD_YELLOW << "[10]" << DEFAULT_COLOR << " How do you turn this on." << '\n';
  std::cout << BOLD_YELLOW << "[11]" << DEFAULT_COLOR << " Save and exit." << '\n';

  return;

}

bool Menu::interpretate_user_input(City* city) {

  std::string user_option;

  std::cout << '\n' << "Please enter the option you want: ";

  std::cin >> user_option;

  while (!is_numeric(user_option) || stoi(user_option) < 1 || stoi(user_option) > 11) {

    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR
          << "Invalid option, please enter " << BOLD_CYAN <<
            "a number between 1 and 11: " << DEFAULT_COLOR;

    std::cin >> user_option;

  }

  int numeric_user_option = stoi(user_option);

  bool not_end_program = true;

  switch (numeric_user_option) {

    case BUILD:

      build(city);

      press_enter_to_continue();

      system (CLR_SCREEN);

      break;

    case BUILDINGS:

      city->show_buildings();

      press_enter_to_continue();

      system (CLR_SCREEN);

      break;

    case RECORD:

      city->show_record();

      press_enter_to_continue();

      system (CLR_SCREEN);

      break;

    case DEMOLISH:

      demolish(city);

      press_enter_to_continue();

      system (CLR_SCREEN);

      break;

    case MAP:

      system (CLR_SCREEN);

      city->show_map();

      press_enter_to_continue();

      system (CLR_SCREEN);

      break;

    case COORDINATE:
    {
      system (CLR_SCREEN);

      int x_coordinate = ask_user_x_coordinate(city);
      int y_coordinate = ask_user_y_coordinate(city);

      city->consult_tile(x_coordinate, y_coordinate);

      press_enter_to_continue();

      system (CLR_SCREEN);

      break;

    }

    case INVENTORY:

      system (CLR_SCREEN);

      city->show_materials();

      press_enter_to_continue();

      system (CLR_SCREEN);

      break;

    case COLLECT_RESOURCES:

      system (CLR_SCREEN);

      city->collect_resources();

      press_enter_to_continue();

      system (CLR_SCREEN);

      break;

    case MATERIAL_RAIN:

      system (CLR_SCREEN);

      city->material_rain();

      press_enter_to_continue();

      system (CLR_SCREEN);

      break;

    case HOW_DO_YOU_TURN_THIS_ON:

      how_do_you_turn_this_on();

      press_enter_to_continue();

      system (CLR_SCREEN);

      break;

    case EXIT:

      save_data(city);

      std::cout << "Hope you enjoyed the program!" << '\n';

      not_end_program = false;

      break;

  }

  return not_end_program;

}

void Menu::how_do_you_turn_this_on() {

  system (CLR_SCREEN);
  string problematic_line_1_part_1 = R"(/`-')";
  string problematic_line_1_part_2 = R"(( )         ( ))";
  string problematic_line_1_part_3 = R"( /`-'\)";

  string problematic_line_2_part_1 = R"(|   |)";
  string problematic_line_2_part_2 = R"(---\_Cobra_/---)";
  string problematic_line_2_part_3 = R"(|   |)";

  std::cout << '\n';
  std::cout << "                  BRRRRRRRRRRRRRRRRRRRRRR" << '\n';
  std::cout << "        _________" << '\n';
  std::cout << "       |         |" << '\n';
  std::cout << BOLD_BLUE << " _o_  _";
  std::cout << DEFAULT_COLOR << "| " << BOLD_BLUE << "___=___" << DEFAULT_COLOR <<" |";
  std::cout << BOLD_BLUE << "_  _o_" << '\n';
  std::cout << problematic_line_1_part_1;
  std::cout << DEFAULT_COLOR << problematic_line_1_part_2;
  std::cout << BOLD_BLUE << problematic_line_1_part_3 << '\n';
  std::cout << BOLD_BLACK << "|   |-"<< BOLD_BLUE << "| ";
  std::cout << DEFAULT_COLOR << " ___*___ ";
  std::cout << BOLD_BLUE << " |" << BOLD_BLACK << "-|   |" << '\n';
  std::cout << "|   |" << BOLD_BLUE << " | ";
  std::cout << BOLD_BLACK << "(-+-+-+-)";
  std::cout << BOLD_BLUE << " |" << BOLD_BLACK <<" |   |" << '\n';
  std::cout << problematic_line_2_part_1;
  std::cout << DEFAULT_COLOR << problematic_line_2_part_2;
  std::cout << BOLD_BLACK << problematic_line_2_part_3 << '\n';
  std::cout << BOLD_BLACK << " ---                 ---" << DEFAULT_COLOR << '\n';

}

void Menu::press_enter_to_continue() {

  std::cout << '\n';
  std::cin.ignore();
  std::cout << "Press ENTER to go back to the menu: ";
  std::cin.get();

}

void Menu::build(City* city) {

  system (CLR_SCREEN);

  string building_to_add;

  std::cout << "Enter the type of building you wish to build (type '" << BOLD_GREEN <<
             "exit" << DEFAULT_COLOR << "' to go back to menu): ";

  std::cin >> building_to_add;

  if (building_to_add == POWER_PLANT) {

    string auxiliar;
    std::cin >> auxiliar;

  }

  while (!city->validate_building_type(lowercase_word(building_to_add)) && building_to_add != "exit") {

    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "Please Enter a valid type: ";
    std::cin >> building_to_add;

  }

  if (building_to_add != "exit") {

    std::cout << '\n';

    int x_coordinate = ask_user_x_coordinate(city);
    int y_coordinate = ask_user_y_coordinate(city);

    city->add_building(building_to_add, x_coordinate, y_coordinate, false);

  }

}

void Menu::demolish(City* city) {

  system (CLR_SCREEN);

  int x_coordinate = ask_user_x_coordinate(city);
  int y_coordinate = ask_user_y_coordinate(city);

  city->demolish_building(x_coordinate, y_coordinate);

}

void Menu::save_data(City* city) {

  fstream material_file;
  material_file.open(MATERIAL_FILE_ROUTE, ios::out);

  if (material_file.is_open()) {

    material_file << city->materials_data_to_string();

    material_file.close();

  }

  fstream building_file;
  building_file.open(MAP_LOCATIONS_ROUTE, ios::out);

  if (building_file.is_open()) {

    building_file << city->building_data_to_string();

    building_file.close();

  }

}

int Menu::ask_user_x_coordinate(City* city) {

  int max_rows = city->get_max_rows();

  string x_coordinate;

  std::cout << "Enter the " << BOLD_YELLOW << "X" << DEFAULT_COLOR << " coordinate of building you wish to build: ";
  std::cin >> x_coordinate;

  while (!is_numeric(x_coordinate) || stoi(x_coordinate) < 0 || stoi(x_coordinate) > max_rows - 1) {

  std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << BOLD_YELLOW << "X" << DEFAULT_COLOR <<
              " coordinate must be a number between" << BOLD_YELLOW << " 0 and " << max_rows - 1 << DEFAULT_COLOR << ": ";
  std::cin >> x_coordinate;

  }

  std::cout << '\n';

  return stoi(x_coordinate);

}

int Menu::ask_user_y_coordinate(City* city) {

  int max_columns = city->get_max_columns();

  string y_coordinate;

  std::cout << "Enter the " << BOLD_YELLOW << "Y" << DEFAULT_COLOR << " coordinate of building you wish to build: ";
  std::cin >> y_coordinate;

  while (!is_numeric(y_coordinate) || stoi(y_coordinate) < 0 || stoi(y_coordinate) > max_columns - 1) {

  std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << BOLD_YELLOW << "Y" << DEFAULT_COLOR <<
              " coordinate must be a number between" << BOLD_YELLOW << " 0 and " << max_columns - 1 << DEFAULT_COLOR << ": ";
  std::cin >> y_coordinate;

  }

  std::cout << '\n';

  return stoi(y_coordinate);

}
