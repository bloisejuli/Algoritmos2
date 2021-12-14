#include "menu.h"

using namespace std;

void Menu::show_new_game_menu() {

  std::cout << '\n';
  std::cout << "Welcome to " << BOLD_GREEN << "Andypolis New Game Menu"
                                  << DEFAULT_COLOR << ", options are: " << '\n';

  std::cout << BOLD_YELLOW << "[1]" << DEFAULT_COLOR << "  Modify building by name." << '\n';
  std::cout << BOLD_YELLOW << "[2]" << DEFAULT_COLOR << "  List all buildings." << '\n';
  std::cout << BOLD_YELLOW << "[3]" << DEFAULT_COLOR << "  Show Map." << '\n';
  std::cout << BOLD_YELLOW << "[4]" << DEFAULT_COLOR << "  Spawn players." << '\n';
  std::cout << BOLD_YELLOW << "[5]" << DEFAULT_COLOR << "  Start new game." << '\n';
  std::cout << BOLD_YELLOW << "[6]" << DEFAULT_COLOR << "  Save and exit." << '\n';
}

void Menu::show_game_menu(int player_number, int player_energy) {
  system (CLR_SCREEN);

  string player_color;

  if(player_number == PLAYER_1)
    player_color = PLAYER_1_COLOR;
  else
    player_color = PLAYER_2_COLOR;

  std::cout << '\n';
  std::cout << "Welcome " << player_color << "Player " << player_number <<
        DEFAULT_COLOR << " to " << BOLD_GREEN << "Andypolis Construction Menu" <<
         DEFAULT_COLOR << ", your options are: " << '\n';

  std::cout << left << BOLD_YELLOW << "[1]" << DEFAULT_COLOR << setw(4) << "  - " << BOLD_LIGHT_BLUE << setw(4) << "(15)" << DEFAULT_COLOR << " - Build building by name." << '\n';
  std::cout << left << BOLD_YELLOW << "[2]" << DEFAULT_COLOR << setw(4) << "  - " << BOLD_LIGHT_BLUE << setw(4) << "(0)" << DEFAULT_COLOR << " - List the buildings built." << '\n';
  std::cout << left << BOLD_YELLOW << "[3]" << DEFAULT_COLOR << setw(4) << "  - " << BOLD_LIGHT_BLUE << setw(4) << "(0)" << DEFAULT_COLOR << " - List all buildings." << '\n';
  std::cout << left << BOLD_YELLOW << "[4]" << DEFAULT_COLOR << setw(4) << "  - " << BOLD_LIGHT_BLUE << setw(4) << "(15)" << DEFAULT_COLOR << " - Demolish a building by coordinates." << '\n';
  std::cout << left << BOLD_YELLOW << "[5]" << DEFAULT_COLOR << setw(4) << "  - " << BOLD_LIGHT_BLUE << setw(4) << "(30)" << DEFAULT_COLOR << " - Attack a enemy building by coordinates." << '\n';
  std::cout << left << BOLD_YELLOW << "[6]" << DEFAULT_COLOR << setw(4) << "  - " << BOLD_LIGHT_BLUE << setw(4) << "(25)" << DEFAULT_COLOR << " - Repair a building by coordinates." << '\n';
  std::cout << left << BOLD_YELLOW << "[7]" << DEFAULT_COLOR << setw(4) << "  - " << BOLD_LIGHT_BLUE << setw(4) << "(0)" << DEFAULT_COLOR << " - Show map." << '\n';
  std::cout << left << BOLD_YELLOW << "[8]" << DEFAULT_COLOR << setw(4) << "  - " << BOLD_LIGHT_BLUE << setw(4) << "(5)" << DEFAULT_COLOR << " - Buy bombs." << '\n';
  std::cout << left << BOLD_YELLOW << "[9]" << DEFAULT_COLOR << setw(4) << "  - " << BOLD_LIGHT_BLUE << setw(4) << "(0)" << DEFAULT_COLOR << " - Consult coordinates." << '\n';
  std::cout << left << BOLD_YELLOW << "[10]" << DEFAULT_COLOR << setw(3) << " - " << BOLD_LIGHT_BLUE << setw(4) << "(0)" << DEFAULT_COLOR << " - Show inventory." << '\n';
  std::cout << left << BOLD_YELLOW << "[11]" << DEFAULT_COLOR << setw(3) << " - " << BOLD_LIGHT_BLUE << setw(4) << "(0)" << DEFAULT_COLOR << " - Show objectives." << '\n';
  std::cout << left << BOLD_YELLOW << "[12]" << DEFAULT_COLOR << setw(3) << " - " << BOLD_LIGHT_BLUE << setw(4) << "(20)" << DEFAULT_COLOR << " - Collect resources." << '\n';
  std::cout << left << BOLD_YELLOW << "[13]" << DEFAULT_COLOR << setw(3) << " - " << BOLD_LIGHT_BLUE << setw(4) << "(?)" << DEFAULT_COLOR << " - Move to a coordinate." << '\n';
  std::cout << left << BOLD_YELLOW << "[14]" << DEFAULT_COLOR << setw(3) << " - " << BOLD_LIGHT_BLUE << setw(4) << "(0)" << DEFAULT_COLOR << " - How do you turn this on." << '\n';
  std::cout << left << BOLD_YELLOW << "[15]" << DEFAULT_COLOR << setw(3) << " - " << BOLD_LIGHT_BLUE << setw(4) << "(0)" << DEFAULT_COLOR << " - End turn." << '\n';
  std::cout << left << BOLD_YELLOW << "[16]" << DEFAULT_COLOR << setw(3) << " - " << BOLD_LIGHT_BLUE << setw(4) << "(0)" << DEFAULT_COLOR << " - Save and exit." << '\n';

  std::cout << '\n' << "Remember your energy is: " << BOLD_YELLOW << player_energy << DEFAULT_COLOR << '\n';
}

void Menu::press_enter_to_continue(bool not_previous_input) {
  std::cout << '\n';

  if(!not_previous_input)
    std::cin.ignore();

  std::cout << "Press ENTER to go back to the menu: ";
  std::cin.get();
}

void Menu::press_enter_to_end_game() {
  std::cout << '\n';
  std::cin.ignore();
  std::cout << "Press ENTER to end the program: ";
  std::cin.get();
}
