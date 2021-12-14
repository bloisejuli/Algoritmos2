#ifndef MATERIALS_H
#define MATERIALS_H
#include <iostream>
#include <fstream>
using namespace std;

class Material{
private:

  string material;
  int quantity;

public:

  //PRE:-
  //POS: Creates a new Material object with its corresponding attributes.
  Material(string material, int quantity);

  //PRE:-
  //POS: Returns material.
  string get_material();

  //PRE: -
  //POS: Replaces quantity to 'new_quantity'.
  void set_quantity(int new_quantity);

  //PRE:-
  //POS: Returns quantity.
  int get_quantity();
};

#endif //MATERIALS_H
