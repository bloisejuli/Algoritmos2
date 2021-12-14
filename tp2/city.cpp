#include "city.h"


City::City() {

  buildings = new BuildingHandler;
  materials = new MaterialHandler;
  record = new Record;
  city_map = 0;

  passable_tiles = new EmptyPassableTiles;

}


//--------------------------Material Management---------------------------------

void City::add_material(string material, int quantity) {

  string lowercase_material = lowercase_word(material);

  materials->add_material(lowercase_material, quantity);

}

void City::show_materials() {

  materials->show_materials();

}

void City::collect_resources() {

  string current_building_type;
  string material_produced;
  int user_material_amount;
  int produce_material_amount;

  record->reset_current_node();

  std::cout << BOLD_GREEN << "You collected the following resources:" << DEFAULT_COLOR << '\n' << '\n';

  while (record->get_current_building_type() != "0") {

    current_building_type = record->get_current_building_type();

    material_produced = buildings->get_resources_type(current_building_type);

    produce_material_amount = buildings->get_resources_amount(current_building_type);

    user_material_amount = materials->get_material_amount(material_produced);

    materials->set_material_amount(material_produced, user_material_amount + produce_material_amount);

    if (produce_material_amount > 0) {
      std::cout << left << setw(WIDTH) << "Material: " << BOLD_GREEN << setw(WIDTH) << material_produced <<
                   DEFAULT_COLOR << setw(WIDTH) << "Amount: " << BOLD_BLUE << setw(WIDTH) <<
                    produce_material_amount << DEFAULT_COLOR << '\n';
    }

    record->next_node();

  }

}

void City::material_rain() {

  if (!passable_tiles->not_empty_tiles()) {

    string material_type = materials->generate_random_material_type();

    int random_material_amount;

    srand ((unsigned)time(NULL));

    if (material_type == STONE)
      random_material_amount = rand() % 2 + 1;

    else if (material_type == STEEL)
      random_material_amount = rand() % 3 + 2;

    else if (material_type == WOOD)
      random_material_amount = rand() % 2;


    for (int i = 0; i < random_material_amount; i++) {

      if (passable_tiles->select_random_tile()) {

        int x_coordinate_target_tile = passable_tiles->get_target_tile_x_coordinate();
        int y_coordinate_target_tile = passable_tiles->get_target_tile_y_coordinate();

        passable_tiles->delete_target_tile();


        city_map->add_material(materials->generate_material(material_type), x_coordinate_target_tile, y_coordinate_target_tile);

      }

    }

    std::cout << "Rain of materials " << BOLD_GREEN << "successfully" << DEFAULT_COLOR << " casted." << '\n';

    std::cout << BOLD_BLUE << random_material_amount << DEFAULT_COLOR << " of material: " <<
               BOLD_GREEN << material_type << DEFAULT_COLOR << " was generated." << '\n';

  }

  else
    std::cout << BOLD_RED<< "ERROR: " << DEFAULT_COLOR << "all roads currently have a material on them."<< '\n';

}

string City::materials_data_to_string() {

  return materials->materials_data_to_string();

}

void City::add_material_to_tile(string material_type, int x_coordinate, int y_coordinate) {

  city_map->add_material(materials->generate_material(material_type), x_coordinate, y_coordinate);

}

//--------------------------Private Material Methods----------------------------

void City::set_material_amount(string material_to_modify, int new_quantity) {

  materials->set_material_amount(material_to_modify, new_quantity);

}

int City::get_material_amount(string target_material) {

  return materials->get_material_amount(target_material);

}

void City::deduct_building_cost(int user_stone, int user_wood, int user_steel, string building_type) {

  int stone_cost = record->get_stone_cost(building_type);
  int wood_cost = record->get_wood_cost(building_type);
  int steel_cost = record->get_steel_cost(building_type);

  materials->set_material_amount(STONE, user_stone - stone_cost);
  materials->set_material_amount(WOOD, user_wood - wood_cost);
  materials->set_material_amount(STEEL, user_steel - steel_cost);

}

void City::refund_building_cost(string building_type) {

  int user_stone = materials->get_material_amount(STONE);
  int user_wood = materials->get_material_amount(WOOD);
  int user_steel = materials->get_material_amount(STEEL);

  int stone_cost = record->get_stone_cost(building_type);
  int wood_cost = record->get_wood_cost(building_type);
  int steel_cost = record->get_steel_cost(building_type);

  materials->set_material_amount(STONE, user_stone + stone_cost / 2);
  materials->set_material_amount(WOOD, user_wood + wood_cost / 2);
  materials->set_material_amount(STEEL, user_steel + steel_cost / 2);

}

//-----------------------------Building Management------------------------------

void City::add_building(string building_type, int x_coordinate, int y_coordinate,
                         bool loading_from_txt){

  string lowercase_building_type = lowercase_word(building_type);
  string capitalized_building_type = capitalize_word(lowercase_building_type);

  bool valid_type = record->validate_building_type(lowercase_building_type);

  bool valid_tile = false;

  if (valid_type)
    valid_tile = city_map->tile_buildable(x_coordinate, y_coordinate);

  else
    valid_tile = true;


  bool empty_tile = false;

  if (valid_type && valid_tile)
    empty_tile = city_map->tile_empty(x_coordinate, y_coordinate);

  else
    empty_tile = true;


  bool valid_amount = false;

  if (valid_type && valid_tile && empty_tile && !loading_from_txt) {

    int amount_built = record->get_building_amount(lowercase_building_type);

    valid_amount = record->validate_building_amount(lowercase_building_type, amount_built);

  }


  else
    valid_amount = true;

  bool enough_materials = false;

  int user_stone = materials->get_material_amount(STONE);
  int user_wood = materials->get_material_amount(WOOD);
  int user_steel = materials->get_material_amount(STEEL);

  if (!loading_from_txt && valid_type && valid_amount && valid_tile && empty_tile)
    enough_materials = record->validate_material_requirement(lowercase_building_type,
                                            user_stone, user_wood, user_steel);

  else
    enough_materials = true;


  //Section related with building by user command
  if (valid_type && valid_tile && empty_tile && valid_amount && enough_materials && !loading_from_txt) {

    if (ask_user_confirmation(capitalized_building_type)) {

      string material_that_produces = get_resource_that_building_produces(lowercase_building_type);

      deduct_building_cost(user_stone, user_wood, user_steel, lowercase_building_type);

      add_building(lowercase_building_type, material_that_produces, x_coordinate, y_coordinate);

      std::cout << BOLD_GREEN<< "Building: " << capitalized_building_type
                  << ", successfully built." << DEFAULT_COLOR << '\n';

    }

    else {
      std::cout << BOLD_RED << "ERROR:" << DEFAULT_COLOR << " Building: "
                  << BOLD_GREEN << capitalized_building_type << DEFAULT_COLOR
                    << " wasn't successfully constucted."<< '\n';
    }

  }


  else if (!valid_type && valid_amount && enough_materials && valid_tile && empty_tile && !loading_from_txt)
    print_error_message(valid_type, valid_amount, enough_materials, valid_tile, empty_tile, loading_from_txt, capitalized_building_type, x_coordinate, y_coordinate);

  else if (valid_type && !valid_amount && enough_materials && valid_tile && empty_tile && !loading_from_txt)
    print_error_message(valid_type, valid_amount, enough_materials, valid_tile, empty_tile, loading_from_txt, capitalized_building_type, x_coordinate, y_coordinate);

  else if (valid_type && valid_amount && !enough_materials && valid_tile && empty_tile && !loading_from_txt)
    print_error_message(valid_type, valid_amount, enough_materials, valid_tile, empty_tile, loading_from_txt, capitalized_building_type, x_coordinate, y_coordinate);

  else if (valid_type && valid_amount && enough_materials && !valid_tile && empty_tile && !loading_from_txt)
    print_error_message(valid_type, valid_amount, enough_materials, valid_tile, empty_tile, loading_from_txt, capitalized_building_type, x_coordinate, y_coordinate);

  else if (valid_type && valid_amount && enough_materials && valid_tile && !empty_tile && !loading_from_txt)
    print_error_message(valid_type, valid_amount, enough_materials, valid_tile, empty_tile, loading_from_txt, capitalized_building_type, x_coordinate, y_coordinate);


  //Section related with building by txt file
  if (valid_type && valid_tile && empty_tile && loading_from_txt) {

    string material_that_produces = get_resource_that_building_produces(lowercase_building_type);

    add_building(lowercase_building_type, material_that_produces, x_coordinate, y_coordinate);

  }

  else if (valid_type && !valid_tile && empty_tile && loading_from_txt)
    print_error_message(valid_type, true, true, valid_tile, empty_tile, loading_from_txt, capitalized_building_type, x_coordinate, y_coordinate);

  else if (valid_type && valid_tile && !empty_tile && loading_from_txt)
    print_error_message(valid_type, true, true, valid_tile, empty_tile, loading_from_txt, capitalized_building_type, x_coordinate, y_coordinate);

}


void City::demolish_building(int x_coordinate, int y_coordinate) {

  bool valid_tile = city_map->tile_buildable(x_coordinate, y_coordinate);

  bool empty_tile = true;

  if (valid_tile) {

    empty_tile = city_map->tile_empty(x_coordinate, y_coordinate);

  }

  string building_type;
  string capitalized_building_type;
  string lowercase_building_type;

  bool building_demolished = false;

  if (valid_tile && !empty_tile) {

    building_type = city_map->get_building_type(x_coordinate, y_coordinate);
    capitalized_building_type = capitalize_word(building_type);
    lowercase_building_type = lowercase_word(building_type);

    building_demolished = buildings->demolish_building(x_coordinate, y_coordinate);
    city_map->remove_building(x_coordinate, y_coordinate);

  }


  if (building_demolished) {

    record->modify_building_amount(building_type, -1);

    refund_building_cost(lowercase_building_type);

  }

  if (building_demolished)
    std::cout << BOLD_GREEN << "Building: '" << capitalized_building_type <<
                            "' successfully demolish." << DEFAULT_COLOR << '\n';

  else if (valid_tile && empty_tile)
    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "There isn't"
               " a building in tile with coordinates: (" << BOLD_YELLOW <<
                x_coordinate << ", " << y_coordinate << DEFAULT_COLOR << ")" << '\n';

  else if (!valid_tile && empty_tile)
    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "The tile with coordinates: ("
               << BOLD_YELLOW << x_coordinate << ", " << y_coordinate << DEFAULT_COLOR <<
               ") is not suited for building." << '\n';

}


void City::show_buildings() {

  system (CLR_SCREEN);

  record->reset_current_node();

  while(record->get_current_building_type() != "0"){

    int amount_built = buildings->get_building_built_amount(record->get_current_building_type());

    if(amount_built > 0){

      buildings->show_buildings(record->get_current_building_type(), amount_built);

    }

    record->next_node();

  }

}


bool City::validate_building_type(string type_to_check){

  return record->validate_building_type(type_to_check);

}


//--------------------------Private Building Management-------------------------

void City::add_building(string building_type, string material_that_produce, int x_coordinate, int y_coordinate) {

  buildings->add_building(building_type, material_that_produce, x_coordinate, y_coordinate);
  record->modify_building_amount(building_type, 1);
  Building* new_building = buildings->get_building(building_type, x_coordinate, y_coordinate);
  city_map->add_building(new_building, x_coordinate, y_coordinate);

}

void City::print_error_message(bool valid_type, bool valid_amount, bool enough_materials,
                          bool valid_tile, bool empty_tile, bool loading_from_txt,
                           string building_type, int x_coordinate, int y_coordinate) {

  if (!valid_type && valid_amount && enough_materials && valid_tile && empty_tile && !loading_from_txt) {
    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR <<
                 "Invalid building type: " << building_type <<
                  ", check menu option '4' to see all valid types." << '\n';
  }

  else if (valid_type && !valid_amount && enough_materials && valid_tile && empty_tile && !loading_from_txt) {
  std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "Building type: " <<
                building_type << " surpasses max quantity allow,"
                " check menu option '3' to see amount built and max quantity allow ." << '\n';
  }

  else if (valid_type && valid_amount && !enough_materials && valid_tile && empty_tile && !loading_from_txt) {
    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR <<
                  "You don't have enough materials to build building: " <<
                    building_type << ", check menu option '7' and '3' to see "
                     "materials amount and building costs." << '\n';
  }

  else if (valid_type && valid_amount && enough_materials && !valid_tile && empty_tile && !loading_from_txt) {
    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR <<
                  "The tile where you are trying to build on is not meant for building,"
                    " check menu option '5' to see the map with all the buildable tiles." << '\n';
  }


  else if (valid_type && valid_amount && enough_materials && valid_tile && !empty_tile && !loading_from_txt) {
    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR <<
                  "The tile where you are trying to build already has a building in it,"
                    " check menu option '5' to see the map with all the built buildings." << '\n';
  }

  else if (valid_type && valid_amount && enough_materials && !valid_tile && empty_tile && loading_from_txt) {

    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "Invalid tile for building: " <<
               BOLD_GREEN << building_type << DEFAULT_COLOR << ", coordinates: (" <<
                BOLD_YELLOW << x_coordinate << ", " << y_coordinate << DEFAULT_COLOR <<
                 ") in file: " << BOLD_BLUE << MAP_LOCATIONS_ROUTE << DEFAULT_COLOR << '\n';

    std::cout << BOLD_RED << "Building: " << building_type << " wasn't built" << DEFAULT_COLOR << '\n';

  }

  else if (valid_type && valid_amount && enough_materials && valid_tile && !empty_tile && loading_from_txt) {

    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "Tile: (" <<
               BOLD_YELLOW << x_coordinate << ", " << y_coordinate << DEFAULT_COLOR <<
                ") in file: " << BOLD_BLUE << MAP_LOCATIONS_ROUTE << DEFAULT_COLOR <<
                 " already has a building in it" <<'\n';

    std::cout << BOLD_RED << "Building: " << building_type << " wasn't built" << DEFAULT_COLOR << '\n';

  }


}

string City::get_resource_that_building_produces(string building_type) {

  if (building_type == MINE)
    return STONE;

  else if (building_type == SAWMILL)
    return WOOD;

  else if (building_type == FACTORY)
    return STEEL;

  else
    return "";

}


//-----------------------------Record Management--------------------------------

void City::add_building(string building_type, int stone_cost, int wood_cost,
                        int steel_cost, int max_building_quantity) {

    record->add_building(building_type, stone_cost, wood_cost, steel_cost, max_building_quantity);

}


void City::show_record() {

  system (CLR_SCREEN);

  int user_stone = materials->get_material_amount(STONE);
  int user_wood = materials->get_material_amount(WOOD);
  int user_steel = materials->get_material_amount(STEEL);

  record->show_record(user_stone, user_wood, user_steel);

  std::cout << "Remember your current materials are: " << '\n';
  materials->show_materials();

}


string City::building_data_to_string() {

  string user_buildings = buildings->building_data_to_string();

  return city_map->materials_data_to_string(user_buildings);

}

//-------------------------------Map Management---------------------------------

void City::generate_map(int rows, int columns) {

  city_map = new Map(rows, columns);

}

void City::add_tile(char tile_type, int x_coordinate, int y_coordinate) {

  if (tile_type == ROAD)
    passable_tiles->add_empty_tile(x_coordinate, y_coordinate);

  city_map->add_tile(tile_type);

}

void City::consult_tile(int x_coordinate, int y_coordinate) {

  city_map->consult(x_coordinate, y_coordinate);

}

int City::get_max_rows() {

  return city_map->get_rows();

}

int City::get_max_columns() {

  return city_map->get_columns();

}

void City::show_map() {

  city_map->show_map();

}



//------------------------Private Map Management--------------------------------

//------------------------------------------------------------------------------

City::~City() {

  delete buildings;
  delete materials;
  delete record;
  delete city_map;
  delete passable_tiles;

}
