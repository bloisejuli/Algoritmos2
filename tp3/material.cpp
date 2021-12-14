#include "material.h"


Material::Material(string material, int quantity) {
  this->material = material;
  this->quantity = quantity;
}

string Material::get_material() {
  return material;
}

void Material::set_quantity(int new_quantity) {
  quantity = new_quantity;
}

int Material::get_quantity() {
  return quantity;
}
