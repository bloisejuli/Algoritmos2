#include "material_handler.h"

MaterialHandler::MaterialHandler() {

  materials = new List<Material>;

}

void MaterialHandler::add_material(string material, int quantity){

  Material* new_material = new Material(material, quantity);
  materials->add_node(new_material);

}

void MaterialHandler::show_materials() {

  materials->reset_current_node();

  while (materials->get_current_value() != 0) {

    string capitalized_material = capitalize_word(materials->get_current_value()->get_material());

    if (materials->get_current_value()->get_material() == STONE) {

      std::cout << left << setw(WIDTH) << "Material: " << BOLD_BLACK <<
       setw(WIDTH) << capitalized_material << DEFAULT_COLOR
        << setw(WIDTH) << " Quantity: "<< BOLD_BLUE << setw(WIDTH) <<
          materials->get_current_value()->get_quantity() << DEFAULT_COLOR << '\n';
    }

    else if (materials->get_current_value()->get_material() == WOOD) {

      std::cout << left << setw(WIDTH) << "Material: " << BOLD_GREEN <<
       setw(WIDTH) << capitalized_material << DEFAULT_COLOR
        << setw(WIDTH) << " Quantity: "<< BOLD_BLUE << setw(WIDTH) <<
          materials->get_current_value()->get_quantity() << DEFAULT_COLOR << '\n';

    }

    else if (materials->get_current_value()->get_material() == STEEL) {

      std::cout << left << setw(WIDTH) << "Material: " << BOLD_CYAN <<
       setw(WIDTH) << capitalized_material << DEFAULT_COLOR
        << setw(WIDTH) << " Quantity: "<< BOLD_BLUE << setw(WIDTH) <<
          materials->get_current_value()->get_quantity() << DEFAULT_COLOR << '\n';

    }

    else {

      std::cout << left << setw(WIDTH) << "Material: " << BOLD_YELLOW <<
       setw(WIDTH) << capitalized_material << DEFAULT_COLOR
        << setw(WIDTH) << " Quantity: "<< BOLD_BLUE << setw(WIDTH) <<
          materials->get_current_value()->get_quantity() << DEFAULT_COLOR << '\n';


    }

    materials->next_node();

  }

}

void MaterialHandler::set_material_amount(string material_to_modify, int new_quantity) {

  materials->reset_current_node();

  while (materials->get_current_value() != 0) {

    if (materials->get_current_value()->get_material() == material_to_modify)
      materials->get_current_value()->set_quantity(new_quantity);

    materials->next_node();

  }
}

int MaterialHandler::get_material_amount(string target_material){

  materials->reset_current_node();

  while (materials->get_current_value() != 0) {

    if (materials->get_current_value()->get_material() == target_material)
      return materials->get_current_value()->get_quantity();

    materials->next_node();

  }

  return -1;
}

string MaterialHandler::generate_random_material_type() {

  srand ((unsigned int)time(NULL));

  int random_material_id = rand() % 3 + 1;

  string material_type;

  if (random_material_id == STONE_ID) {

    material_type = STONE;

  }

  else if (random_material_id == WOOD_ID) {

    material_type = WOOD;

  }

  else if (random_material_id == STEEL_ID) {

    material_type = STEEL;

  }

  return material_type;

}

Material* MaterialHandler::generate_material(string material_type) {

  Material* new_material = new Material(material_type, 1);

  return new_material;

}

string MaterialHandler::materials_data_to_string() {

  string new_materials;

  materials->reset_current_node();

  while (materials->get_current_value() != 0) {

    new_materials = new_materials + materials->get_current_value()->get_material() + " ";
    new_materials = new_materials + to_string(materials->get_current_value()->get_quantity()) + "\n";

    materials->next_node();
  }

  return new_materials;

}

MaterialHandler::~MaterialHandler() {

  delete materials;

}
