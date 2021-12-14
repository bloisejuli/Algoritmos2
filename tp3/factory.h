#ifndef FACTORY_H
#define FACTORY_H

#include "building.h"

class Factory : public Building {

private:
  bool damaged;

public:

  //PRE:-
  //POS: Creates Factory object.
  Factory(string, string, string, int, int, Player*);

  //PRE:-
  //POS: Returns STEEL_PROVIDED_BY_FACTORY.
  void produce_material();

  //PRE: -
  //POS: Assings 'damged' = true.
  void damage_building();

  //PRE: -
  //POS: Assings 'damged' = false.
  void repair_building();

  //PRE: -
  //POS: Returns 'damaged'
  bool get_building_state();

};

#endif // FACTORY_H
