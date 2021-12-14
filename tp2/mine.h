#ifndef MINE_H
#define MINE_H

#include "building.h"

class Mine : public Building {

public:

    //PRE:-
    //POS: Creates Mine object.
    Mine(string, string, int, int);

    //PRE:-
    //POS: Returns STONE_PROVIDED_BY_MINE.
    int produce_material();
};

#endif // MINE_H
