#ifndef TILE_H
#define TILE_H
#include <fstream>
#include <iostream>
#include "constants.h"
#include "player.h"
using namespace std;

class Tile {

protected:
    Player* player_on_it;
    Player* player_passing_by;

public:

    //PRE:-
    //POS: Creates a Tile object.
    Tile();

    void place_player(Player* player);

    void place_player_passing_by(Player* player_passing_by);

    void remove_player();

    void remove_player_passing_by();

    Player* get_player();

    Player* get_player_passing_by();

    bool two_players_on_it();

    //PRE:-
    //POS:-
    virtual ~Tile() {};

    //PRE:-
    //POS: -
    virtual void show();

    //PRE:-
    //POS: Returns .
    virtual bool tile_empty();

    //PRE:-
    //POS: Returns "".
    virtual string get_value();

    //PRE:-
    //POS:-
    virtual string get_tile_class() = 0;

};

#endif //TILE_H