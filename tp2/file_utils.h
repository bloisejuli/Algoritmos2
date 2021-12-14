#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <iostream>
#include <fstream>
#include "city.h"

using namespace std;

//PRE: 'city' must be a valid City pointer.
//POS: Loads materials from MATERIAL_FILE_ROUTE and returns true if there wasn't any error, 
//     otherwise returns false.
bool load_materials(City* city);

//PRE: 'city' must be a valid City pointer.
//POS: Loads buildings from BUILDING_FILE_ROUTE and returns true if there wasn't any error, 
//     otherwise returns false. 
bool load_buildings_attributes(City* city);

//PRE: 'city' must be a valid City pointer.
//POS: Loads buildings and materials from MAP_LOCATIONS_ROUTE and returns true if there wasn't any error, 
//     otherwise returns false. 
bool load_buildings(City* city);

//PRE: 'city' must be a valid City pointer.
//POS: Loads tiles from MAP_FILE_ROUTE and returns true if there wasn't any error, 
//     otherwise returns false.
bool load_tiles(City* city);

#endif //FILE_UTILS_H
