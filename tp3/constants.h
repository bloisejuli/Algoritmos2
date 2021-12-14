#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>
#include <iostream>

using namespace std;

//text colors
const string DEFAULT_COLOR = "\e[0m";
const string BOLD_RED = "\e[1;31m";
const string BOLD_BLUE = "\e[1;34m";
const string BOLD_BLACK = "\e[1;30m";
const string BOLD_GREEN = "\e[1;32m";
const string BOLD_YELLOW = "\e[1;33m";
const string BOLD_CYAN = "\e[1;36m";
const string BOLD_VIOLET = "\e[1;35m";
const string BOLD_GREY = "\033[1;38;5;245m";
const string BOLD_LIGHT_BLUE = "\033[1;38;5;45m";
const string BOLD_BROWN = "\033[38;5;94m";

//background colors
#define END_COLOR "\033[0m"
#define BGND_GRAY "\033[48;5;252m"
#define BGND_BROWN "\033[48;5;94m"
#define BGND_DARK_GRAY "\033[48;5;234m"
#define BGND_DARK_GREEN "\033[48;5;2m"
#define BGND_LIGHT_BLUE "\033[48;5;33m"
#define BGND_LIGHT_WHITE "\033[48;5;252m"

const string BLINK = "\033[6m";

//player_colors
const string PLAYER_1_COLOR = "\e[1;31m";
const string PLAYER_2_COLOR = "\e[1;34m";

const string PLAYER_1_ICON = "\U0001f53b";
const string PLAYER_2_ICON = "\U0001f539";

const int PLAYER_1 = 1;
const int PLAYER_2 = 2;

const string PLAYER_ONE = "Player 1";
const string PLAYER_TWO = "Player 2";

//Objectives
const string OBJECTIVE_1 = "Haber juntado 100.000 andycoins a lo largo de la partida.";
const string OBJECTIVE_2 = "Tener en el inventario 50000 piedras.";
const string OBJECTIVE_3 = "Haber usado 5 bombas.";
const string OBJECTIVE_4 = "Haber terminado un turno con 100 puntos de energia.";
const string OBJECTIVE_5 = "Haber construido el maximo posible de escuelas.";
const string OBJECTIVE_6 = "Haber construido una mina de cada tipo.";
const string OBJECTIVE_7 = "Haber terminado un turno con 0 de energia.";
const string OBJECTIVE_8 = "Haber construido un edificio de cada tipo.";
const string OBJECTIVE_9 = "Tener 10 bombas en el inventario.";
const string OBJECTIVE_10 = "Haber comprado 500 bombas en una partida.";

const int BUY_ANDYPOLIS = 0;
const int STONE_AGE = 1;
const int BOMBARDIER = 2;
const int ENERGETIC = 3;
const int LITERATE = 4;
const int MINER = 5;
const int TIRED = 6;
const int BUILDER = 7;
const int ARMED = 8;
const int EXTREMIST = 9;

const int AMOUNT_OF_PLAYER_OBJECTIVES = 3;
const int TOTAL_OBJECTIVES = 10;

const int TOTAL_GOLD_COLLECTED = 100000;
const int TOTAL_STONE_HOLD = 50000;
const int USED_BOMBS = 5;
const int BOMBS_ON_INVENTORY = 10;
const int BUYED_MANY_BOMBS = 500;


const string DIVISORY_LINE = "\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550";

const int WIDTH = 10;

const int MODIFY_BUILDING = 1;
const int BUILDING_LIST = 2;
const int SHOW_MAP = 3;
const int SPAWN_PLAYERS = 4;
const int START = 5;
const int SAVE_AND_EXIT = 6;

const int BUILD = 1;
const int BUILDINGS = 2;
const int RECORD = 3;
const int DEMOLISH = 4;
const int ATTACK = 5;
const int REPAIR = 6;
const int MAP = 7;
const int BUY_BOMBS = 8;
const int COORDINATE = 9;
const int INVENTORY = 10;
const int OBJECTIVES = 11;
const int COLLECT_RESOURCES = 12;
const int TRAVEL = 13;
const int HOW_DO_YOU_TURN_THIS_ON = 14;
const int END_TURN = 15;
const int EXIT = 16;

const string MATERIAL_FILE_ROUTE = "materiales.txt";
const string BUILDING_FILE_ROUTE = "edificios.txt";
const string MAP_LOCATIONS_ROUTE = "ubicaciones.txt";
const string MAP_FILE_ROUTE = "mapa.txt";

const string STONE = "piedra";
const string WOOD = "madera";
const string STEEL = "metal";
const string GOLD = "andycoins";
const string BOMB = "bombas";
const string ENERGY = "energia";

const char LAKE = 'L';
const char TERRAIN = 'T';
const char ROAD = 'C';
const char BITUMEN = 'B';
const char DOCK = 'M';

const string TERRAIN_TYPE = "terrain";
const string ROAD_TYPE = "road";
const string BITUMEN_TYPE = "bitumen";
const string DOCK_TYPE = "dock";
const string LAKE_TYPE = "lake";

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
const string POWER_PLANT = "planta electrica";
const string GOLD_MINE = "mina oro";

const int STONE_PROVIDED_BY_MINE = 15;
const int WOOD_PROVIDED_BY_SAWMILL = 25;
const int STEEL_PROVIDED_BY_FACTORY = 40;
const int GOLD_PROVIDED_BY_GOLD_MINE = 50;
const int GOLD_PROVIDED_BY_SCHOOL = 25;
const int ENERGY_PROVIDED_BY_POWER_PLANT = 15;

const int STONE_UNITS = 100;
const int WOOD_OR_STEEL_UNITS = 50;
const int GOLD_UNITS = 250;

const int INITIAL_ENERGY = 50;
const int ENERGY_RECOVERED_AT_END_OF_TURN = 20;
const int ENERGY_TO_BUILD = 15;
const int ENERGY_TO_DEMOLISH = 15;
const int ENERGY_TO_ATTACK = 30;
const int ENERGY_TO_REPAIR = 25;
const int ENERGY_TO_BUY_BOMBS = 5;
const int ENERGY_TO_COLLECT = 20;
const int MAX_ENERGY = 100;

const string LAKE_ICON = "\U0001f7e6";
const string TERRAIN_ICON = "\U0001f7e9";
const string ROAD_ICON = "\u2B1C";
const string DOCK_ICON = "\U0001f7eb";
const string BITUMEN_ICON = "\u2B1B";

#define FRAMED "\033[51m"
#define FRAMED_OFF "\033[54m"
#define BLINK "\033[6m"
#define BLINK_OFF "\033[25m"

const string MINE_ICON = "\u26CF ";
const string SAWMILL_ICON = "\U0001fa9a ";
const string FACTORY_ICON = "\U0001f3ed";
const string SCHOOL_ICON = "\U0001f3eb";
const string OBELISK_ICON = "\U0001f5fc";
const string POWER_PLANT_ICON = "\u26A1";
const string GOLD_MINE_ICON = "\U0001f9c8";

const string STONE_ICON = "\U0001faa8 ";
const string WOOD_ICON = "\U0001fab5 ";
const string STEEL_ICON = "\u2699 ";
const string GOLD_ICON = "\U0001f4b0";

const int NOT_FOUND_POSITION = -1;
const string NOT_FOUND_NAME = "";
const int INFINITY = 99999999;

#endif //CONSTANTS_H
