#include "utils.h"

string capitalize_word(string word) {

  word[0] = char(toupper(int(word[0])));

  return word;

}

string lowercase_word(string word) {

  for (unsigned int i = 0; i < word.length(); i++) {

      word[i] = (char)tolower(word[i]);

  }

  return word;
}

bool is_numeric(string string_to_check) {

  for (int i = 0; i < int(string_to_check.length()); i++)

    if (isdigit(string_to_check[i]) == false)
       return false;

  return true;

}

bool ask_user_confirmation(string building_type) {

  string user_confirmation;

  std::cout << "Are you sure you want to add a building: " << BOLD_GREEN
              << building_type << DEFAULT_COLOR << " (y/n): ";

  std::cin >> user_confirmation;

  if (user_confirmation == "y" || user_confirmation == "yes")
    return true;

  return false;

}