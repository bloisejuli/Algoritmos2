#ifndef POWER_PLANT_H
#define POWER_PLANT_H

#include "building.h"

class PowerPlant: public Building {

public:

  //PRE:-
  //POS: Creates a PowerPlant object.
  PowerPlant(string, string, string, int, int, Player*);

  //PRE:-
  //POS: Returns .
  void produce_material();

};

#endif // POWER_PLANT_H
