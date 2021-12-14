#ifndef MINE_H
#define MINE_H

#include "building.h"

class Mine : public Building {

private:
  bool damaged;

public:

    //PRE:-
    //POS: Creates Mine object.
    Mine(string, string, string, int, int, Player*);

    //PRE:-
    //POS: Returns STONE_PROVIDED_BY_MINE.
    void produce_material();

    void damage_building();

    void repair_building();

    bool get_building_state();
};

#endif // MINE_H
