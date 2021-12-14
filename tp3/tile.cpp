#include "tile.h"

Tile::Tile() {

    player_on_it = 0;
    player_passing_by = 0;

}

void Tile::place_player(Player* player) {
    player_on_it = player;
}

void Tile::place_player_passing_by(Player* player_passing_by) {
    this->player_passing_by = player_passing_by;
}

void Tile::remove_player() {
    player_on_it = 0;
}

void Tile::remove_player_passing_by() {
    player_passing_by = 0;
}

Player* Tile::get_player() {
    return player_on_it;
}

Player* Tile::get_player_passing_by() {
    return player_passing_by;
}

bool Tile::two_players_on_it() {
    return player_passing_by != 0;
}

bool Tile::tile_empty() {
    return player_on_it == 0;
}

string Tile::get_value() {
    return "";
}

void Tile::show() {}