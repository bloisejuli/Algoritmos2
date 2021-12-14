#ifndef MAP_H
#define MAP_H
#include "tile.h"
#include "buildable_tile.h"
#include "building.h"
#include "passable_tile.h"
#include "inaccesible_tile.h"
#include "factory.h"
#include "mine.h"
#include "vertex.h"
#include <stack>

using namespace std;

class Map {

private:
    Tile*** map;

    int total_of_rows;
    int total_of_columns;

    Tile** current_tile;
    int current_row;
    int current_column;

public:

    //PRE: 'row' > 0 and 'columns' > 0.
    //POS: Assigns total_of_rows = 'rows', total_of_columns = 'columns', current_row = 0, current_column = 0.
    //     Creates a dynamic array of dimension (total_of_rows x total_of_columns) and initializes all the
    //     pointer of tiles to 0.
    Map(int rows, int columns);

    //PRE:-
    //POS: Destroy map and frees dynamic array's memory.
    ~Map();

    //PRE: 'tile_type' must be LAKE, TERRAIN or ROAD.
    //POS: Loads the map with the tiles types. Creates the according tile and current_row++, current_column++.
    void add_tile(char tile_type);

    //PRE: x_coordinate' and 'y_coordinate' must be valid map coordinates.
    //POS: Shows on screen the tile type, if its empty or the content.
    void consult(int x_coordinate, int y_coordinate, Player* player_1, Player* player_2);

    //PRE: x_coordinate' and 'y_coordinate' must be the coordinates of a buildable tile.
    //POS: Returns the building type.
    string get_building_type(int x_coordinate, int y_coordinate);

    //PRE: x_coordinate' and 'y_coordinate' must be valid map coordinates.
    //POS: Returns true if the consulted tile is a buildable tile.
    bool tile_buildable(int x_coordinate, int y_coordinate);

    //PRE: x_coordinate' and 'y_coordinate' must be valid map coordinates.
    //POS: Returns true if the tile is empty.
    bool tile_empty(int x_coordinate, int y_coordinate);

    //PRE: x_coordinate' and 'y_coordinate' must be the coordinates of a buildable tile.
    //POS: Creates a new Building and saves it at those coordinates.
    void add_building(Building* building, int x_coordinate, int y_coordinate);

    //PRE: x_coordinate' and 'y_coordinate' must be the coordinates of a buildable tile.
    //POS: Changes the tile in said coordinates point to null.
    void remove_building(int x_coordinate, int y_coordinate);

    bool tile_has_building(int x_coordinate, int y_coordinate);

    bool tile_has_repairable_building(int x_coordinate, int y_coordinate);

    //PRE: x_coordinate' and 'y_coordinate' must be the coordinates of a passable tile.
    //POS: Creates a new Material and saves it at those coordinates.
    void add_material(Material* material, int x_coordinate, int y_coordinate);

    bool spawn_player(Player* player, int x_coordinate, int y_coordinate);

    void move_player(Player* player, int energy_cost, stack<Vertex> vertex_traversed);

    // List<Material>* collect_thrown_materials(string coordinates_traversed, Player* player, List<Material>* materials_collected, stack<Vertice> vertex_traversed);

    List<Material>* collect_thrown_material(int x_coordinate, int y_coordinate, Player* player, List<Material>* materials_collected);

    void movement_animation(int player_id);

    void movement_announcer(string tiles_visited, int player_id, int energy_cost, List<Material>* materials_collected);

    bool traversable_tile(int x_coordinate, int y_coordinate);

    //PRE:-
    //POS: Returns 'total_of_rows'.
    int get_rows();

    //PRE:-
    //POS: Returns 'total_of_columns'.
    int get_columns();

    //PRE:-
    //POS: Shows on screen the map with icons representing buildings, materials and tiles types.
    void show_map(bool legend_visibility, int player_id);

    Player* get_building_owner(int x_coordinate, int y_coordinate);

    bool attack_building(int x_coordinate, int y_coordinate);

    bool repair_building(int x_coordinate, int y_coordinate);

    //PRE: -
    //POS: Returns all the  in the map in format of 'ubicaciones.txt'.
    string materials_data_to_string();

    string save_player_position(string saved_data, int player_id);


private:

    //PRE:-
    //POS: Initializes the dynamic matrix with 0.
    void initialize();

    //PRE:-
    //POS: Shows on screen map legend.
    void show_map_legend(string player_1_buildings_coordinates, string player_2_buildings_coordinates);

    void player_building_coordinates(BuildableTile* target_tile, string& player_buildings_coordinates);

    string get_material_icon(string material_type);

    string get_tile_icon(char tile_type);

    string get_background_color_tile_passable(char tile_type);

    void print_columns_grid();

    void print_rows_grid(int current_row, int current_column);

    void print_buildable_tile(int current_row, int current_column, bool tile_empty, int player_id,
                              string &player_1_buildings_coordinates, string &player_2_buildings_coordinates);

    void print_passable_tile(int current_row, int current_column, bool tile_empty, int player_id);

    void print_inaccesible_tile(int current_row, int current_column, bool tile_empty, int player_id);
};


#endif //MAP_H
