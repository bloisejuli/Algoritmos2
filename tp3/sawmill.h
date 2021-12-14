#ifndef SAWMILL_H
#define SAWMILL_H

#include "building.h"

class Sawmill: public Building {

public:

  //PRE:-
  //POS: Creates a Sawmill object.
  Sawmill(string, string, string, int, int, Player*);

  //PRE:-
  //POS: Returns WOOD_PROVIDED_BY_SAWMILL.
  void produce_material();

};

#endif // SAWMILL_H
