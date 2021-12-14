#include "map.h"
#include "constants.h"
#include "utils.h"

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

  else if (tile_type == ROAD)
    *current_tile = new PassableTile;


  if (current_column == total_of_columns - 1) {

    current_column = 0;
    current_row++;

  }

  else
    current_column++;

  current_tile = &map[current_row][current_column];

}

void Map::consult(int x_coordinate, int y_coordinate) {

  map[x_coordinate][y_coordinate]->show();

}

string Map::get_building_type(int x_coordinate, int y_coordinate) {

  return map[x_coordinate][y_coordinate]->get_value();
}

Tile* Map::get_tile(int x_coordinate, int y_coordinate) {

  return map[x_coordinate][y_coordinate];

}

bool Map::tile_buildable(int x_coordinate, int y_coordinate) {

  return map[x_coordinate][y_coordinate]->get_tile_class() == BUILDABLE;

}

bool Map::tile_passable(int x_coordinate, int y_coordinate) {

  return map[x_coordinate][y_coordinate]->get_tile_class() == PASSABLE;

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

void Map::add_material(Material* material, int x_coordinate, int y_coordinate) {

  PassableTile* target_tile = dynamic_cast<PassableTile*> (map[x_coordinate][y_coordinate]);

  target_tile->add_material(material);

}

int Map::get_rows() {

  return total_of_rows;

}

int Map::get_columns() {

  return total_of_columns;

}

void Map::show_map() {

  std::cout << BOLD_YELLOW << '\n';

  // rows gridlines

  std::cout << "    ";

  for (int k = 0; k < total_of_columns; k++) {

    if (k == total_of_columns - 1)
      std::cout << "  " << k << " " << "\n";

    else
      std::cout << "  " << k << " ";
  }

  std::cout << "    ";

  for (int l = 0; l < total_of_columns; l++) {

    if (l == total_of_columns - 1)
      std::cout << "════" << "\n";

    else
      std::cout << "════";
  }


  for (int i = 0; i < total_of_rows; i++) {
    for (int j = 0; j < total_of_columns; j++) {

      // colums gridlines
      if (j == 0)
        std::cout << BOLD_YELLOW << i << " ║ ";

      if (map[i][j]->get_tile_class() == BUILDABLE) {

        bool tile_empty = map[i][j]->tile_empty();

        if (tile_empty) {

          if (j == total_of_columns - 1)
            cout << BOLD_GREEN << "|" << TERRAIN_ICON << "|" << DEFAULT_COLOR << '\n';
          else
            cout << BOLD_GREEN << "|" << TERRAIN_ICON << "|" << DEFAULT_COLOR;

        }

        else {

          string building_icon;

          if (map[i][j]->get_value() == MINE)
            building_icon = MINE_ICON;

          else if (map[i][j]->get_value() == SAWMILL)
            building_icon = SAWMILL_ICON;

          else if (map[i][j]->get_value() == FACTORY)
            building_icon = FACTORY_ICON;

          else if (map[i][j]->get_value() == SCHOOL)
            building_icon = SCHOOL_ICON;

          else if (map[i][j]->get_value() == OBELISK)
            building_icon = OBELISK_ICON;

          else if (map[i][j]->get_value() == POWER_PLANT)
            building_icon = POWER_PLANT_ICON;

          if (j == total_of_columns - 1)
            cout << BOLD_GREEN << "|" << DEFAULT_COLOR << building_icon << BOLD_GREEN << "|" << DEFAULT_COLOR << '\n';

          else
            cout << BOLD_GREEN << "|" << DEFAULT_COLOR << building_icon << BOLD_GREEN << "|" << DEFAULT_COLOR;

        }

      }

      else if (map[i][j]->get_tile_class() == PASSABLE) {

        bool tile_empty = map[i][j]->tile_empty();

        if (tile_empty) {

          if (j == total_of_columns - 1)
            cout << DEFAULT_COLOR << "|" << ROAD_ICON << "|" << DEFAULT_COLOR << '\n';

          else
            cout << DEFAULT_COLOR << "|" << ROAD_ICON << "|" << DEFAULT_COLOR;

        }

        else {

          string material_icon;

          if (map[i][j]->get_value() == STONE)
            material_icon = STONE_ICON;

          else if (map[i][j]->get_value() == WOOD)
            material_icon = WOOD_ICON;

          else if (map[i][j]->get_value() == STEEL)
            material_icon = STEEL_ICON;

          if (j == total_of_columns - 1)
            cout << DEFAULT_COLOR << "|" << material_icon << "|"  << '\n';

          else
            cout << DEFAULT_COLOR << "|"  << material_icon << "|";

        }

      }

      else {

        if (j == total_of_columns - 1)
          cout << BOLD_BLUE << "|" << LAKE_ICON << "|" << DEFAULT_COLOR << '\n';

        else
          cout << BOLD_BLUE << "|" << LAKE_ICON << "|" << DEFAULT_COLOR;

      }
    }
  }

  show_map_legend();

}

string Map::materials_data_to_string(string saved_data) {

  for (int i = 0; i < total_of_rows; i++) {
    for (int j = 0; j < total_of_columns; j++) {

      if (map[i][j]->get_tile_class() == PASSABLE) {

        if (!map[i][j]->tile_empty()) {

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

//--------------------------Private Map Methods----------------------------

void Map::initialize() {

  for (int i = 0; i < total_of_rows; i++) {

    for (int j = 0; j < total_of_columns; j++) {

      map[i][j] = 0;

    }

  }

}

void Map::show_map_legend() {

  std::cout << '\n' << BOLD_BLUE  << "════";

  for (int i = 0; i < total_of_columns; i++) {

    if (i == total_of_columns - 1)
      std::cout << "════" << "\n";

    else
      std::cout << "════";

  }

  std::cout << right << setw(27) << "MAP LEGEND" << DEFAULT_COLOR << '\n' << '\n';

  std::cout << left << setw(5) << MINE_ICON << ":" << capitalize_word(MINE) << '\n';
  std::cout << left << setw(6) << SAWMILL_ICON << ":" << capitalize_word(SAWMILL) << '\n';
  std::cout << left << setw(5) << FACTORY_ICON << ":" << capitalize_word(FACTORY) << '\n';
  std::cout << left << setw(5) << SCHOOL_ICON << ":" << capitalize_word(SCHOOL) << '\n';
  std::cout << left << setw(5) << OBELISK_ICON << ":" << capitalize_word(OBELISK) << '\n';
  std::cout << left << setw(4) << POWER_PLANT_ICON << ":" << capitalize_word(POWER_PLANT) << '\n' << '\n';

  std::cout << left << setw(6) << STONE_ICON << ":" << capitalize_word(STONE) << '\n';
  std::cout << left << setw(6) << WOOD_ICON << ":" << capitalize_word(WOOD) << '\n';
  std::cout << left << setw(5) << STEEL_ICON << ":" << capitalize_word(STEEL) << '\n';
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
