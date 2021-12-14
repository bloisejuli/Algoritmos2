#ifndef SAWMILL_H
#define SAWMILL_H

#include "building.h"

class Sawmill: public Building {

public:

  //PRE:-
  //POS: Creates a Sawmill object.
  Sawmill(string, string, int, int);

  //PRE:-
  //POS: Returns WOOD_PROVIDED_BY_SAWMILL.
  int produce_material();

};

#endif // SAWMILL_H
