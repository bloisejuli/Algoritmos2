#include "file_manager.h"

FileManager::FileManager() {}

void FileManager::load_materials(Player* player_1, Player* player_2) {

  ifstream file;
  file.open(MATERIAL_FILE_ROUTE);

  if (!file) {
    cout << BOLD_RED << "ERROR!:" <<  DEFAULT_COLOR << " Could not find file: "
          "'materiales.txt', this may cause an " << BOLD_RED << "unexpected unwanted behavior "
           << DEFAULT_COLOR << "in the functioning of the program" << endl;

  }
  else {

    string current_material;
    string quantity_of_material_player_1;
    string quantity_of_material_player_2;

    while ((file.peek() != EOF)) {
      getline(file, current_material, ' ');
      getline(file, quantity_of_material_player_1, ' ');
      getline(file, quantity_of_material_player_2);
      player_1->add_resource(current_material, stoi(quantity_of_material_player_1));
      player_2->add_resource(current_material, stoi(quantity_of_material_player_2));
    }

    player_1->add_resource(ENERGY, INITIAL_ENERGY);
    player_2->add_resource(ENERGY, INITIAL_ENERGY);
    file.close();

 }

}

void FileManager::load_default_materials(Player* player_1, Player* player_2) {
  player_1->add_resource(STONE, 0);
  player_1->add_resource(WOOD, 0);
  player_1->add_resource(STEEL, 0);
  player_1->add_resource(GOLD, 0);
  player_1->add_resource(BOMB, 0);
  player_1->add_resource(ENERGY, INITIAL_ENERGY);

  player_2->add_resource(STONE, 0);
  player_2->add_resource(WOOD, 0);
  player_2->add_resource(STEEL, 0);
  player_2->add_resource(GOLD, 0);
  player_2->add_resource(BOMB, 0);
  player_2->add_resource(ENERGY, INITIAL_ENERGY);
}

void FileManager::load_buildings_attributes(City* city) {
  ifstream file;
  file.open(BUILDING_FILE_ROUTE);

  if (!file) {
    cout << BOLD_RED << "ERROR!:" <<  DEFAULT_COLOR << " Could not find file: "
          "'edificios.txt', this may cause an " << BOLD_RED << "unexpected unwanted behavior "
           << DEFAULT_COLOR << "in the functioning of the program" << endl;

  }
  else {

    string building_type;
    string stone_cost;
    string wood_cost;
    string steel_cost;
    string max_building_quantity;
    string auxiliar;
    string building_types;

    while ((file.peek() != EOF)) {
      getline(file, building_type, ' ');
      getline(file, stone_cost, ' ');
      
      if (!is_numeric(stone_cost)) {
        building_type = building_type + ' ' + stone_cost;
        getline(file, stone_cost, ' ');
      }

      getline(file, wood_cost, ' ');
      getline(file, steel_cost, ' ');
      getline(file, max_building_quantity);

      city->add_building(building_type, stoi(stone_cost), stoi(wood_cost),
                          stoi(steel_cost), stoi(max_building_quantity));
      city->add_building_type(building_type);
    }
    file.close();
  }
}

bool FileManager::load_buildings(City* city, Player* player_1, Player* player_2) {
  Player* new_player;
  bool reading_a_player;

  ifstream file;

  file.open(MAP_LOCATIONS_ROUTE);

  if (!file) {
    cout << BOLD_YELLOW << "Warning!:" <<  DEFAULT_COLOR << " Could not find file: "
                                     "'ubicaciones.txt', starting new game." << endl;
    return true;
  }
  else {
    if(file.peek() == EOF) {
      cout << BOLD_YELLOW << "Warning!:"  <<  DEFAULT_COLOR << " file : 'ubicaciones.txt' "
                                       "is empty, starting new game." << endl;
      return true;
    }
    else {
      string element_type;
      string x_coordinate;
      string y_coordinate;
      string symbol_aux;
      string name_aux;

      while ((file.peek() != EOF)) {
        getline(file, element_type, ' ');
        getline(file, name_aux, '(');
        getline(file, x_coordinate, ',');
        getline(file, symbol_aux, ' ');
        getline(file, y_coordinate, ')');
        getline(file, symbol_aux);

        if(!is_numeric(name_aux)) {
          element_type = element_type + " " + name_aux;
          element_type.pop_back();
        }

        reading_a_player = false;

        if(is_numeric(element_type)) {
          reading_a_player = true;

          if(element_type == "1") {
            new_player = player_1;
          }
          else {
            new_player = player_2;
          }

          city->spawn_player(new_player, stoi(x_coordinate), stoi(y_coordinate));
        }

        if (city->validate_building_type(element_type)) {
          bool loading_from_txt = true;
          int player_stone = 0;
          int player_wood = 0;
          int player_steel = 0;

          city->add_building(element_type, stoi(x_coordinate), stoi(y_coordinate), loading_from_txt,
                             player_stone, player_wood, player_steel, new_player);
        }
        else if (!city->validate_building_type(element_type) && !reading_a_player)
          city->place_material_on_map(element_type, stoi(x_coordinate), stoi(y_coordinate));
      }
      file.close();
      return false;
    }
  }
}

void FileManager::load_tiles(City* city, Graph* graph_player_1, Graph* graph_player_2) {
  ifstream file;
  file.open(MAP_FILE_ROUTE);

  if (!file) {
    cout << BOLD_RED << "ERROR!:" <<  DEFAULT_COLOR << " Could not find file: "
          "'mapa.txt', this may cause an " << BOLD_RED << "unexpected unwanted behavior "
           << DEFAULT_COLOR << "in the functioning of the program" << endl;
  }
  else {
    string total_of_rows;
    string total_of_columns;
    getline(file, total_of_rows, ' ');
    getline(file, total_of_columns);

    city->generate_map(stoi(total_of_rows), stoi(total_of_columns));

    string line;
    char tile_type;
    int current_row = 0;
    int current_column;
    int weight;
    char auxiliar_type;

    while ((file.peek() != EOF)) {
      current_column = 0;
      getline(file, line);
      stringstream ss(line); //from API stringstream

      while (ss >> tile_type) {
        city->add_tile(tile_type, current_row, current_column);
        graph_player_1->add_vertex(current_row, current_column, tile_type);
        graph_player_2->add_vertex(current_row, current_column, tile_type);

        if (current_row != 0) {
          auxiliar_type = graph_player_1->get_tile_type(current_row - 1, current_column);
          weight = get_weight(auxiliar_type, 1);
          graph_player_1->add_path(current_row, current_column, current_row - 1, current_column, weight);
          weight = get_weight(tile_type, 1);
          graph_player_1->add_path(current_row - 1, current_column, current_row, current_column, weight);

          weight = get_weight(auxiliar_type, 2);
          graph_player_2->add_path(current_row, current_column, current_row - 1, current_column, weight);
          weight = get_weight(tile_type, 2);
          graph_player_2->add_path(current_row - 1, current_column, current_row, current_column, weight);
        }

        if (current_column != 0) {
          auxiliar_type = graph_player_1->get_tile_type(current_row, current_column - 1);
          weight = get_weight(auxiliar_type, 1);
          graph_player_1->add_path(current_row, current_column, current_row, current_column - 1, weight);
          weight = get_weight(tile_type, 1);
          graph_player_1->add_path(current_row, current_column - 1, current_row, current_column, weight);

          weight = get_weight(auxiliar_type, 2);
          graph_player_2->add_path(current_row, current_column, current_row, current_column - 1, weight);
          weight = get_weight(tile_type, 2);
          graph_player_2->add_path(current_row, current_column - 1, current_row, current_column, weight);
        }
        current_column++;
      }
      current_row++;
    }
    file.close();
  }
}
