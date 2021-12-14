#ifndef GOLD_MINE_H
#define GOLD_MINE_H

#include "building.h"

class GoldMine : public Building {

public:

    //PRE:-
    //POS: Creates Mine object.
    GoldMine(string, string, string, int, int, Player*);

    //PRE:-
    //POS: Returns GOLD_PROVIDED_BY_GOLD_MINE.
    void produce_material();
};

#endif // GOLD_MINE_H
