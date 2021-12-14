#include "file_utils.h"

bool load_materials(City* city) {

  ifstream file;
  file.open(MATERIAL_FILE_ROUTE);

  if (!file) {

    cout << BOLD_RED << "ERROR!:" <<  DEFAULT_COLOR << " Could not find file: "
                                     "'materiales.txt', ending program" << endl;
    return false;

  }

  string current_material;

  string quantity_of_material;

  while ((file.peek() != EOF)) {

    getline(file, current_material, ' ');
    getline(file, quantity_of_material);

    city->add_material(current_material, stoi(quantity_of_material));

  }


  file.close();
  return true;

}

bool load_buildings_attributes(City* city) {

  ifstream file;
  file.open(BUILDING_FILE_ROUTE);

  if (!file) {

    cout << BOLD_RED << "ERROR!: " << DEFAULT_COLOR << "Could not find file: "
                                      "'edificios.txt', ending program" << endl;

    return false;

  }

  string building_type;
  string stone_cost;
  string wood_cost;
  string steel_cost;
  string max_building_quantity;
  string auxiliar;

  while ((file.peek() != EOF)) {

    getline(file, building_type, ' ');

    if (building_type == POWER_PLANT)
      getline(file, auxiliar, ' ');

    getline(file, stone_cost, ' ');
    getline(file, wood_cost, ' ');
    getline(file, steel_cost, ' ');
    getline(file, max_building_quantity);

    city->add_building(building_type, stoi(stone_cost), stoi(wood_cost),
                        stoi(steel_cost), stoi(max_building_quantity));

  }

  file.close();
  return true;

}

bool load_buildings(City* city) {

  ifstream file;

  file.open(MAP_LOCATIONS_ROUTE);

  if (!file) {

    cout << BOLD_RED << "ERROR!:" <<  DEFAULT_COLOR << " Could not find file: "
                                     "'ubicaciones.txt', ending program" << endl;
    return false;

  }

  string element_type;
  string x_coordinate;
  string y_coordinate;
  string aux;

  while ((file.peek() != EOF)) {

    getline(file, element_type, ' ');
    getline(file, aux, '(');
    getline(file, x_coordinate, ',');
    getline(file, aux, ' ');
    getline(file, y_coordinate, ')');
    getline(file, aux);

    if (city->validate_building_type(element_type))
      city->add_building(element_type, stoi(x_coordinate), stoi(y_coordinate), true);

    else
      city->add_material_to_tile(element_type, stoi(x_coordinate), stoi(y_coordinate));

  }

  file.close();
  return true;

}

bool load_tiles(City* city) {

  ifstream file;
  file.open(MAP_FILE_ROUTE);

  if (!file) {

    cout << BOLD_RED << "ERROR!:" <<  DEFAULT_COLOR << " Could not find file: "
                                     "'mapa.txt', ending program" << endl;
    return false;

  }

  string total_of_rows;
  string total_of_columns;

  getline(file, total_of_rows, ' ');
  getline(file, total_of_columns);

  city->generate_map(stoi(total_of_rows), stoi(total_of_columns));

  string line;
  char tile_type;

  int current_row = 0;
  int current_column;

  while ((file.peek() != EOF)) {

    current_column = 0;

    getline(file, line);

    stringstream ss(line); //from API stringstream

    while (ss >> tile_type) {

      city->add_tile(tile_type, current_row, current_column);

      current_column++;

    }

    current_row++;

  }

  file.close();
  return true;

}
