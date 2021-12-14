#include "city.h"


City::City() {
  buildings = new BuildingHandler;
  record = new Record;
  city_map = 0;
  passable_tiles = new EmptyPassableTiles;
  building_types = new List<string>;
}

//--------------------------Material Management---------------------------------

void City::produce_resources(Player* current_player) {
  buildings->produce_resources(current_player);
}

void City::collect_resources(int &stone_collected, int &wood_collected, int &steel_collected,
                              int &energy_collected, int &gold_collected, Player* current_player) {
  int stone_produced = 0;
  int wood_produced = 0;
  int steel_produced = 0;
  int energy_produced = 0;
  int gold_produced = 0;

  buildings->collect_resources(stone_produced, wood_produced, steel_produced,
                                energy_produced, gold_produced, current_player);

  stone_collected = stone_produced;
  wood_collected  = wood_produced;
  steel_collected = steel_produced;
  energy_collected = energy_produced;
  gold_collected = gold_produced;
}

void City::material_rain() {

  if(!passable_tiles->not_empty_tiles()) {
    bool still_empty_tiles = true;
    int random_stone_amount = rand() % 2 + 1;
    int random_steel_amount = rand() % 3 + 2;
    int random_wood_amount = rand() % 4;
    int random_andycoins_amount = rand() % 2;

    still_empty_tiles =  place_material_on_map(random_stone_amount, STONE);

    if(still_empty_tiles)
        still_empty_tiles =  place_material_on_map(random_steel_amount, STEEL);

    if(still_empty_tiles)
        still_empty_tiles =  place_material_on_map(random_wood_amount, WOOD);

    if(still_empty_tiles)
        still_empty_tiles =  place_material_on_map(random_andycoins_amount, GOLD);

    std::cout << '\n' << "Rain of materials " << BOLD_GREEN << "successfully" << DEFAULT_COLOR << " casted." << '\n';
  }
  else
    std::cout << BOLD_YELLOW << "Caution: " << DEFAULT_COLOR << "all passable tiles currently have a material on them." <<
      '\n' << "Rain of materials " << BOLD_RED << "wasn't" << DEFAULT_COLOR << " casted." << '\n';
}

int City::get_material_cost(string building_type, string material_type) {
  int material_cost;

  if(material_type == STONE)
      material_cost = record->get_stone_cost(building_type);
  else if(material_type == WOOD)
      material_cost = record->get_wood_cost(building_type);
  else if(material_type == STEEL)
      material_cost = record->get_steel_cost(building_type);

  return material_cost;
}

void City::place_material_on_map(string material_type, int x_coordinate, int y_coordinate) {
  city_map->add_material(generate_material(material_type),x_coordinate, y_coordinate);
  passable_tiles->search_tile(x_coordinate, y_coordinate);
}

//--------------------------Private Material Methods----------------------------

Material* City::generate_material(string material_type) {
    int quantity = 0;

    if(material_type == STONE)
        quantity = STONE_UNITS;
    else if(material_type == WOOD || material_type == STEEL)
        quantity = WOOD_OR_STEEL_UNITS;
    else if(material_type == GOLD)
        quantity = GOLD_UNITS;

    Material* new_material = new Material(material_type, quantity);

    return new_material;
}

void City::show_material_rain_announcement( int amount_droped, string material_type) {
    std::cout << BOLD_BLUE << amount_droped << DEFAULT_COLOR << " of material: " <<
              BOLD_GREEN << material_type << DEFAULT_COLOR << " was generated." << '\n';
}

bool City::place_material_on_map(int amount_of_drops, string material_type) {
    bool not_empty_tiles = false;

    if(amount_of_drops == 0)
      not_empty_tiles = true;

    int amount_droped = 0;

    for (int i = 0; i < amount_of_drops; i++) {
        if (passable_tiles->select_random_tile()) {
            not_empty_tiles = true;
            int x_coordinate_target_tile = passable_tiles->get_target_tile_x_coordinate();
            int y_coordinate_target_tile = passable_tiles->get_target_tile_y_coordinate();

            passable_tiles->delete_target_tile();

            city_map->add_material(generate_material(material_type),
                                   x_coordinate_target_tile, y_coordinate_target_tile);
            amount_droped++;
        }
        else
            not_empty_tiles = false;
    }
    show_material_rain_announcement(amount_droped, material_type);

    return not_empty_tiles;
}

//-----------------------------Building Management------------------------------

bool City::add_building(string building_type, int x_coordinate, int y_coordinate, bool loading_from_txt,
                         int player_stone, int player_wood, int player_steel, Player* current_player) {
  bool building_built = false;

  string lowercase_building_type = lowercase_word(building_type);
  string capitalized_building_type = capitalize_word(lowercase_building_type);

  bool valid_type = record->validate_building_type(lowercase_building_type);

  bool valid_tile = true;

  if (valid_type)
    valid_tile = city_map->tile_buildable(x_coordinate, y_coordinate);

  bool empty_tile = true;

  if (valid_type && valid_tile)
    empty_tile = city_map->tile_empty(x_coordinate, y_coordinate);

  bool valid_amount = true;

  if (valid_type && valid_tile && empty_tile)
    valid_amount = record->validate_building_amount(lowercase_building_type, current_player->get_id());

  bool enough_materials = true;

  if (!loading_from_txt && valid_type && valid_amount && valid_tile && empty_tile)
    enough_materials = record->validate_material_requirement(lowercase_building_type,
                                            player_stone, player_wood, player_steel);

  if (valid_type && valid_tile && empty_tile && valid_amount && enough_materials && !loading_from_txt) {
    bool user_confirmed = ask_user_confirmation(capitalized_building_type);
    if (user_confirmed) {
      string material_that_produces = get_resource_that_building_produces(lowercase_building_type);
      string icon_building = get_building_icon(lowercase_building_type);
      building_built = true;
      add_building(lowercase_building_type, material_that_produces, icon_building, x_coordinate, y_coordinate,
                   current_player);
    }
    announce_when_a_building_is_built(user_confirmed, capitalized_building_type);
  }
  else if (valid_type && valid_tile && empty_tile && valid_amount && enough_materials && loading_from_txt) {
    string material_that_produces = get_resource_that_building_produces(lowercase_building_type);
    string icon_building = get_building_icon(lowercase_building_type);
    add_building(lowercase_building_type, material_that_produces, icon_building, x_coordinate, y_coordinate, current_player);
    building_built = true;
  }
  else
    print_error_message(valid_type, valid_amount, enough_materials, valid_tile, empty_tile, loading_from_txt, capitalized_building_type, x_coordinate, y_coordinate);

  return building_built;
}

bool City::demolish_building(int x_coordinate, int y_coordinate, int player_id) {
  bool valid_tile = city_map->tile_buildable(x_coordinate, y_coordinate);
  bool empty_tile = true;

  if (valid_tile)
    empty_tile = city_map->tile_empty(x_coordinate, y_coordinate);

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

  if (building_demolished)
    record->modify_building_amount(building_type, -1, player_id);

  announce_when_a_building_is_demolished(building_demolished, valid_tile, empty_tile, capitalized_building_type,
                                         x_coordinate, y_coordinate);
  return building_demolished;
}

void City::destroy_building(int x_coordinate, int y_coordinate, int player_id) {

  string building_type = city_map->get_building_type(x_coordinate, y_coordinate);
  string capitalized_building_type = capitalize_word(building_type);

  buildings->demolish_building(x_coordinate, y_coordinate);
  city_map->remove_building(x_coordinate, y_coordinate);
  record->modify_building_amount(building_type, -1, player_id);
}

void City::show_buildings(Player* current_player) {
  system (CLR_SCREEN);

  building_types->reset_current_node();

  while (building_types->get_current_value() != 0) {
    string current_building_type = *building_types->get_current_value();
    buildings->show_buildings(current_player, current_building_type);
    building_types->next_node();
  }
}

bool City::validate_building_type(string type_to_check){
  return record->validate_building_type(type_to_check);
}

bool City::player_has_building_type(string building_type, Player* player) {
  return buildings->player_has_building_type(building_type, player);
}

bool City::player_has_buildings_to_repair(Player* player) {
  return buildings->player_has_buildings_to_repair(player);
}

bool City::player_built_max_amount_school(int player_id) {
  int schools_amount = buildings->get_building_built_amount(SCHOOL, player_id);
  int max_schools_amount = record->get_building_max_amount(SCHOOL);

  return schools_amount == max_schools_amount;
}

//--------------------------Private Building Management-------------------------

void City::add_building(string building_type, string material_that_produce, string icon_building, int x_coordinate,
                        int y_coordinate, Player* current_player) {

  buildings->add_building(building_type, material_that_produce, icon_building, x_coordinate, y_coordinate, current_player);
  record->modify_building_amount(building_type, 1, current_player->get_id());
  Building* new_building = buildings->get_building(building_type, x_coordinate, y_coordinate);
  city_map->add_building(new_building, x_coordinate, y_coordinate);
}

void City::print_error_message(bool valid_type, bool valid_amount, bool enough_materials,
                          bool valid_tile, bool empty_tile, bool loading_from_txt,
                           string building_type, int x_coordinate, int y_coordinate) {

  if (!valid_type && valid_amount && enough_materials && valid_tile && empty_tile && !loading_from_txt) {
    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR <<
                 "Invalid building type: " << building_type <<
                  ", check menu option '3' to see all valid types." << '\n';
  }
  else if (valid_type && !valid_amount && enough_materials && valid_tile && empty_tile && !loading_from_txt) {
  std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "Building type: " <<
                building_type << " surpasses max quantity allow,"
                " check menu option '3' to see amount built and max quantity allow ." << '\n';
  }
  else if (valid_type && valid_amount && !enough_materials && valid_tile && empty_tile && !loading_from_txt) {
    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR <<
                  "You don't have enough materials to build building: " <<
                    building_type << ", check menu option '10' and '3' to see "
                     "materials amount and building costs." << '\n';
  }
  else if (valid_type && valid_amount && enough_materials && !valid_tile && empty_tile && !loading_from_txt) {
    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR <<
                  "The tile where you are trying to build on is not meant for building,"
                    " check menu option '7' to see the map with all the buildable tiles." << '\n';
  }
  else if (valid_type && valid_amount && enough_materials && valid_tile && !empty_tile && !loading_from_txt) {
    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR <<
                  "The tile where you are trying to build already has a building in it,"
                    " check menu option '7' to see the map with all the built buildings." << '\n';
  }
  else if (valid_type && valid_amount && enough_materials && !valid_tile && empty_tile && loading_from_txt) {

    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "Invalid tile for building: " <<
               BOLD_GREEN << building_type << DEFAULT_COLOR << ", coordinates: (" <<
                BOLD_YELLOW << x_coordinate << ", " << y_coordinate << DEFAULT_COLOR <<
                 ") in file: " << BOLD_BLUE << MAP_LOCATIONS_ROUTE << DEFAULT_COLOR << '\n';

    std::cout << BOLD_RED << "Building: " << building_type << " wasn't built" << DEFAULT_COLOR << '\n' << '\n';
  }
  else if (valid_type && valid_amount && enough_materials && valid_tile && !empty_tile && loading_from_txt) {

    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "Tile: (" <<
               BOLD_YELLOW << x_coordinate << ", " << y_coordinate << DEFAULT_COLOR <<
                ") in file: " << BOLD_BLUE << MAP_LOCATIONS_ROUTE << DEFAULT_COLOR <<
                 " already has a building in it" <<'\n';

    std::cout << BOLD_RED << "Building: " << building_type << " wasn't built" << DEFAULT_COLOR << '\n' << '\n';
  }
  else if (valid_type && !valid_amount && enough_materials && valid_tile && empty_tile && loading_from_txt) {

    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "Building type: " <<
                  BOLD_GREEN << building_type << DEFAULT_COLOR << " in coordinates (" <<
                  BOLD_YELLOW <<  x_coordinate << ", " << y_coordinate << DEFAULT_COLOR
                    << ") surpasses max quantity allow." << '\n';

    std::cout << BOLD_RED << "Building: " << building_type << " wasn't built" << DEFAULT_COLOR << '\n' << '\n';
  }
}

void City::announce_when_a_building_is_demolished(bool building_demolished, bool valid_tile, bool empty_tile,
                                                  string building_type, int x_coordinate, int y_coordinate) {

  if (building_demolished)
    std::cout << BOLD_GREEN << "Building: '" << building_type <<
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

void City::announce_when_a_building_is_built(bool user_confirmed, string building_type) {
    if(user_confirmed)
        std::cout << BOLD_GREEN << "Building: " << building_type
                  << ", successfully built." << DEFAULT_COLOR << '\n';
    else
      std::cout << BOLD_RED << "ERROR:" << DEFAULT_COLOR << " Building: "
                  << BOLD_GREEN << building_type << DEFAULT_COLOR
                    << " wasn't successfully constucted."<< '\n';
}

string City::get_resource_that_building_produces(string building_type) {
  string material_type = "";

  if (building_type == MINE)
    material_type = STONE;
  else if (building_type == SAWMILL)
    material_type = WOOD;
  else if (building_type == FACTORY)
    material_type = STEEL;
  else if (building_type == SCHOOL)
    material_type = GOLD;
  else if (building_type == GOLD_MINE)
    material_type = GOLD;
  else if (building_type == POWER_PLANT)
    material_type = ENERGY;

  return material_type;
}

string City::get_building_icon(string building_type) {
   string icon = "";

  if (building_type == MINE)
    icon = MINE_ICON;
  else if (building_type == SAWMILL)
    icon = SAWMILL_ICON;
  else if (building_type == FACTORY)
    icon = FACTORY_ICON;
  else if (building_type == SCHOOL)
    icon = SCHOOL_ICON;
  else if (building_type == GOLD_MINE)
    icon = GOLD_MINE_ICON;
  else if (building_type == POWER_PLANT)
    icon = POWER_PLANT_ICON;
  else if (building_type == OBELISK)
    icon = OBELISK_ICON;

  return icon;
}

//-----------------------------Record Management--------------------------------

void City::add_building(string building_type, int stone_cost, int wood_cost,
                        int steel_cost, int max_building_quantity) {
  record->add_building(building_type, stone_cost, wood_cost, steel_cost, max_building_quantity);
}

void City::add_building_type(string building_type) {
  string* new_building_type = new string;
  *new_building_type = building_type;
  building_types->add_node(new_building_type);
}


void City::show_record(int user_stone, int user_wood, int user_steel, int player_id) {
  system (CLR_SCREEN);

  record->show_record(user_stone, user_wood, user_steel, player_id);
}

void City::modify_building_costs(string building_type) {
  record->modify_building_costs(building_type);
}

string City::record_data_to_string() {
  return record->record_data_to_string();
}

//-------------------------------Map Management---------------------------------


void City::generate_map(int rows, int columns) {
  city_map = new Map(rows, columns);
}

void City::add_tile(char tile_type, int x_coordinate, int y_coordinate) {
  if (tile_type == ROAD || tile_type == BITUMEN || tile_type == DOCK)
    passable_tiles->add_empty_tile(x_coordinate, y_coordinate);

  city_map->add_tile(tile_type);
}

void City::consult_tile(int x_coordinate, int y_coordinate, Player* player_1, Player* player_2) {
  city_map->consult(x_coordinate, y_coordinate, player_1, player_2);
}

int City::get_max_rows() {
  return city_map->get_rows();
}

int City::get_max_columns() {
  return city_map->get_columns();
}

void City::show_map(bool legend_visibility, int player_id) {
    city_map->show_map(legend_visibility, player_id);
}

string City::get_target_building_type(int x_coordinate, int y_coordinate) {
  return city_map->get_building_type(x_coordinate, y_coordinate);
}

bool City::tile_buildable(int x_coordinate, int y_coordinate) {
  return city_map->tile_buildable(x_coordinate, y_coordinate);
}

bool City::tile_has_building(int x_coordinate, int y_coordinate) {
  return city_map->tile_has_building(x_coordinate, y_coordinate);
}

bool City::tile_has_repairable_building(int x_coordinate, int y_coordinate) {
  return city_map->tile_has_repairable_building(x_coordinate, y_coordinate);
}

Player* City::get_building_owner(int x_coordinate, int y_coordinate) {
  return city_map->get_building_owner(x_coordinate, y_coordinate);
}

bool City::attack_building(int x_coordinate, int y_coordinate) {
  return city_map->attack_building(x_coordinate, y_coordinate);
}

bool City::repair_building(int x_coordinate, int y_coordinate) {
  return city_map->repair_building(x_coordinate, y_coordinate);
}

bool City::spawn_player(Player* player, int x_coordinate, int y_coordinate) {
  return city_map->spawn_player(player, x_coordinate, y_coordinate);
}

void City::move_player(Player* player, int energy_cost, stack<Vertex> vertex_traversed) {
    city_map->move_player(player, energy_cost, vertex_traversed);
}

bool City::traversable_tile(int x_coordinate, int y_coordinate) {
  return city_map->traversable_tile(x_coordinate, y_coordinate);
}

string City::elements_data_to_string() {
  string save_data;

  save_data = city_map->materials_data_to_string();
  save_data = city_map->save_player_position(save_data, 1);
  save_data = buildings->building_data_to_string(save_data, 1);
  save_data = city_map->save_player_position(save_data, 2);
  save_data = buildings->building_data_to_string(save_data, 2);

  return save_data;
}

//------------------------------------------------------------------------------

City::~City() {
  delete buildings;
  delete record;
  delete city_map;
  delete passable_tiles;
  delete building_types;
}
