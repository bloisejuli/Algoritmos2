#ifndef OBELISK_H
#define OBELISK_H

#include "building.h"

class Obelisk : public Building {

public:

  //PRE:-
  //POS: Creates a Obelisk object.
  Obelisk(string, string, string, int, int, Player*);

};

#endif // OBELISK_H
