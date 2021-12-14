#include "game.h"

Game::Game(){
  menu = new Menu();
  andypolis = new City();
  bool available_objectives[TOTAL_OBJECTIVES];
  player_1 = new Player();
  player_2 = new Player();
  graph_player_1 = new Graph();
  graph_player_2 = new Graph();

  for(int i = 0; i < TOTAL_OBJECTIVES; i++) { available_objectives[i] = true; }

  get_player_objectives(available_objectives, player_1);
  get_player_objectives(available_objectives, player_2);
}

void Game::start_game() {
  bool new_game = load_files();
  graph_player_1->use_dijkstra();
  graph_player_2->use_dijkstra();
  bool change_game_settings = true;
  bool end_program = false;
  bool spawned_players = false;

  if(new_game) {
    while (change_game_settings) {
      menu->show_new_game_menu();
      interpretate_user_input(end_program, change_game_settings, spawned_players);
    }
  }

  Player* initial_player = select_first_player();
  Player* current_player = initial_player;
  int current_player_number = 0;
  bool not_end_turn = true;
  bool initial_turn = true;

  while (!end_program) {

    not_end_turn = true;
    start_of_turn(initial_player, current_player, initial_turn);
    current_player_number = get_player_id(current_player);

    while(not_end_turn) {
      menu->show_game_menu(current_player_number, current_player->get_resource_amount(ENERGY));
      interpretate_player_input(end_program, not_end_turn, current_player);
    }

    if(!end_program)
      end_program = end_turn(current_player);
  }

  save_data();
}

bool Game::load_files() {
  FileManager file_manager;

  bool new_game = false;

  file_manager.load_buildings_attributes(andypolis);
  file_manager.load_tiles(andypolis, graph_player_1, graph_player_2);

  new_game = file_manager.load_buildings(andypolis, player_1, player_2);

  if (new_game)
    file_manager.load_default_materials(player_1, player_2);
  else
    file_manager.load_materials(player_1, player_2);

  return new_game;
}

void Game::save_data() {

  fstream material_file;
  material_file.open(MATERIAL_FILE_ROUTE, ios::out);

  if (material_file.is_open()) {
      string new_materials;
      string quantity_player_1;
      string quantity_player_2;
      string resources = player_1->resources_type_data_to_string();
      string resources_player_1 = player_1->resources_amount_data_to_string();
      string resources_player_2 = player_2->resources_amount_data_to_string();

      stringstream resource(resources); //from API stringstream
      stringstream resource_1(resources_player_1);
      stringstream resource_2(resources_player_2);

      while (resource >> new_materials) {
          resource_1 >> quantity_player_1;
          resource_2 >> quantity_player_2;
          new_materials = new_materials + " " + quantity_player_1 + " " + " " + quantity_player_2 + '\n';
          material_file << new_materials;
      }

    material_file.close();
  }

  fstream building_file;
  building_file.open(MAP_LOCATIONS_ROUTE, ios::out);

  if (building_file.is_open()) {
    building_file << andypolis->elements_data_to_string();
    building_file.close();
  }

  fstream record_file;
  record_file.open(BUILDING_FILE_ROUTE, ios::out);

  if (record_file.is_open()) {
    record_file << andypolis->record_data_to_string();
    record_file.close();
  }
}

void Game::get_player_objectives(bool* available_objectives, Player* player) {

  int random_objective;
  bool is_not_available;
  int objectives[AMOUNT_OF_PLAYER_OBJECTIVES];

  for( int i = 0; i < AMOUNT_OF_PLAYER_OBJECTIVES; i++) {
    is_not_available = true;

    while (is_not_available) {
      random_objective = rand() % TOTAL_OBJECTIVES;

      if(available_objectives[random_objective])
        is_not_available = false;
    }

    available_objectives[random_objective] = false;
    objectives[i] = random_objective;
  }

  player->set_objectives(objectives);
}

Player* Game::select_first_player() {
  Player* current_player;
  int random_player_id = rand() % 2 + 1;

  std::cout << get_player_color(random_player_id) << "Player " << random_player_id << DEFAULT_COLOR <<
   " will be playing first "<< '\n';

  menu->press_enter_to_continue(true);

  if(random_player_id == PLAYER_1)
    current_player = player_1;

  else
    current_player = player_2;

  return current_player;
}

void Game::spawn_players(bool &spawned_players){
  string new_player_id;
  spawned_players = true;
  int next_player_id_to_spawn;
  bool valid_spawing;

  system (CLR_SCREEN);
  std::cout << "Available players are:" << '\n';

  std::cout << get_player_color(1) << "∘ " << PLAYER_ONE << '\n';
  std::cout << get_player_color(2) << "∘ " << PLAYER_TWO << '\n';

  std::cout << '\n' << DEFAULT_COLOR << "Please select your" << BOLD_VIOLET << " player number" << DEFAULT_COLOR << ": ";
  std::cin >> new_player_id;

  while (!is_numeric(new_player_id) || stoi(new_player_id) < 1 || stoi(new_player_id) > 2) {
    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "player " << BOLD_VIOLET <<
      "number" << DEFAULT_COLOR << " must be a number between " << BOLD_CYAN << " 1 and 2 " << DEFAULT_COLOR << "." << '\n';

    std::cout << '\n' << DEFAULT_COLOR << "Please select your" << BOLD_VIOLET << " player number" << DEFAULT_COLOR << ": ";
    std::cin >> new_player_id;
  }

  if (stoi(new_player_id) == PLAYER_1) {
    valid_spawing = spawn_player(player_1);

    while (!valid_spawing) {
      valid_spawing = spawn_player(player_1);
    }

    next_player_id_to_spawn = PLAYER_2;
  }
  else {
    valid_spawing = spawn_player(player_2);

    while (!valid_spawing) {
      valid_spawing = spawn_player(player_2);
    }

    next_player_id_to_spawn = PLAYER_1;
  }

  std::cout << get_player_color(next_player_id_to_spawn) << "Player " << next_player_id_to_spawn <<
              DEFAULT_COLOR << " enter your " << BOLD_VIOLET << "spawing coorinates" << DEFAULT_COLOR << "." << '\n';

  if (next_player_id_to_spawn == PLAYER_1) {
    valid_spawing = spawn_player(player_1);

    while (!valid_spawing) {
      valid_spawing = spawn_player(player_1);
    }
  }

  else {
    valid_spawing = spawn_player(player_2);

    while (!valid_spawing) {
      valid_spawing = spawn_player(player_2);
    }
  }
}

bool Game::spawn_player(Player* new_player){
  int x_coordinate, y_coordinate;

  x_coordinate = ask_user_x_coordinate();
  y_coordinate = ask_user_y_coordinate();
  return andypolis->spawn_player(new_player, x_coordinate, y_coordinate);
}

int Game::get_player_id(Player* player) {

  int player_number;

  if(player == player_1)
    player_number = PLAYER_1;
  else
    player_number = PLAYER_2;

  return player_number;
}

void Game::interpretate_user_input(bool &end_program, bool &change_game_settings, bool &spawned_players) {

  std::string user_option;
  std::cout << '\n' << "Please enter the option you want: ";
  std::cin >> user_option;

  while (!is_numeric(user_option) || stoi(user_option) < 1 || stoi(user_option) > 6) {
    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR
          << "Invalid option, please enter " << BOLD_CYAN <<
            "a number between 1 and 5: " << DEFAULT_COLOR;

    std::cin >> user_option;
  }

  int numeric_user_option = stoi(user_option);

  switch (numeric_user_option) {

    case MODIFY_BUILDING:

      modify_building_costs();

      menu->press_enter_to_continue(false);

      system (CLR_SCREEN);

      break;

    case BUILDING_LIST:

      show_buildings_attributes(0);

      menu->press_enter_to_continue(false);

      system (CLR_SCREEN);

      break;

    case SHOW_MAP:

      andypolis->show_map(true, 0);

      menu->press_enter_to_continue(false);

      system (CLR_SCREEN);

      break;

    case SPAWN_PLAYERS:

      spawn_players(spawned_players);

      menu->press_enter_to_continue(false);

      system (CLR_SCREEN);

      break;

    case START:

      if (spawned_players) {
        change_game_settings = false;
        system (CLR_SCREEN);
      }

      else {
        system (CLR_SCREEN);
        std::cout << BOLD_RED << "ERROR:" << DEFAULT_COLOR << " Both players must have chosen their " <<
          BOLD_RED << "spawing coordinates" << DEFAULT_COLOR << ", using option " << BOLD_YELLOW <<  "[4]" << DEFAULT_COLOR << "." << '\n';
      }

      break;

    case SAVE_AND_EXIT:

      std::cout << "Hope you enjoyed the program!" << '\n';

      end_program = true;
      change_game_settings = false;

      break;
  }
}

void Game::modify_building_costs() {

  system (CLR_SCREEN);

  string building_to_add;

  std::cout << "Enter the type of building you wish to build (type '" << BOLD_GREEN <<
             "exit" << DEFAULT_COLOR << "' to go back to menu): ";

   cin.ignore();
   getline(cin, building_to_add);

  while ((!andypolis->validate_building_type(lowercase_word(building_to_add)) && building_to_add != "exit") || lowercase_word(building_to_add) == "obelisco") {

    if(lowercase_word(building_to_add) == "obelisco")
      std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "You can't modify building costs values from the"
          << BOLD_GREEN << " 'Obelisco'" << DEFAULT_COLOR <<", enter a new building type to modify it's costs: ";

    else
      std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "Please Enter a valid type: ";

    std::cin >> building_to_add;

  }

  if (building_to_add != "exit") {

    std::cout << '\n';

    andypolis->modify_building_costs(lowercase_word(building_to_add));

  }

}

void Game::interpretate_player_input(bool &end_program, bool &not_end_turn, Player* current_player) {

  std::string user_option;

  std::cout << '\n' << "Please enter the option you want: ";

  std::cin >> user_option;

  while (!is_numeric(user_option) || stoi(user_option) < 1 || stoi(user_option) > 16) {

    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR
          << "Invalid option, please enter " << BOLD_CYAN <<
            "a number between 1 and 16: " << DEFAULT_COLOR;

    std::cin >> user_option;

  }

  int numeric_user_option = stoi(user_option);
  bool previous_input;

  switch (numeric_user_option) {

    case BUILD:

      previous_input = build(current_player, end_program, not_end_turn);

      if(!end_program)
        menu->press_enter_to_continue(previous_input);

      else
        menu->press_enter_to_end_game();

      system (CLR_SCREEN);

      break;

    case BUILDINGS:

      andypolis->show_buildings(current_player);

      menu->press_enter_to_continue(false);

      system (CLR_SCREEN);

      break;

    case RECORD:

      show_buildings_attributes(current_player);

      menu->press_enter_to_continue(false);

      system (CLR_SCREEN);

      break;

    case DEMOLISH:

      demolish(current_player);

      menu->press_enter_to_continue(false);

      system (CLR_SCREEN);

      break;

    case ATTACK:

      attack(current_player);

      menu->press_enter_to_continue(false);

      system (CLR_SCREEN);

      break;

    case REPAIR:

      repair(current_player);

      menu->press_enter_to_continue(false);

      system (CLR_SCREEN);

      break;

    case MAP:

      andypolis->show_map(true, current_player->get_id());

      menu->press_enter_to_continue(false);

      system (CLR_SCREEN);

      break;

    case BUY_BOMBS:

      buy_bomb(current_player);

      menu->press_enter_to_continue(false);

      system (CLR_SCREEN);

      break;

    case COORDINATE:
    {
      system (CLR_SCREEN);

      int x_coordinate = ask_user_x_coordinate();
      int y_coordinate = ask_user_y_coordinate();

      andypolis->consult_tile(x_coordinate, y_coordinate, player_1, player_2);

      menu->press_enter_to_continue(false);

      system (CLR_SCREEN);

      break;

    }

    case INVENTORY:

      system (CLR_SCREEN);

      current_player->show_resources();

      menu->press_enter_to_continue(false);

      system (CLR_SCREEN);

      break;

    case OBJECTIVES:

      system (CLR_SCREEN);

      show_player_objectives(current_player);

      menu->press_enter_to_continue(false);

      system (CLR_SCREEN);

      break;

    case COLLECT_RESOURCES:

      system (CLR_SCREEN);

      collect_player_resources(current_player);

      menu->press_enter_to_continue(false);

      system (CLR_SCREEN);

      break;

    case TRAVEL:

      move_player(current_player);

      menu->press_enter_to_continue(false);

      system (CLR_SCREEN);

      break;

    case HOW_DO_YOU_TURN_THIS_ON:

      how_do_you_turn_this_on();

      menu->press_enter_to_continue(false);

      system (CLR_SCREEN);

      break;

    case EXIT:

      std::cout << "Hope you enjoyed the program!" << '\n';

      not_end_turn = false;
      end_program = true;

      break;

    case END_TURN:

      not_end_turn = false;

      break;

  }

}

bool Game::build(Player* current_player, bool &end_program, bool &not_end_turn) {

  system (CLR_SCREEN);

  bool player_exited_method = true;

  if(current_player->get_resource_amount(ENERGY) >= ENERGY_TO_BUILD) {
    string building_to_add;

    std::cout << "Enter the type of building you wish to build (type '" << BOLD_GREEN <<
               "exit" << DEFAULT_COLOR << "' to go back to menu): ";

    cin.ignore();
    getline(cin, building_to_add);

    while (!andypolis->validate_building_type(lowercase_word(building_to_add)) && building_to_add != "exit") {
      std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "Please Enter a valid type: ";
      std::cin >> building_to_add;
    }

    if (building_to_add != "exit") {
      std::cout << '\n';

      player_exited_method  = false;
      int x_coordinate = ask_user_x_coordinate();
      int y_coordinate = ask_user_y_coordinate();
      int player_stone = current_player->get_resource_amount(STONE);
      int player_wood = current_player->get_resource_amount(WOOD);
      int player_steel = current_player->get_resource_amount(STEEL);
      bool building_built = andypolis->add_building(building_to_add, x_coordinate,
                                                     y_coordinate, false, player_stone,
                                                       player_wood, player_steel, current_player);

      if (building_built) {
        int building_stone_cost = andypolis->get_material_cost(lowercase_word(building_to_add), STONE);
        int building_wood_cost = andypolis->get_material_cost(lowercase_word(building_to_add), WOOD);
        int building_steel_cost = andypolis->get_material_cost(lowercase_word(building_to_add), STEEL);
        int player_id = current_player->get_id();
        int total_of_rows = andypolis->get_max_rows();
        int total_of_columns = andypolis->get_max_columns();

        current_player->deduct_building_cost(building_stone_cost, building_wood_cost, building_steel_cost);
        current_player->deduct_energy(ENERGY_TO_BUILD);

        if (player_id == PLAYER_1)
          graph_player_1->add_obstacle(x_coordinate, y_coordinate, total_of_rows, total_of_columns);
        else
          graph_player_2->add_obstacle(x_coordinate, y_coordinate, total_of_rows, total_of_columns);

        if (building_to_add == OBELISK) {
          end_program = true;
          not_end_turn = false;
          std::cout << '\n' << BOLD_GREEN << "CONGRATS " << get_player_color(current_player->get_id()) <<
            "Player " << current_player->get_id() << DEFAULT_COLOR << " you won the game by building the "
              << BOLD_BLACK << OBELISK << DEFAULT_COLOR << "." << '\n';
        }
      }
    }
  }

  else
    no_energy_announcement();

  return player_exited_method;
}

void Game::demolish(Player* current_player) {

  system (CLR_SCREEN);

  if(current_player->get_resource_amount(ENERGY) >= 15) {

    int x_coordinate = ask_user_x_coordinate();
    int y_coordinate = ask_user_y_coordinate();

    if(andypolis->tile_buildable(x_coordinate, y_coordinate) && andypolis->tile_has_building(x_coordinate, y_coordinate)) {

      bool building_demolished;

      Player* building_owner = andypolis->get_building_owner(x_coordinate, y_coordinate);

      if (building_owner == current_player) {

        string target_building_type = andypolis->get_target_building_type(x_coordinate, y_coordinate);

        building_demolished = andypolis->demolish_building(x_coordinate, y_coordinate, current_player->get_id());

        if (building_demolished) {
          int building_stone_cost = andypolis->get_material_cost(target_building_type, STONE);
          int building_wood_cost = andypolis->get_material_cost(target_building_type, WOOD);
          int building_steel_cost = andypolis->get_material_cost(target_building_type, STEEL);
          int player_id = current_player->get_id();
          int total_of_rows = andypolis->get_max_rows();
          int total_of_columns = andypolis->get_max_columns();

          current_player->refund_building_cost(building_stone_cost, building_wood_cost, building_steel_cost);
          current_player->deduct_energy(15);

          if (player_id == PLAYER_1)
            graph_player_1->remove_obstacle(x_coordinate, y_coordinate, total_of_rows, total_of_columns, player_id);
          else
            graph_player_2->remove_obstacle(x_coordinate, y_coordinate, total_of_rows, total_of_columns, player_id);
        }
      }
      else {

        std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "The building in coordinates: (" <<
          BOLD_YELLOW << x_coordinate << ", " << y_coordinate << DEFAULT_COLOR << ") " <<
           " that you are trying to " << BOLD_RED << "demolish" << DEFAULT_COLOR <<
            " is " << BOLD_RED << "NOT yours" << DEFAULT_COLOR << '\n';
      }
    }
    else
    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "The tile in coordinates: (" <<
      BOLD_YELLOW << x_coordinate << ", " << y_coordinate << DEFAULT_COLOR << ") " <<
       BOLD_RED << "doesn't" << DEFAULT_COLOR << " have a building in it." << DEFAULT_COLOR << '\n';
  }
  else
    no_energy_announcement();
}

void Game::attack(Player* current_player) {

  system (CLR_SCREEN);

  if(current_player->get_resource_amount(ENERGY) >= ENERGY_TO_ATTACK) {

    int x_coordinate = ask_user_x_coordinate();
    int y_coordinate = ask_user_y_coordinate();

    if(andypolis->tile_buildable(x_coordinate, y_coordinate) && andypolis->tile_has_building(x_coordinate, y_coordinate)) {

      bool destroyed_building;

      Player* building_owner = andypolis->get_building_owner(x_coordinate, y_coordinate);

      if (building_owner != current_player) {

        int current_player_id = get_player_id(current_player);
        string player_color = get_player_color(current_player_id);

        destroyed_building = andypolis->attack_building(x_coordinate, y_coordinate);
        string target_building_type = andypolis->get_target_building_type(x_coordinate, y_coordinate);

        if (destroyed_building) {
          int total_of_rows = andypolis->get_max_rows();
          int total_of_columns = andypolis->get_max_columns();

          andypolis->destroy_building(x_coordinate, y_coordinate, current_player->get_id()); // here
          current_player->use_bomb();

          if (current_player_id == PLAYER_1)
            graph_player_1->remove_obstacle(x_coordinate, y_coordinate, total_of_rows, total_of_columns, current_player_id);
          else
            graph_player_2->remove_obstacle(x_coordinate, y_coordinate, total_of_rows, total_of_columns, current_player_id);


          std::cout << player_color << "Player " << current_player_id << DEFAULT_COLOR <<
           " you successfully " << BOLD_RED << "destroyed" << DEFAULT_COLOR << " building: " <<
            BOLD_GREEN << capitalize_word(target_building_type) << DEFAULT_COLOR << " in coordinates: (" <<
              BOLD_YELLOW << x_coordinate << ", " << y_coordinate << DEFAULT_COLOR << ")." << '\n';
        }
        else
          std::cout << player_color << "Player " << current_player_id << DEFAULT_COLOR <<
           " you successfully " << BOLD_RED << "damaged" << DEFAULT_COLOR << " building: " <<
            BOLD_GREEN << capitalize_word(target_building_type) << DEFAULT_COLOR << " in coordinates: (" <<
              BOLD_YELLOW << x_coordinate << ", " << y_coordinate << DEFAULT_COLOR << ")." << '\n';

      current_player->deduct_energy(ENERGY_TO_ATTACK);
      }
      else {
        std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "The building in coordinates: (" <<
          BOLD_YELLOW << x_coordinate << ", " << y_coordinate << DEFAULT_COLOR << ") " <<
           "that you are trying to " << BOLD_RED << "attack" << DEFAULT_COLOR <<
            " is " << BOLD_GREEN << "yours." << DEFAULT_COLOR << '\n';
      }
    }
    else
    std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "The tile in coordinates: (" <<
      BOLD_YELLOW << x_coordinate << ", " << y_coordinate << DEFAULT_COLOR << ") " <<
       BOLD_RED << "doesn't" << DEFAULT_COLOR << " have a building in it." << DEFAULT_COLOR << '\n';
  }

  else
    no_energy_announcement();
}

void Game::repair(Player* current_player) {
  system (CLR_SCREEN);

  string player_color = get_player_color(current_player->get_id());
  bool buildings_to_repair = andypolis->player_has_buildings_to_repair(current_player);

  std::cout <<  player_color << "Player " << to_string(current_player->get_id()) << DEFAULT_COLOR << ":" << '\n';

  if(buildings_to_repair) {

    if(current_player->get_resource_amount(ENERGY) >= ENERGY_TO_REPAIR) {

      int x_coordinate = ask_user_x_coordinate();
      int y_coordinate = ask_user_y_coordinate();

      if(andypolis->tile_buildable(x_coordinate, y_coordinate) && andypolis->tile_has_repairable_building(x_coordinate, y_coordinate)) {
        Player* building_owner = andypolis->get_building_owner(x_coordinate, y_coordinate);

        if (building_owner == current_player) {
          int current_player_id = get_player_id(current_player);
          string player_color = get_player_color(current_player_id);
          bool repaired_building;

          repaired_building = andypolis->repair_building(x_coordinate, y_coordinate);

          string target_building_type = andypolis->get_target_building_type(x_coordinate, y_coordinate);

          if (repaired_building) {
            std::cout << player_color << "Player " << current_player_id << DEFAULT_COLOR <<
             " you successfully " << BOLD_GREEN << "repaired" << DEFAULT_COLOR << " building: " <<
              BOLD_GREEN << capitalize_word(target_building_type) << DEFAULT_COLOR << " in coordinates: (" <<
                BOLD_YELLOW << x_coordinate << ", " << y_coordinate << DEFAULT_COLOR << ")." << '\n';

            current_player->deduct_energy(30);
          }
          else
            std::cout << player_color << "Player " << current_player_id << DEFAULT_COLOR <<
             " there isn't any " << BOLD_RED << "damaged" << DEFAULT_COLOR << " building: " <<
              BOLD_GREEN << capitalize_word(target_building_type) << DEFAULT_COLOR << " in coordinates: (" <<
                BOLD_YELLOW << x_coordinate << ", " << y_coordinate << DEFAULT_COLOR << ")." << '\n';

        }
        else {

          std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "The building in coordinates: (" <<
            BOLD_YELLOW << x_coordinate << ", " << y_coordinate << DEFAULT_COLOR << ") " <<
             "that you are trying to " << BOLD_GREEN << "repair" << DEFAULT_COLOR <<
              " isn't " << BOLD_GREEN << "yours." << DEFAULT_COLOR << '\n';
        }
      }

      else if (!andypolis->tile_buildable(x_coordinate, y_coordinate))
        std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "The tile in coordinates: (" <<
          BOLD_YELLOW << x_coordinate << ", " << y_coordinate << DEFAULT_COLOR << ") " <<
           BOLD_RED << "doesn't" << DEFAULT_COLOR << " have a building in it." << DEFAULT_COLOR << '\n';

       else if (andypolis->tile_buildable(x_coordinate, y_coordinate) && !andypolis->tile_has_repairable_building(x_coordinate, y_coordinate))
         std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "The tile in coordinates: (" <<
           BOLD_YELLOW << x_coordinate << ", " << y_coordinate << DEFAULT_COLOR << ") " <<
            BOLD_RED << "doesn't" << DEFAULT_COLOR << " have a " << BOLD_GREEN <<
             "repairable" << DEFAULT_COLOR << " building in it." << DEFAULT_COLOR << '\n';
    }

    else
      no_energy_announcement();
  }
  else
    std::cout << "You " << BOLD_GREEN << "don't" << DEFAULT_COLOR << " have any buildings to repair. :)" << '\n';

}

void Game::buy_bomb(Player* current_player) {

  system (CLR_SCREEN);

  if(current_player->get_resource_amount(ENERGY) >= ENERGY_TO_BUY_BOMBS) {

    string bombs_to_buy;
    int player_gold = current_player->get_resource_amount(GOLD);

    std::cout << "Your current amount of " << BOLD_YELLOW << GOLD << DEFAULT_COLOR <<
                  " is : "  << BOLD_YELLOW  << player_gold << DEFAULT_COLOR << '\n';

    std::cout << "Enter the " << BOLD_BLUE << "amount" << DEFAULT_COLOR << " of '" <<
               BOLD_RED << BOMB << DEFAULT_COLOR << "' you want to buy: ";

    std::cin >> bombs_to_buy;

    while (!is_numeric(bombs_to_buy) || stoi(bombs_to_buy) < 0 || stoi(bombs_to_buy) * 100 > player_gold) {

      if(!is_numeric(bombs_to_buy) || stoi(bombs_to_buy) < 0) {
        std::cout << '\n' << BOLD_RED << "ERROR: " << DEFAULT_COLOR << BOLD_BLUE << "Amount" <<
                   DEFAULT_COLOR <<" of '" << BOLD_RED << BOMB << DEFAULT_COLOR <<
                    "' must be a " << BOLD_LIGHT_BLUE<< "positive number" << DEFAULT_COLOR << ": ";
      }



      else {
        std::cout << '\n' << BOLD_RED << "ERROR: " << DEFAULT_COLOR << "You don't have enough " <<
                   BOLD_YELLOW << GOLD << DEFAULT_COLOR << " to buy that " << BOLD_BLUE
                    << "amount" << DEFAULT_COLOR << " of " << BOLD_RED << BOMB << DEFAULT_COLOR << '\n' << '\n';

        std::cout << "Enter the " << BOLD_BLUE << "amount" << DEFAULT_COLOR << " of '" <<
                   BOLD_RED << BOMB << DEFAULT_COLOR << "' you want to buy: ";
      }

      std::cin >> bombs_to_buy;

    }

    int bombs_cost = 100 * stoi(bombs_to_buy);

    current_player->buy_bombs(stoi(bombs_to_buy), bombs_cost);

    std::cout << "You bought: " << BOLD_BLUE << bombs_to_buy << " " << BOLD_RED << BOMB <<
    DEFAULT_COLOR << " have fun being a terrorist." << '\n';

    if(stoi(bombs_to_buy) >= 1)
      current_player->deduct_energy(ENERGY_TO_BUY_BOMBS);

  }

  else
    no_energy_announcement();

}

void Game::show_buildings_attributes(Player* current_player) {

  if(current_player == 0) {

    int use_stone = 0;
    int use_wood = 0;
    int use_steel = 0;
    int player_id = 0;

    andypolis->show_record(use_stone, use_wood, use_steel, player_id);

  }

  else {

    int player_stone = current_player->get_resource_amount(STONE);
    int player_wood = current_player->get_resource_amount(WOOD);
    int player_steel = current_player->get_resource_amount(STEEL);

    andypolis->show_record(player_stone, player_wood, player_steel, current_player->get_id());

    if(current_player != 0) {
      std::cout << "Remember your current materials are: " << '\n';
      current_player->show_resources();
    }

  }

}

void Game::collect_player_resources(Player* current_player) {

  system (CLR_SCREEN);

  if(current_player->get_resource_amount(ENERGY) >= ENERGY_TO_COLLECT) {

    int stone_collected = 0;
    int wood_collected = 0;
    int steel_collected = 0;
    int energy_collected = 0;
    int gold_collected = 0;

    andypolis->collect_resources(stone_collected, wood_collected, steel_collected,
                                  energy_collected, gold_collected, current_player);

    current_player->collect_resources(stone_collected, wood_collected, steel_collected,
                                       energy_collected, gold_collected);

   bool proper_recollection = collected_resources_announcement(stone_collected,
                                wood_collected, steel_collected, energy_collected,
                                  gold_collected, current_player);

    if(proper_recollection)
      current_player->deduct_energy(ENERGY_TO_COLLECT);

  }

  else
    no_energy_announcement();

}

void Game::move_player(Player* current_player) {
  system (CLR_SCREEN);

  int destination_x_coordinate = ask_user_x_coordinate();
  int destination_y_coordinate = ask_user_y_coordinate();
  bool valid_destination = true;
  int movement_cost;
  int player_id = current_player->get_id();
  int player_x_coordinate = current_player->get_x_coordinate();
  int player_y_coordinate = current_player->get_y_coordinate();
  int player_energy = current_player->get_resource_amount(ENERGY);
  string tiles_visited = "";
  string coordinates_traversed = "";
  Graph* corresponding_graph;

  if (!andypolis->traversable_tile(destination_x_coordinate, destination_y_coordinate)) {
    valid_destination = false;
  }

  if (valid_destination) {
    if (player_id == 1)
      corresponding_graph = graph_player_1;
    else if (player_id == 2)
      corresponding_graph = graph_player_2;

    stack<Vertex> vertex_traversed;

    vertex_traversed = corresponding_graph->minimum_path(player_x_coordinate, player_y_coordinate,
                                                       destination_x_coordinate, destination_y_coordinate, player_energy, movement_cost);
    if(player_energy >= movement_cost) {
        andypolis->move_player(current_player, movement_cost, vertex_traversed);
      current_player->deduct_energy(movement_cost);
    }
    else
      no_energy_announcement();
  }
}

int Game::ask_user_x_coordinate() {

  int max_rows = andypolis->get_max_rows();

  string x_coordinate;

  std::cout << "Enter the " << BOLD_YELLOW << "X" << DEFAULT_COLOR << " coordinate: ";
  std::cin >> x_coordinate;

  while (!is_numeric(x_coordinate) || stoi(x_coordinate) < 0 || stoi(x_coordinate) > max_rows - 1) {

  std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << BOLD_YELLOW << "X" << DEFAULT_COLOR <<
              " coordinate must be a number between" << BOLD_YELLOW << " 0 and " << max_rows - 1 << DEFAULT_COLOR << ": ";
  std::cin >> x_coordinate;

  }

  std::cout << '\n';

  return stoi(x_coordinate);

}

int Game::ask_user_y_coordinate() {

  int max_columns = andypolis->get_max_columns();

  string y_coordinate;

  std::cout << "Enter the " << BOLD_YELLOW << "Y" << DEFAULT_COLOR << " coordinate: ";
  std::cin >> y_coordinate;

  while (!is_numeric(y_coordinate) || stoi(y_coordinate) < 0 || stoi(y_coordinate) > max_columns - 1) {

  std::cout << BOLD_RED << "ERROR: " << DEFAULT_COLOR << BOLD_YELLOW << "Y" << DEFAULT_COLOR <<
              " coordinate must be a number between" << BOLD_YELLOW << " 0 and " << max_columns - 1 << DEFAULT_COLOR << ": ";
  std::cin >> y_coordinate;

  }

  std::cout << '\n';

  return stoi(y_coordinate);

}

void Game::how_do_you_turn_this_on() {

  system (CLR_SCREEN);
  string problematic_line_1_part_1 = R"(/`-')";
  string problematic_line_1_part_2 = R"(( )         ( ))";
  string problematic_line_1_part_3 = R"( /`-'\)";

  string problematic_line_2_part_1 = R"(|   |)";
  string problematic_line_2_part_2 = R"(---\_Cobra_/---)";
  string problematic_line_2_part_3 = R"(|   |)";

  std::cout << '\n';
  std::cout << "                  BRRRRRRRRRRRRRRRRRRRRRR" << '\n';
  std::cout << "        _________" << '\n';
  std::cout << "       |         |" << '\n';
  std::cout << BOLD_BLUE << " _o_  _";
  std::cout << DEFAULT_COLOR << "| " << BOLD_BLUE << "___=___" << DEFAULT_COLOR <<" |";
  std::cout << BOLD_BLUE << "_  _o_" << '\n';
  std::cout << problematic_line_1_part_1;
  std::cout << DEFAULT_COLOR << problematic_line_1_part_2;
  std::cout << BOLD_BLUE << problematic_line_1_part_3 << '\n';
  std::cout << BOLD_BLACK << "|   |-"<< BOLD_BLUE << "| ";
  std::cout << DEFAULT_COLOR << " ___*___ ";
  std::cout << BOLD_BLUE << " |" << BOLD_BLACK << "-|   |" << '\n';
  std::cout << "|   |" << BOLD_BLUE << " | ";
  std::cout << BOLD_BLACK << "(-+-+-+-)";
  std::cout << BOLD_BLUE << " |" << BOLD_BLACK <<" |   |" << '\n';
  std::cout << problematic_line_2_part_1;
  std::cout << DEFAULT_COLOR << problematic_line_2_part_2;
  std::cout << BOLD_BLACK << problematic_line_2_part_3 << '\n';
  std::cout << BOLD_BLACK << " ---                 ---" << DEFAULT_COLOR << '\n';

}

void Game::start_of_turn(Player* initial_player, Player* current_player, bool &initial_turn) {

  if (current_player == initial_player) {

    system (CLR_SCREEN);

    std::cout << "The following " << BOLD_BLUE << "resources" << DEFAULT_COLOR << " have " << BOLD_LIGHT_BLUE << "rained:" << DEFAULT_COLOR << '\n' << '\n';

    andypolis->material_rain();

    if(initial_turn) {

      menu->press_enter_to_continue(true);
      initial_turn = false;

    }

    else
      menu->press_enter_to_continue(false);

  }

  andypolis->produce_resources(current_player);
}

bool Game::end_turn(Player* &current_player) {
  current_player->recharge_energy();

  bool is_winner = check_player_objectives(current_player);

  if(current_player == player_1)
    current_player = player_2;
  else
    current_player = player_1;

  return is_winner;
}

void Game::no_energy_announcement() {

  std::cout << '\n' << BOLD_RED << "ERROR:" << DEFAULT_COLOR << " you have " << BOLD_LIGHT_BLUE <<
             "no energy" << DEFAULT_COLOR << " to do said action." << '\n';

}

bool Game::collected_resources_announcement(int stone_collected, int wood_collected, int steel_collected,
                                              int energy_collected, int gold_collected, Player* current_player) {
  bool proper_recollection = true;

  if(stone_collected == 0 && wood_collected == 0 && steel_collected == 0 && energy_collected == 0 && gold_collected == 0) {

    std::cout << BOLD_RED << "You already collected all the resources produced by your buildings." <<
                  DEFAULT_COLOR << '\n' << '\n';

    proper_recollection = false;

  }

  else {

    std::cout << BOLD_GREEN << "You collected the following resources:" << DEFAULT_COLOR << '\n' << '\n';

    if (stone_collected > 0) {
      std::cout << left << setw(WIDTH) << "Material: " << BOLD_BLACK << setw(WIDTH) << capitalize_word(STONE) <<
                   DEFAULT_COLOR << setw(WIDTH) << "Amount: " << BOLD_BLUE << setw(2) <<
                    stone_collected << DEFAULT_COLOR << ", from building type: " <<
                     BOLD_GREEN << setw(WIDTH) << capitalize_word(MINE) << DEFAULT_COLOR << '\n';
    }

    if (wood_collected > 0) {
      std::cout << left << setw(WIDTH) << "Material: " << BOLD_GREEN << setw(WIDTH) << capitalize_word(WOOD) <<
                   DEFAULT_COLOR << setw(WIDTH) << "Amount: " << BOLD_BLUE << setw(2) <<
                    wood_collected << DEFAULT_COLOR << ", from building type: " <<
                     BOLD_GREEN << setw(WIDTH) << capitalize_word(SAWMILL) << DEFAULT_COLOR << '\n';
    }

    if (steel_collected > 0) {
      std::cout << left << setw(WIDTH) << "Material: " << BOLD_CYAN << setw(WIDTH) << capitalize_word(STEEL) <<
                   DEFAULT_COLOR << setw(WIDTH) << "Amount: " << BOLD_BLUE << setw(2) <<
                    steel_collected << DEFAULT_COLOR << ", from building type: " <<
                     BOLD_GREEN << setw(WIDTH) << capitalize_word(FACTORY) << DEFAULT_COLOR << '\n';
    }

    if (energy_collected > 0) {
      std::cout << left << setw(WIDTH) << "Material: " << BOLD_LIGHT_BLUE << setw(WIDTH) << capitalize_word(ENERGY) <<
                   DEFAULT_COLOR << setw(WIDTH) << "Amount: " << BOLD_BLUE << setw(2) <<
                    energy_collected << DEFAULT_COLOR << ", from building type: " <<
                     BOLD_GREEN << setw(WIDTH) << capitalize_word(POWER_PLANT) << DEFAULT_COLOR << '\n';
    }

    if (gold_collected > 0) {

      bool player_has_school = andypolis->player_has_building_type(SCHOOL, current_player);
      bool player_has_gold_mine = andypolis->player_has_building_type(GOLD_MINE, current_player);

      if (player_has_school && !player_has_gold_mine)
        std::cout << left << setw(WIDTH) << "Material: " << BOLD_YELLOW << setw(WIDTH) << capitalize_word(GOLD) <<
                     DEFAULT_COLOR << setw(WIDTH) << "Amount: " << BOLD_BLUE << setw(2) <<
                      gold_collected << DEFAULT_COLOR << ", from building type: " <<
                       BOLD_GREEN << setw(WIDTH) << capitalize_word(SCHOOL) << DEFAULT_COLOR << '\n';

      else if (player_has_gold_mine && !player_has_school)
        std::cout << left << setw(WIDTH) << "Material: " << BOLD_YELLOW << setw(WIDTH) << capitalize_word(GOLD) <<
                   DEFAULT_COLOR << setw(WIDTH) << "Amount: " << BOLD_BLUE << setw(2) <<
                    gold_collected << DEFAULT_COLOR << ", from building type: " <<
                     BOLD_GREEN << setw(WIDTH) << capitalize_word(GOLD_MINE) << DEFAULT_COLOR << '\n';

      else if (player_has_gold_mine && player_has_school)
        std::cout << left << setw(WIDTH) << "Material: " << BOLD_YELLOW << setw(WIDTH) << capitalize_word(GOLD) <<
                   DEFAULT_COLOR << setw(WIDTH) << "Amount: " << BOLD_BLUE << setw(2) <<
                    gold_collected << DEFAULT_COLOR << ", from building type: " << BOLD_GREEN <<
                     setw(8) << capitalize_word(GOLD_MINE) << DEFAULT_COLOR << " and "
                      << BOLD_GREEN << capitalize_word(SCHOOL) << DEFAULT_COLOR << '\n';
    }

  }

  return proper_recollection;

}

void Game::show_player_objectives(Player* current_player) {
  int* player_objectives = current_player->get_objectives();
  std::cout << get_player_color(current_player->get_id()) << "Player "
    << current_player->get_id() << DEFAULT_COLOR << " you current objectives are:" << '\n';

  for (int i = 0; i < AMOUNT_OF_PLAYER_OBJECTIVES; i++) {
    std::cout << get_player_color(current_player->get_id()) << "∘ " << DEFAULT_COLOR;

    if (check_objective(player_objectives[i], current_player))
      std::cout << BOLD_GREEN << objectives[player_objectives[i]] << DEFAULT_COLOR <<'\n';

    else
      std::cout << objectives[player_objectives[i]] << '\n';
  }
}

bool Game::check_objective(int objective, Player* current_player) {
  bool current_objective;
   switch (objective) {
      case BUY_ANDYPOLIS:
        current_objective = check_objective_1(current_player);
        //std::cout << "Cantidad de andycoins: " << current_player->get_gold_collected() << '\n';
        break;
      case STONE_AGE:
        current_objective = check_objective_2(current_player);
        //std::cout << "Cantidad de piedra: " << current_player->get_resource_amount(STONE) << '\n';
        break;
      case BOMBARDIER:
        current_objective = check_objective_3(current_player);
        //std::cout << "Bombas usadas: " << current_player->get_bombs_used() << '\n';
        break;
      case ENERGETIC:
        current_objective = check_objective_4(current_player);
        //std::cout << "Turno terminado con energia igual a: " << current_player->get_resource_amount(ENERGY) << '\n';
        break;
      case LITERATE:
        current_objective = check_objective_5(current_player);
        //std::cout << "Escuelas construidas: " << andypolis->player_built_max_amount(current_player->get_id(), SCHOOL) << '\n';
        break;
      case MINER:
        current_objective = check_objective_6(current_player);
        //std::cout << "Hay una mina de cada tipo: " << '\n';
        break;
      case TIRED:
        current_objective = check_objective_7(current_player);
        //std::cout << "Cansado: " << current_player->get_resource_amount(ENERGY) << '\n';
        break;
      case BUILDER:
        current_objective = check_objective_8(current_player);
        //std::cout << "Cantidad de andycoins:" << current_player->get_gold_collected() << '\n';
        break;
      case ARMED:
        current_objective = check_objective_9(current_player);
        //std::cout << "Bombas en el invetario: " << current_player->get_resource_amount(BOMB) << '\n';
        break;
      case EXTREMIST:
        current_objective = check_objective_10(current_player);
        //std::cout << "Bombas compradas: " << current_player->get_bombs_bought() << '\n';
        break;
    }

    return current_objective;
}



bool Game::check_player_objectives(Player* current_player) {

  bool is_winner = false;
  int number_of_objectives_met = 0;
  int* player_objectives = current_player->get_objectives();

  for (int i = 0; i < AMOUNT_OF_PLAYER_OBJECTIVES; i++) {
    if (check_objective(player_objectives[i], current_player))
      number_of_objectives_met++;
  }

  if(number_of_objectives_met >= 2) {
    is_winner = true;
    std::cout << '\n' << BOLD_GREEN << "CONGRATS " << get_player_color(current_player->get_id()) <<
      "Player " << current_player->get_id() << DEFAULT_COLOR << " you won the game by completing your "
        << BOLD_LIGHT_BLUE <<"objectives!" << DEFAULT_COLOR << '\n';
  }

  else
    is_winner = false;

  return is_winner;
}

bool Game::check_objective_1(Player* current_player) {
  return current_player->get_gold_collected() >= TOTAL_GOLD_COLLECTED;
}

bool Game::check_objective_2(Player* current_player) {
  return current_player->get_resource_amount(STONE) >= TOTAL_STONE_HOLD;
}

bool Game::check_objective_3(Player* current_player) {
  return current_player->get_bombs_used() >= USED_BOMBS;
}

bool Game::check_objective_4(Player* current_player) {
  return current_player->get_resource_amount(ENERGY) == MAX_ENERGY;
}

bool Game::check_objective_5(Player* current_player) {
  return andypolis->player_built_max_amount_school(current_player->get_id());
}

bool Game::check_objective_6(Player* current_player) {
  if(andypolis->player_has_building_type(MINE, current_player) &&
     andypolis->player_has_building_type(GOLD_MINE, current_player))
     return true;
  else
    return false;
}

bool Game::check_objective_7(Player* current_player) {
  return current_player->get_resource_amount(ENERGY) == 0;
}

bool Game::check_objective_8(Player* current_player) {
  if(andypolis->player_has_building_type(MINE, current_player) &&
     andypolis->player_has_building_type(GOLD_MINE, current_player) &&
     andypolis->player_has_building_type(SAWMILL, current_player) &&
     andypolis->player_has_building_type(FACTORY, current_player) &&
     andypolis->player_has_building_type(SCHOOL, current_player) &&
     andypolis->player_has_building_type(POWER_PLANT, current_player))
    return true;
  else
    return false;
}

bool Game::check_objective_9(Player* current_player) {
  return current_player->get_resource_amount(BOMB) >= BOMBS_ON_INVENTORY;
}

bool Game::check_objective_10(Player* current_player) {
  return current_player->get_bombs_bought() >= BUYED_MANY_BOMBS;
}

Game::~Game() {
  delete menu;
  delete andypolis;
  delete player_1;
  delete player_2;
  delete graph_player_1;
  delete graph_player_2;
}
