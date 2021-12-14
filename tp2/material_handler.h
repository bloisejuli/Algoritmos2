#ifndef MATERIAL_HANDLER_H
#define MATERIAL_HANDLER_H
#include "list.h"
#include "material.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

class MaterialHandler{

private:
  List<Material>* materials;

public:

  //PRE:-
  //POS: Creates a MaterialHandler object, with an empty list.
  MaterialHandler();

  //PRE:-
  //POS: Destroys MaterialHandler object and calls the destructor of the list.
  ~MaterialHandler();

  //PRE: -
  //POS: Creates a new Material object with its corresponding attributes.
  void add_material(string material, int quantity);

  //PRE: -
  //POS: Shows on screen the materials and their quantity.
  void show_materials();

  //PRE: 'material' must be a valid material name.
  //POS: Replaces the quantity of target material to 'new_quantity'.
  void set_material_amount(string material_to_modify, int new_quantity);

  //PRE: 'target_material' must be a material valid.
  //POS: Returns the quantity of target material.
  int get_material_amount(string target_material);

  //PRE:-
  //POS: Returns a random material between STONE, WOOD and STEEL.
  string generate_random_material_type();

  //PRE: 'material_type' must be a valid type.
  //POS: Creates a new Material object and returns a pointer to it.
  Material* generate_material(string material_type);

  //PRE:-
  //POS: Returns all the materials in the format of 'materiales.txt'.
  string materials_data_to_string();

};

#endif //MATERIAL_HANDLER_H
