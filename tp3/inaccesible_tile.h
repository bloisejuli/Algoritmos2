#ifndef INACCESIBLE_TILE_H
#define INACCESIBLE_TILE_H

#include "tile.h"

class InaccesibleTile : public Tile {

public:


    //PRE:-
    //POS: Creates a InaccesibleTile object.
    InaccesibleTile();

    //PRE:-
    //POS: Informs on screen that the tile is inaccesible.
    void show();

    //PRE:-
    //POS: Returns 'INACCESIBLE'.
    string get_tile_class();

};

#endif // INACCESIBLE_TILE_H
