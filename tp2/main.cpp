#include "menu.h"
#include "file_utils.h"

using namespace std;

int main() {

  system (CLR_SCREEN);

  City andypolis;

  bool not_end_program = true;

  not_end_program = load_buildings_attributes(&andypolis);

  if (not_end_program)
    not_end_program = load_materials(&andypolis);

  if (not_end_program)
    not_end_program = load_tiles(&andypolis);

  if (not_end_program)
    not_end_program = load_buildings(&andypolis);

  Menu menu;

  while (not_end_program) {

    menu.show_menu();

    not_end_program = menu.interpretate_user_input(&andypolis);

  }

  return 0;

}
