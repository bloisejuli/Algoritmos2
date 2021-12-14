#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <fstream>
#include "menu.h"
#include "city.h"
#include "file_manager.h"
#include "player.h"
#include "graph.h"

using namespace std;

class Game {

private:
  Menu* menu;
  City* andypolis;
  Player* player_1;
  Player* player_2;
  Graph* graph_player_1;
  Graph* graph_player_2;
  string objectives[10] = { OBJECTIVE_1, OBJECTIVE_2, OBJECTIVE_3, OBJECTIVE_4, OBJECTIVE_5, OBJECTIVE_6, OBJECTIVE_7, OBJECTIVE_8, OBJECTIVE_9, OBJECTIVE_10 };

public:
  //PRE: -
  //POS: Creates Game object.
  Game();


  //PRE: -
  //POS: Destroys Game object and calls the destructor of its attributes.
  ~Game();

  //PRE: -
  //POS: Starts the game.
  void start_game();

private:
  //PRE: -
  //POS: Returns true if is a new game, flase otherwise.
  bool load_files();

  //PRE: -
  //POS: Assings objectives to player
  void get_player_objectives(bool* available_objectives, Player* player);

  //PRE: -
  //POS: Updates the files with the new information from the program.
  void save_data();
  //PRE: -
  //POS: Select a Player. 
  Player* select_first_player();
 
  //PRE: 'player' must be a valid player.
  //POS: Returns player number
  int get_player_id(Player* player);

  //PRE: -
  //POS: Interpretates the user input.
  void interpretate_user_input(bool &end_program, bool &change_game_settings, bool &spawned_players);

  //PRE: -
  //POS: Modifies the cost of construction of the building.
  void modify_building_costs();

  //PRE: -
  //POS: Interpretates the player input.
  void interpretate_player_input(bool &end_program, bool &not_end_turn, Player* current_player);

  //PRE: -
  //POS: Returns true if building built, false otherwise.
  bool build(Player* current_player, bool &end_program, bool &not_end_turn);

  //PRE: -
  //POS: Makes the whole procces of demolishing a building.
  void demolish(Player* current_player);

  //PRE: -
  //POS: Makes the whole procces of attaking a building.
  void attack(Player* current_player);

  //PRE: -
  //POS: Makes the whole procces of repairing a building.
  void repair(Player* current_player);

  //PRE: -
  //POS: Makes the whole procces of buying to bombs.
  void buy_bomb(Player* current_player);

  //PRE: -
  //POS: Shows on screen all building information and the amount of material.
  void show_buildings_attributes(Player* current_player);

  //PRE: -
  //POS: Makes the whole procces of collecting resources.
  void collect_player_resources(Player* current_player);

  //PRE: -
  //POS: Makes the whole process of moving player.
  void move_player(Player* current_player);

  //PRE: -
  //POS: Spawns Players 
  void spawn_players(bool &spawned_players);

  //PRE:
  //POS:
  bool spawn_player(Player* new_player);

  //PRE: -
  //POS: Asks user x coordinate.
  int ask_user_x_coordinate();

  //PRE: -
  //POS: Asks user y coordinate.
  int ask_user_y_coordinate();

  //PRE: -
  //POS: Shows on screen a cobra car. 
  void how_do_you_turn_this_on();

  //PRE: -
  //POS: Produces resources for the building of the player and if 'initial_player' == 'current_player' makes material rain.
  void start_of_turn(Player* initial_player, Player* current_player, bool &initial_turn);

  //PRE: -
  //POS: Returns true if player is winner, false otherwise.
  bool end_turn(Player* &current_player);

  //PRE: -
  //POS: Shows on screen the no energy announcement.
  void no_energy_announcement();

  //PRE: -
  //POS: Returns false if the player has already collected his building resources.
  bool collected_resources_announcement(int stone_collected, int wood_collected, int steel_collected,
                                         int energy_collected, int gold_collected, Player* current_player);

  //PRE: -
  //POS: Shows on screen player objectives.
  void show_player_objectives(Player* current_player);

  //PRE: -
  //POS: Returns true if the objective has been accomplished.  
  bool check_objective(int objective, Player* current_player);

  //PRE: -
  //POS: Returns true if the player has accomplished two objectives.
  bool check_player_objectives(Player* current_player);

  //PRE: - 
  //POS: Returns true if the player has accomplished OBJECTIVE_1: "Haber juntado 100.000 andycoins a lo largo de la partida."
  bool check_objective_1(Player* current_player);

  //PRE: -
  //POS: Returns true if the player has accomplished OBJECTIVE_2: "Tener en el inventario 50000 piedras".
  bool check_objective_2(Player* current_player);

  //PRE: -
  //POS: Returns true if the player has accomplished OBJECTIVE_3: "Haber usado 5 bombas."
  bool check_objective_3(Player* current_player);

  //PRE: -
  //POS: Returns true if the player has accomplished OBJECTIVE_4: "Haber terminado un turno con 100 puntos de energia."
  bool check_objective_4(Player* current_player);

  //PRE: -
  //POS: Returns true if the player has accomplished OBJECTIVE_5: "Haber construido el maximo posible de escuelas."
  bool check_objective_5(Player* current_player);

  //PRE: -
  //POS: Returns true if the player has accomplished OBJECTIVE_6: "Haber construido una mina de cada tipo."
  bool check_objective_6(Player* current_player);
  
  //PRE: -
  //POS: Returns true if the player has accomplished OBJECTIVE_7: "Haber terminado un turno con 0 de energia."
  bool check_objective_7(Player* current_player);

  //PRE: -
  //POS: Returns true if the player has accomplished OBJECTIVE_8: "Haber construido un edificio de cada tipo."
  bool check_objective_8(Player* current_player);
  
  //PRE: -
  //POS: Returns true if the player has accomplished OBJECTIVE_9: "Tener 10 bombas en el inventario."
  bool check_objective_9(Player* current_player);

  //PRE: -
  //POS: Returns true if the player has accomplished OBJECTIVE_10: "Haber comprado 500 bombas en una partida."
  bool check_objective_10(Player* current_player);

};

#endif // GAME_H
