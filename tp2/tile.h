#ifndef TILE_H
#define TILE_H
#include <fstream>
#include <iostream>
#include "constants.h"
using namespace std;

class Tile {

public:

    //PRE:-
    //POS: Creates a Tile object.
    Tile(){};

    //PRE:-
    //POS:-
    virtual ~Tile() {};

    //PRE:-
    //POS: -
    virtual void show() = 0;

    //PRE:-
    //POS: Returns true.
    virtual bool tile_empty();

    //PRE:-
    //POS: Returns "".
    virtual string get_value();

    //PRE:-
    //POS:-
    virtual string get_tile_class() = 0;

};

#endif //TILE_H
