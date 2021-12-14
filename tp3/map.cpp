#include "map.h"
#include "constants.h"
#include "utils.h"
#include <chrono>
#include <thread>

Map::Map(int rows, int columns) {

    total_of_rows = rows;
    total_of_columns = columns;

    map = new Tile**[rows];

    for (int i = 0; i < rows; i++)
        map[i] = new Tile*[columns];

    initialize();

    current_row = 0;
    current_column = 0;
    current_tile = &map[current_row][current_column];

}

void Map::add_tile(char tile_type) {

    if (tile_type == LAKE)
        *current_tile = new InaccesibleTile;

    else if (tile_type == TERRAIN)
        *current_tile = new BuildableTile;

    else
        *current_tile = new PassableTile(tile_type);


    if (current_column == total_of_columns - 1) {

        current_column = 0;
        current_row++;

    }

    else
        current_column++;

    current_tile = &map[current_row][current_column];

}

void Map::consult(int x_coordinate, int y_coordinate, Player* player_1, Player* player_2) {

    if(map[x_coordinate][y_coordinate]->get_tile_class() == BUILDABLE) {

        BuildableTile* target_tile = dynamic_cast<BuildableTile*> (map[x_coordinate][y_coordinate]);
        target_tile->show(player_1, player_2);

    }

    else
        map[x_coordinate][y_coordinate]->show();

}

string Map::get_building_type(int x_coordinate, int y_coordinate) {

    return map[x_coordinate][y_coordinate]->get_value();
}

bool Map::tile_buildable(int x_coordinate, int y_coordinate) {
    return map[x_coordinate][y_coordinate]->get_tile_class() == BUILDABLE;
}

bool Map::tile_empty(int x_coordinate, int y_coordinate) {
    return map[x_coordinate][y_coordinate]->tile_empty();
}

void Map::add_building(Building* building, int x_coordinate, int y_coordinate) {
    BuildableTile* target_tile = dynamic_cast<BuildableTile*> (map[x_coordinate][y_coordinate]);

    target_tile->add_building(building);
}

void Map::remove_building(int x_coordinate, int y_coordinate) {
    BuildableTile* target_tile = dynamic_cast<BuildableTile*> (map[x_coordinate][y_coordinate]);

    target_tile->remove_building();
}

bool Map::tile_has_building(int x_coordinate, int y_coordinate) {

    bool has_building = false;

    BuildableTile* target_tile = dynamic_cast<BuildableTile*> (map[x_coordinate][y_coordinate]);

    Building* building_on_tile = target_tile->get_building();

    if(building_on_tile != 0)
        has_building = true;

    return has_building;

}

bool Map::tile_has_repairable_building(int x_coordinate, int y_coordinate) {

    bool has_repairable_building = false;

    string building_type = map[x_coordinate][y_coordinate]->get_value();

    if (building_type == FACTORY || building_type == MINE)
        has_repairable_building = true;

    return has_repairable_building;

}

void Map::add_material(Material* material, int x_coordinate, int y_coordinate) {
    PassableTile* target_tile = dynamic_cast<PassableTile*> (map[x_coordinate][y_coordinate]);

    target_tile->add_material(material);
}

bool Map::spawn_player(Player* player, int x_coordinate, int y_coordinate) {
  bool correct_spawing;
  if(map[x_coordinate][y_coordinate]->tile_empty()) {
    map[x_coordinate][y_coordinate]->place_player(player);
    player->set_x_coordinate(x_coordinate);
    player->set_y_coordinate(y_coordinate);
    correct_spawing = true;
  }
  else {
    std::cout << BOLD_RED << "ERROR:" << DEFAULT_COLOR << " tile with coordinates: (" <<
              BOLD_YELLOW << x_coordinate << ", " << y_coordinate << DEFAULT_COLOR <<
              "), where you are trying to place a player is " << BOLD_RED << "occupied." << DEFAULT_COLOR << '\n';
    correct_spawing = false;
  }

  return correct_spawing;
}

void Map::move_player(Player* player, int energy_cost, stack<Vertex> vertex_traversed) {
    int x_coordinate;
    int y_coordinate;
    List<Material>* materials_collected = new List<Material>;
    string tiles_visited = "";

    while (!vertex_traversed.empty()) {
        if (!map[player->get_x_coordinate()][player->get_y_coordinate()]->two_players_on_it())
            map[player->get_x_coordinate()][player->get_y_coordinate()]->remove_player();
        else
            map[player->get_x_coordinate()][player->get_y_coordinate()]->remove_player_passing_by();

        x_coordinate = vertex_traversed.top().get_x_coordinate();
        y_coordinate = vertex_traversed.top().get_y_coordinate();

        materials_collected = collect_thrown_material(x_coordinate, y_coordinate, player, materials_collected);
        player->set_x_coordinate(x_coordinate);
        player->set_y_coordinate(y_coordinate);

        if (map[x_coordinate][y_coordinate]->tile_empty())
            map[x_coordinate][y_coordinate]->place_player(player);
        else
            map[x_coordinate][y_coordinate]->place_player_passing_by(player);

        movement_animation(player->get_id());
        vertex_traversed.pop();
        if (!vertex_traversed.empty())
            tiles_visited += "(" + to_string(x_coordinate) + ", " + to_string(y_coordinate) + ") -> ";
        else
            tiles_visited += "(" + to_string(x_coordinate) + ", " + to_string(y_coordinate) + ")";
    }

    movement_announcer(tiles_visited, player->get_id(), energy_cost, materials_collected);
}

List<Material>* Map::collect_thrown_material(int x_coordinate, int y_coordinate, Player* player, List<Material>* materials_collected) {
    if (map[x_coordinate][y_coordinate]->get_tile_class() == PASSABLE &&
        !map[x_coordinate][y_coordinate]->tile_empty()) {
        PassableTile* target_tile = dynamic_cast<PassableTile*> (map[x_coordinate][y_coordinate]);

        if (!target_tile->tile_empty()) {
            string material_name;
            int material_quantity;
            int player_material_quantity;
            bool material_already_on_list = false;

            material_name = target_tile->get_value();
            if (material_name != "") {
                material_quantity = target_tile->get_material_amount();
                player_material_quantity = player->get_resource_amount(material_name);

                materials_collected->reset_current_node();
                while(materials_collected->get_current_value() != 0) {
                    if(materials_collected->get_current_value()->get_material() == material_name) {
                        material_already_on_list = true;
                        int material_amount = materials_collected->get_current_value()->get_quantity();
                        materials_collected->get_current_value()->set_quantity(material_amount + material_quantity);
                    }
                    materials_collected->next_node();
                }

                if(!material_already_on_list) {
                    Material* material_collected = new Material(material_name, material_quantity);
                    materials_collected->add_node(material_collected);
                }

                target_tile->remove_material();
                player->set_resource_amount(material_name, player_material_quantity + material_quantity);
            }
        }
    }

    return materials_collected;
}

void Map::movement_animation(int player_id) {
    system (CLR_SCREEN);

    show_map(false, player_id);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Map::movement_announcer(string tiles_visited, int player_id, int energy_cost, List<Material>* materials_collected) {
    string player;
    string player_color = get_player_color(player_id);

    if (player_id == PLAYER_1)
        player = PLAYER_ONE;
    else
        player = PLAYER_TWO;

    std::cout << '\n' << player_color << player << DEFAULT_COLOR << ": you traversed the following tiles: " <<
              BOLD_YELLOW << tiles_visited << DEFAULT_COLOR << " and it cost you " <<
              BOLD_LIGHT_BLUE << energy_cost << DEFAULT_COLOR << " energy." << '\n';

    std::cout << '\n' << "And collected the following " << player_color << "resources" << DEFAULT_COLOR << ":" << '\n';

    string material_name;
    int material_amount;

    materials_collected->reset_current_node();
    while(materials_collected->get_current_value() != 0) {
        material_name = materials_collected->get_current_value()->get_material();
        material_amount = materials_collected->get_current_value()->get_quantity();

        std::cout << get_material_color(material_name) << capitalize_word(material_name) <<
                  DEFAULT_COLOR << ": " << BOLD_BLUE << material_amount << DEFAULT_COLOR << '\n';

        materials_collected->next_node();
    }

    delete materials_collected;
}

bool Map::traversable_tile(int x_coordinate, int y_coordinate) {
    bool traversable_tile = true;

    if(map[x_coordinate][y_coordinate]->get_tile_class() != PASSABLE) {
        if(!map[x_coordinate][y_coordinate]->tile_empty()) {
            traversable_tile = false;
            std::cout << BOLD_RED << "ERROR:" << DEFAULT_COLOR << " tile with coordinates: (" <<
                      BOLD_YELLOW << x_coordinate << ", " << y_coordinate << DEFAULT_COLOR <<
                      ") is "<< BOLD_RED << "not empty"<< DEFAULT_COLOR << " for you to move." << '\n';
        }
    }

    return traversable_tile;
}

int Map::get_rows() {
    return total_of_rows;
}

int Map::get_columns() {
    return total_of_columns;
}

void Map::show_map(bool legend_visibility, int player_id) {

    system (CLR_SCREEN);

    string player_1_buildings_coordinates = "";
    string player_2_buildings_coordinates = "";

    print_columns_grid();

    for (int i = 0; i < total_of_rows; i++) {
        for (int j = 0; j < total_of_columns; j++) {

            print_rows_grid(i, j);

            bool tile_empty = map[i][j]->tile_empty();
            string tile_type = map[i][j]->get_tile_class();

            if (tile_type == BUILDABLE) {
                print_buildable_tile(i, j, tile_empty, player_id, player_1_buildings_coordinates, player_2_buildings_coordinates);
            }
            else if (tile_type == PASSABLE){
                print_passable_tile(i, j, tile_empty, player_id);
            }
            else{
                print_inaccesible_tile(i, j, tile_empty, player_id);
            }
        }
    }

    if(legend_visibility)
        show_map_legend(player_1_buildings_coordinates, player_2_buildings_coordinates);
}

Player* Map::get_building_owner(int x_coordinate, int y_coordinate) {
    BuildableTile* target_tile = dynamic_cast<BuildableTile*> (map[x_coordinate][y_coordinate]);

    return target_tile->get_building_owner();
}

bool Map::attack_building(int x_coordinate, int y_coordinate) {
    bool destroyed_building = true;
    BuildableTile* target_tile = dynamic_cast<BuildableTile*> (map[x_coordinate][y_coordinate]);

    if(target_tile->get_value() == FACTORY) {
        Factory* target_building = dynamic_cast<Factory*> (target_tile->get_building());

        if(!target_building->get_building_state()) {

            target_building->damage_building();
            destroyed_building = false;
        }
    }
    else if(target_tile->get_value() == MINE) {
        Mine* target_building = dynamic_cast<Mine*> (target_tile->get_building());

        if(!target_building->get_building_state()) {

            target_building->damage_building();
            destroyed_building = false;
        }
    }

    return destroyed_building;
}

bool Map::repair_building(int x_coordinate, int y_coordinate) {
    bool repaired_building = false;
    BuildableTile* target_tile = dynamic_cast<BuildableTile*> (map[x_coordinate][y_coordinate]);

    if(target_tile->get_value() == FACTORY) {
        Factory* target_building = dynamic_cast<Factory*> (target_tile->get_building());

        if(target_building->get_building_state()) {
            target_building->repair_building();
            repaired_building = true;
        }
    }

    else if(target_tile->get_value() == MINE) {
        Mine* target_building = dynamic_cast<Mine*> (target_tile->get_building());

        if(target_building->get_building_state()) {
            target_building->repair_building();
            repaired_building = true;
        }
    }

    return repaired_building;
}

string Map::materials_data_to_string() {
    string saved_data;

    for (int i = 0; i < total_of_rows; i++) {
        for (int j = 0; j < total_of_columns; j++) {
            if (map[i][j]->get_tile_class() == PASSABLE) {
                if (!map[i][j]->tile_empty() && map[i][j]->get_player() == 0) {
                    saved_data = saved_data + map[i][j]->get_value();
                    saved_data = saved_data + " (";
                    saved_data = saved_data + to_string(i);
                    saved_data = saved_data + ", ";
                    saved_data = saved_data + to_string(j);
                    saved_data = saved_data + ")" + '\n';
                }
            }
        }
    }

    return saved_data;
}

string Map::save_player_position(string saved_data, int player_id) {
    for (int i = 0; i < total_of_rows; i++) {
        for (int j = 0; j < total_of_columns; j++) {
            if (!map[i][j]->tile_empty()) {
                if (map[i][j]->get_player() != 0 && map[i][j]->get_player()->get_id() == player_id) {
                    saved_data = saved_data + to_string(player_id);
                    saved_data = saved_data + " (";
                    saved_data = saved_data + to_string(i);
                    saved_data = saved_data + ", ";
                    saved_data = saved_data + to_string(j);
                    saved_data = saved_data + ")" + '\n';
                }
            }
        }
    }

    return saved_data;
}

//--------------------------Private Map Methods----------------------------

void Map::initialize() {
    for (int i = 0; i < total_of_rows; i++) {
        for (int j = 0; j < total_of_columns; j++) {
            map[i][j] = 0;
        }
    }
}

void Map::show_map_legend(string player_1_buildings_coordinates, string player_2_buildings_coordinates) {
    Gotoxy gotoxy;
    int x_displacement = 15 + total_of_columns * 2;

    std::cout << BOLD_BLUE;

    for (int i = 0; i < 21; i++) {
        if (i == 0)
            std::cout << gotoxy.pos(1, x_displacement + i) << "╔══" << "\n";
        else if (i == 20)
            std::cout << gotoxy.pos(1, x_displacement + i) << "══╗" << "\n";
        else
            std::cout << gotoxy.pos(1, x_displacement + i) << "══";
    }

    std::cout << gotoxy.pos(2, x_displacement) << setw(24) << "║ MAP LEGEND" << "║" << DEFAULT_COLOR << '\n' << '\n';

    std::cout << gotoxy.pos(3, x_displacement) << BOLD_BLUE << "║ " << right << setw(23) << "║" << DEFAULT_COLOR << '\n';

    std::cout << gotoxy.pos(4, x_displacement) << BOLD_BLUE << "║ " << DEFAULT_COLOR << MINE_ICON << ":" << left << setw(17) << capitalize_word(MINE) << BOLD_BLUE << "║" << '\n';
    std::cout << gotoxy.pos(5, x_displacement) << BOLD_BLUE << "║ " << DEFAULT_COLOR << SAWMILL_ICON << ":" << left << setw(17) << capitalize_word(SAWMILL) << BOLD_BLUE << "║" << '\n';
    std::cout << gotoxy.pos(6, x_displacement) << BOLD_BLUE << "║ " << DEFAULT_COLOR << FACTORY_ICON << ":" << left << setw(17) << capitalize_word(FACTORY) << BOLD_BLUE << "║" << '\n';
    std::cout << gotoxy.pos(7, x_displacement) << BOLD_BLUE << "║ " << DEFAULT_COLOR << SCHOOL_ICON << ":" << left << setw(17) << capitalize_word(SCHOOL) << BOLD_BLUE << "║" << '\n';
    std::cout << gotoxy.pos(8, x_displacement) << BOLD_BLUE << "║ " << DEFAULT_COLOR << OBELISK_ICON << ":" << left << setw(17) << capitalize_word(OBELISK) << BOLD_BLUE << "║" << '\n';
    std::cout << gotoxy.pos(9, x_displacement) << BOLD_BLUE << "║ " << DEFAULT_COLOR << POWER_PLANT_ICON << ":" << left << setw(17) << capitalize_word(POWER_PLANT) << BOLD_BLUE << "║" << '\n';
    std::cout << gotoxy.pos(10, x_displacement) << BOLD_BLUE << "║ " << DEFAULT_COLOR << GOLD_MINE_ICON << ":" << left << setw(17) << capitalize_word(GOLD_MINE) << BOLD_BLUE << "║" << '\n';

    std::cout << gotoxy.pos(11, x_displacement) << BOLD_BLUE << "║ " << right << setw(23) << "║" << DEFAULT_COLOR << '\n';

    std::cout << gotoxy.pos(12, x_displacement) << BOLD_BLUE << "║ " << DEFAULT_COLOR << STONE_ICON << ":" << left << setw(17) << capitalize_word(STONE) << BOLD_BLUE << "║" << '\n';
    std::cout << gotoxy.pos(13, x_displacement) << BOLD_BLUE << "║ " << DEFAULT_COLOR << WOOD_ICON << ":" << left << setw(17) << capitalize_word(WOOD) << BOLD_BLUE << "║" << '\n';
    std::cout << gotoxy.pos(14, x_displacement) << BOLD_BLUE << "║ " << DEFAULT_COLOR << STEEL_ICON << ":" << left << setw(17) << capitalize_word(STEEL) << BOLD_BLUE << "║" << '\n';
    std::cout << gotoxy.pos(15, x_displacement) << BOLD_BLUE << "║ " << DEFAULT_COLOR << GOLD_ICON << ":" << left << setw(17) << capitalize_word(GOLD) << BOLD_BLUE << "║" << '\n';

    std::cout << gotoxy.pos(16, x_displacement) << BOLD_BLUE << "║ " << right << setw(23) << "║" << DEFAULT_COLOR << '\n';

    std::cout << gotoxy.pos(17, x_displacement) << BOLD_BLUE << "║ " << DEFAULT_COLOR << TERRAIN_ICON << ":" << left << setw(17) << capitalize_word(TERRAIN_TYPE) << BOLD_BLUE << "║" << '\n';
    std::cout << gotoxy.pos(18, x_displacement) << BOLD_BLUE << "║ " << DEFAULT_COLOR << LAKE_ICON << ":" << left << setw(17) << capitalize_word(LAKE_TYPE) << BOLD_BLUE << "║" << '\n';
    std::cout << gotoxy.pos(19, x_displacement) << BOLD_BLUE << "║ " << DEFAULT_COLOR << ROAD_ICON << ":" << left << setw(17) << capitalize_word(ROAD_TYPE) << BOLD_BLUE << "║" << '\n';
    std::cout << gotoxy.pos(20, x_displacement) << BOLD_BLUE << "║ " << DEFAULT_COLOR << BITUMEN_ICON << ":" << left << setw(17) << capitalize_word(BITUMEN_TYPE) << BOLD_BLUE << "║" << '\n';
    std::cout << gotoxy.pos(21, x_displacement) << BOLD_BLUE << "║ " << DEFAULT_COLOR << DOCK_ICON << ":" << left << setw(17) << capitalize_word(DOCK_TYPE) << BOLD_BLUE << "║" << '\n' << '\n';

    std::cout << BOLD_BLUE;

    for (int i = 0; i < 21; i++) {
        if (i == 0)
            std::cout << gotoxy.pos(22, x_displacement + i) << "╚══" << "\n";
        else if (i == 20)
            std::cout << gotoxy.pos(22, x_displacement + i) << "══╝" << "\n";
        else
            std::cout << gotoxy.pos(22, x_displacement + i) << "══";
    }

    std::cout << DEFAULT_COLOR << '\n' << '\n';

    if(player_1_buildings_coordinates != "")
        std::cout << PLAYER_1_COLOR << "Player 1" << DEFAULT_COLOR << " buildings are in: " <<
                  BOLD_YELLOW << player_1_buildings_coordinates << DEFAULT_COLOR <<'\n';

    if(player_2_buildings_coordinates != "")
        std::cout << PLAYER_2_COLOR << "Player 2" << DEFAULT_COLOR << " buildings are in: " <<
                  BOLD_YELLOW << player_2_buildings_coordinates << DEFAULT_COLOR <<'\n';
}

void Map::player_building_coordinates(BuildableTile* target_tile, string &player_buildings_coordinates) {
    player_buildings_coordinates += "(";
    player_buildings_coordinates += to_string(target_tile->get_building()->get_x_coordinate());
    player_buildings_coordinates += ", ";
    player_buildings_coordinates += to_string(target_tile->get_building()->get_y_coordinate());
    player_buildings_coordinates += ") ";
}

string Map::get_material_icon(string material_type) {
    string icon;

    if (material_type == STONE)
        icon = STONE_ICON;
    else if (material_type == WOOD)
        icon = WOOD_ICON;
    else if (material_type == STEEL)
        icon = STEEL_ICON;
    else if (material_type == GOLD)
        icon = GOLD_ICON;

    return icon;
}

string Map::get_tile_icon(char tile_type) {
    string icon;

    if (tile_type == ROAD)
        icon = ROAD_ICON;
    else if (tile_type == DOCK)
        icon = DOCK_ICON;
    else if (tile_type == BITUMEN)
        icon = BITUMEN_ICON;

    return icon;
}

string Map::get_background_color_tile_passable(char tile_type) {
    string background_color;

    if (tile_type == ROAD)
        background_color = BGND_LIGHT_WHITE;
    else if(tile_type == DOCK)
        background_color = BGND_BROWN;
    else if(tile_type == BITUMEN)
        background_color = BGND_DARK_GRAY;

    return background_color;
}

void Map::print_passable_tile(int current_row, int current_column, bool tile_empty, int player_id) {
    bool is_current_player = false;

    PassableTile* target_tile = dynamic_cast<PassableTile*> (map[current_row][current_column]);
    char tile_type = target_tile->get_tile_type();

    if(tile_empty) {
        if (current_column == total_of_columns - 1)
            std::cout << get_background_color_tile_passable(tile_type) << BOLD_GREY <<
                      get_tile_icon(tile_type) << END_COLOR << '\n';
        else
            std::cout << get_background_color_tile_passable(tile_type) << BOLD_GREY <<
                      get_tile_icon(tile_type) << END_COLOR;
    }
    else {
        string icon;

        if(target_tile->get_player() == 0)
            icon = get_material_icon(target_tile->get_value());
        else {
            if (target_tile->two_players_on_it())
                icon = target_tile->get_player_passing_by()->get_icon();
            else
                icon = target_tile->get_player()->get_icon();

            if(target_tile->get_player()->get_id() == player_id)
                is_current_player = true;
        }

        if(is_current_player) {
            if (current_column == total_of_columns - 1)
                std::cout << get_background_color_tile_passable(tile_type) << BOLD_GREY << get_background_color_tile_passable(tile_type) <<
                          BLINK << icon << BOLD_GREY << END_COLOR << '\n';
            else
                std::cout << get_background_color_tile_passable(tile_type) << BOLD_GREY << get_background_color_tile_passable(tile_type) <<
                          BLINK << icon << BOLD_GREY << END_COLOR;
        }
        else {
            if (current_column == total_of_columns - 1)
                std::cout << get_background_color_tile_passable(tile_type) << BOLD_GREY << get_background_color_tile_passable(tile_type) <<
                          icon << BOLD_GREY << END_COLOR << '\n';
            else
                std::cout << get_background_color_tile_passable(tile_type) << BOLD_GREY << get_background_color_tile_passable(tile_type) <<
                          icon << BOLD_GREY << END_COLOR;
        }
    }
}

void Map::print_columns_grid() {

    std::cout << BOLD_YELLOW << '\n';

    std::cout << "     ";

    for (int k = 0; k < total_of_columns; k++) {
        if (k > 9)
            std::cout << k;
        else
            std::cout << k << " " ;
    }

    std::cout << '\n';
    std::cout << "     ";

    for (int l = 0; l < total_of_columns; l++) {
        if (l == total_of_columns - 1)
            std::cout << "══" << "\n";
        else
            std::cout << "══";
    }

    std::cout << DEFAULT_COLOR;
}

void Map::print_rows_grid(int current_row, int current_column) {
    if (current_column == 0) {

        if(current_row < 10)
            std::cout << BOLD_YELLOW << " " << current_row << " ║ ";
        else
            std::cout << BOLD_YELLOW <<  current_row << " ║ ";
    }
}

void Map::print_buildable_tile(int current_row, int current_column, bool tile_empty, int player_id,
                               string &player_1_buildings_coordinates, string &player_2_buildings_coordinates) {
    bool is_current_player = false;
    if (tile_empty) {
        if (current_column == total_of_columns - 1)
            cout << BOLD_GREEN << BGND_DARK_GREEN << TERRAIN_ICON << END_COLOR << BOLD_GREEN << END_COLOR << '\n';
        else
            cout << BOLD_GREEN << BGND_DARK_GREEN << TERRAIN_ICON << END_COLOR << BOLD_GREEN << END_COLOR;
    }
    else {
        string icon;
        BuildableTile* target_tile = dynamic_cast<BuildableTile*> (map[current_row][current_column]);

        if(target_tile->get_player() == 0) {
            icon = target_tile->get_building()->get_icon_building();

            if (target_tile->get_building_owner()->get_id() == PLAYER_1)
                player_building_coordinates(target_tile, player_1_buildings_coordinates);
            else if (target_tile->get_building_owner()->get_id() == PLAYER_2)
                player_building_coordinates(target_tile, player_2_buildings_coordinates);
        }
        else {
            if (target_tile->two_players_on_it())
                icon = target_tile->get_player_passing_by()->get_icon();
            else
                icon = target_tile->get_player()->get_icon();

            if(target_tile->get_player()->get_id() == player_id)
                is_current_player = true;
        }

        if(is_current_player) {
            if (current_column == total_of_columns - 1)
                cout << BOLD_GREEN << BGND_DARK_GREEN << BLINK << icon << END_COLOR << BOLD_GREEN << END_COLOR << '\n';
            else
                cout  << BOLD_GREEN  << BGND_DARK_GREEN << BLINK << icon << END_COLOR  << BOLD_GREEN << END_COLOR;
        }
        else {
            if (current_column == total_of_columns - 1)
                cout << BOLD_GREEN << BGND_DARK_GREEN << icon << END_COLOR << BOLD_GREEN << END_COLOR << '\n';
            else
                cout  << BOLD_GREEN  << BGND_DARK_GREEN << icon << END_COLOR  << BOLD_GREEN << END_COLOR;
        }
    }
}

void Map::print_inaccesible_tile(int current_row, int current_column, bool tile_empty, int player_id) {
    bool is_current_player = false;
    if(tile_empty) {
        if (current_column == total_of_columns - 1)
            cout << BGND_LIGHT_BLUE << BOLD_BLUE << LAKE_ICON << END_COLOR << '\n';
        else
            cout << BGND_LIGHT_BLUE << BOLD_BLUE << LAKE_ICON << END_COLOR;
    }
    else {
        string icon;
        if (map[current_row][current_column]->two_players_on_it())
            icon = map[current_row][current_column]->get_player_passing_by()->get_icon();
        else
            icon = map[current_row][current_column]->get_player()->get_icon();

        if(map[current_row][current_column]->get_player()->get_id() == player_id)
            is_current_player = true;

        if(is_current_player) {
            if (current_column == total_of_columns - 1)
                cout << BGND_LIGHT_BLUE << BOLD_BLUE << BLINK << icon << END_COLOR << '\n';
            else
                cout << BGND_LIGHT_BLUE << BOLD_BLUE << BLINK << icon << END_COLOR;
        }
        else {
            if (current_column == total_of_columns - 1)
                cout << BGND_LIGHT_BLUE << BOLD_BLUE << icon << END_COLOR << '\n';
            else
                cout << BGND_LIGHT_BLUE << BOLD_BLUE << icon << END_COLOR;
        }
    }
}

//------------------------------------------------------------------------------

Map::~Map() {

    for (int i = 0; i < total_of_rows; i++) {
        for (int j = 0; j < total_of_columns; j++) {

            delete map[i][j];
        }
        delete[] map[i];
    }
    delete[] map;
}
