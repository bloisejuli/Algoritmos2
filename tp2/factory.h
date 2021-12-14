#ifndef FACTORY_H
#define FACTORY_H

#include "building.h"

class Factory : public Building {

public:
  
  //PRE:-
  //POS: Creates Factory object.
  Factory(string, string, int, int);

  //PRE:-
  //POS: Returns STEEL_PROVIDED_BY_FACTORY.
  int produce_material();

};

#endif // FACTORY_H
