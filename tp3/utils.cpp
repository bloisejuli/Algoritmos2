#include "utils.h"

string capitalize_word(string word) {

  word[0] = char(toupper(int(word[0])));

  return word;

}

string lowercase_word(string word) {

  for (unsigned int i = 0; i < word.length(); i++) {

      word[i] = (char)tolower(word[i]);

  }

  return word;
}

bool is_numeric(string string_to_check) {

  for (int i = 0; i < int(string_to_check.length()); i++)

    if (!isdigit(string_to_check[i]))
       return false;

  return true;

}

bool ask_user_confirmation(string building_type) {

  string user_confirmation;

  std::cout << "Are you sure you want to add a building: " << BOLD_GREEN
              << building_type << DEFAULT_COLOR << " (y/n): ";

  std::cin >> user_confirmation;

  if (user_confirmation == "y" || user_confirmation == "yes")
    return true;

  return false;

}

string get_material_color(string material_type) {

    if (material_type == GOLD)
        return BOLD_YELLOW;

    else if (material_type == STONE)
        return BOLD_BLACK;

    else if (material_type == WOOD)
        return BOLD_GREEN;

    else if (material_type == STEEL)
        return BOLD_CYAN;

    else if (material_type == BOMB)
        return BOLD_RED;

    else if (material_type == ENERGY)
        return BOLD_LIGHT_BLUE;

    else
        return BOLD_BLUE;

}

string get_player_color(int player_id) {
  string player_color;

  if (player_id == 1)
    player_color = PLAYER_1_COLOR;

  else
    player_color = PLAYER_2_COLOR;

  return player_color;
}

int get_weight(char tile_type, int player_id) {
  int tile_weight;
  if(tile_type == TERRAIN)
    tile_weight = 25;
  else if(tile_type == LAKE) {
    if(player_id == 1)
      tile_weight = 2;
    else
      tile_weight = 5;
  }
  else if(tile_type == BITUMEN)
    tile_weight = 0;
  else if(tile_type == DOCK) {
    if(player_id == 1)
      tile_weight = 5;
    else
      tile_weight = 2;
  }
  else if(tile_type == ROAD)
    tile_weight = 4;

  return tile_weight;
}
