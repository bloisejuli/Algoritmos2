#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>
#include <iostream>

using namespace std;

const string DEFAULT_COLOR = "\e[0m";
const string BOLD_RED = "\e[1;31m";
const string BOLD_BLUE = "\e[1;34m";
const string BOLD_BLACK = "\e[1;30m";
const string BOLD_GREEN = "\e[1;32m";
const string BOLD_YELLOW = "\e[1;33m";
const string BOLD_CYAN = "\e[1;36m";
const string BOLD_VIOLET = "\e[1;35m";

const string DIVISORY_LINE = "\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550";

const int WIDTH = 10;

const int BUILD = 1;
const int BUILDINGS = 2;
const int RECORD = 3;
const int DEMOLISH = 4;
const int MAP = 5;
const int COORDINATE = 6;
const int INVENTORY = 7;
const int COLLECT_RESOURCES = 8;
const int MATERIAL_RAIN = 9;
const int HOW_DO_YOU_TURN_THIS_ON = 10;
const int EXIT = 11;

const string MATERIAL_FILE_ROUTE = "materiales.txt";
const string BUILDING_FILE_ROUTE = "edificios.txt";
const string MAP_LOCATIONS_ROUTE = "ubicaciones.txt";
const string MAP_FILE_ROUTE = "mapa.txt";

const string STONE = "piedra";
const string WOOD = "madera";
const string STEEL = "metal";

const int STONE_ID = 1;
const int WOOD_ID = 2;
const int STEEL_ID = 3;

const char LAKE = 'L';
const char TERRAIN = 'T';
const char ROAD = 'C';

const string BUILDABLE = "buildable";
const string INACCESIBLE = "inaccesible";
const string PASSABLE = "passable";

const string EMPTY = "empty";
const string OCCUPIED = "occupied";

const string MINE = "mina";
const string SAWMILL = "aserradero";
const string FACTORY = "fabrica";
const string SCHOOL = "escuela";
const string OBELISK = "obelisco";
const string POWER_PLANT = "planta";

const int STONE_PROVIDED_BY_MINE = 15;
const int WOOD_PROVIDED_BY_SAWMILL = 25;
const int STEEL_PROVIDED_BY_FACTORY = 40;

const string LAKE_ICON = "\U0001f7e6";
const string TERRAIN_ICON = "\U0001f7e9";
const string ROAD_ICON = "\u2B1C";

const string MINE_ICON = "\u26CF ";
const string SAWMILL_ICON = "\U0001fa9a ";
const string FACTORY_ICON = "\U0001f3ed";
const string SCHOOL_ICON = "\U0001f3eb";
const string OBELISK_ICON = "\u265F ";
const string POWER_PLANT_ICON = "\u26A1";

const string STONE_ICON = "\U0001faa8 ";
const string WOOD_ICON = "\U0001fab5 ";
const string STEEL_ICON = "\u2699 ";

#endif //CONSTANTS_H
