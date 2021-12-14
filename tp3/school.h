#ifndef SCHOOL_H
#define SCHOOL_H

#include "building.h"

class School : public Building {

public:

  //PRE:-
  //POS: Creates a School.
  School(string, string, string, int, int, Player*);

  //PRE:-
  //POS: Returns GOLD_PROVIDED_BY_SCHOOL.
  void produce_material();

};

#endif // SCHOOL_H
