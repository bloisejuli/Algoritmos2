#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstring>
#include "constants.h"
#include "Gotoxy.h"

#ifdef __linux__
#define CLR_SCREEN "clear"
#endif // __linux__

#ifdef __MINGW32__
#define CLR_SCREEN "CLS"
#endif // __MINGW32__

#ifdef __APPLE__
#define CLR_SCREEN "clear"
#endif // __APPLE__


using namespace std;

//PRE:
//POS: Returns the word capitalized.
string capitalize_word(string word);

//PRE: -
//POS: Returns the word in lowercase.
string lowercase_word(string word);

//PRE:-
//POS: Returns true if 'string_to_check' is numeric, otherwise it returns false.
bool is_numeric(string string_to_check);

//PRE:-
//POS: Asks the user if is sure to the action, if he enters 'y' or 'yes' it returns true, otherwise it returns false.
bool ask_user_confirmation(string building_type);

string get_material_color(string material_type);

string get_player_color(int player_id);

int get_weight(char tile_type, int player_id);

#endif //UTILS_H
