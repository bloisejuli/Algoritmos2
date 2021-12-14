#include "graph.h"
#include <iostream>

Graph::Graph() {
    adjacency_matrix = nullptr;
    vertexes = new GraphList<Vertex>();
    minimum_path_algorithm = nullptr;
}


void Graph::add_vertex(int x_coordinate, int y_coordinate, char type) {
    expand_adjacency_matrix();
    vertexes -> add(x_coordinate, y_coordinate, type);
}


void Graph::add_path(int starting_x_coordinate, int starting_y_coordinate, int end_x_coordinate, int end_y_coordinate, int weight) {
    int origin_position = vertexes ->get_position(starting_x_coordinate, starting_y_coordinate);
    int destiny_position = vertexes ->get_position(end_x_coordinate, end_y_coordinate);

    if(origin_position == NOT_FOUND_POSITION){
        cout << "The vertex whit coordinates " << "(" << to_string(starting_x_coordinate) << ", " << to_string(starting_y_coordinate) << ")" << " doesn't exists in graph" << endl;
    }
    if(destiny_position == NOT_FOUND_POSITION){
        cout << "The vertex whit coordinates " << "(" << to_string(end_x_coordinate) << ", " << to_string(end_y_coordinate) << ")" << " doesn't exists in graph" << endl;
    }

    if(!(destiny_position == NOT_FOUND_POSITION || origin_position == NOT_FOUND_POSITION)) {
        adjacency_matrix[origin_position][destiny_position] = weight;
    }
}


char Graph::get_tile_type(int x_coordinate, int y_coordinate) {
  return vertexes->get_type(x_coordinate, y_coordinate);
}

stack<Vertex> Graph::minimum_path(int starting_x_coordinate, int starting_y_coordinate, int end_x_coordinate,
                        int end_y_coordinate, int player_energy, int &movement_cost) {
    int origin_position = vertexes ->get_position(starting_x_coordinate, starting_y_coordinate);
    int destiny_position = vertexes ->get_position(end_x_coordinate, end_y_coordinate);

    if(origin_position == NOT_FOUND_POSITION){
        cout << "The vertex whit coordinates " << "(" << to_string(starting_x_coordinate) << ", " << to_string(starting_y_coordinate) << ")" << "  doesn't exists in graph" << endl;
    }

    if(destiny_position == NOT_FOUND_POSITION){
        cout << "The vertex whit coordinates  " << "(" << to_string(end_x_coordinate) << ", " << to_string(end_y_coordinate) << ")" << "  doesn't exists in graph" << endl;
    }

    if(origin_position != NOT_FOUND_POSITION && destiny_position != NOT_FOUND_POSITION)
        return minimum_path(origin_position, destiny_position, player_energy, movement_cost);

    else {
        stack<Vertex> vertex_traversed;
        return vertex_traversed;
    }

}


void Graph::expand_adjacency_matrix() {
    int** aux_matrix;
    int new_vertexes_amount = vertexes->get_elements_amount() + 1;

    aux_matrix = new int*[new_vertexes_amount];
    for(int i = 0; i < new_vertexes_amount; i++){
        aux_matrix[i] = new int[new_vertexes_amount];
    }

    copy_adjacency_matrix(aux_matrix);
    initialize_new_vertex(aux_matrix);
    break_free_adjacency_matrix();
    adjacency_matrix = aux_matrix;
}

void Graph::copy_adjacency_matrix(int** new_adjacent) {
    for(int i = 0; i < vertexes -> get_elements_amount(); i++){
        for(int j = 0; j < vertexes -> get_elements_amount(); j++){
            new_adjacent[i][j] = adjacency_matrix[i][j];
        }
    }
}

void Graph::initialize_new_vertex(int** new_adjacent) {
    for(int i = 0; i < vertexes -> get_elements_amount(); i++){
        new_adjacent[vertexes -> get_elements_amount()][i] = INFINITY;
        new_adjacent[i][vertexes -> get_elements_amount()] = INFINITY;
    }
    new_adjacent[vertexes -> get_elements_amount()][vertexes -> get_elements_amount()] = 0;
}



void Graph::break_free_adjacency_matrix() {
    for(int i = 0; i < vertexes -> get_elements_amount(); i++){
        delete[] adjacency_matrix[i];
    }
    delete[] adjacency_matrix;
}

Graph::~Graph() {
    break_free_adjacency_matrix();
    adjacency_matrix = nullptr;
    delete vertexes;
    delete minimum_path_algorithm;
}



stack<Vertex> Graph::minimum_path(int origin, int destiny, int player_energy, int &movement_cost) {
    return minimum_path_algorithm -> minimum_path(origin, destiny, player_energy, movement_cost);
}

void Graph::use_dijkstra() {
    delete minimum_path_algorithm;
    minimum_path_algorithm = new Dijkstra(vertexes, adjacency_matrix);
}

void Graph::add_obstacle(int x_coordinate, int y_coordinate, int total_of_rows, int total_of_columns) {
  if (x_coordinate != 0)
    add_path(x_coordinate - 1, y_coordinate, x_coordinate, y_coordinate, INFINITY);
  if (x_coordinate != total_of_rows - 1)
      add_path(x_coordinate + 1, y_coordinate, x_coordinate, y_coordinate, INFINITY);
  if (y_coordinate != 0)
      add_path(x_coordinate, y_coordinate - 1, x_coordinate, y_coordinate, INFINITY);
  if (y_coordinate != total_of_columns - 1)
      add_path(x_coordinate, y_coordinate + 1, x_coordinate, y_coordinate, INFINITY);
}

void Graph::remove_obstacle(int x_coordinate, int y_coordinate, int total_of_rows, int total_of_columns, int player_id) {
  char tile_type = vertexes->get_type(x_coordinate, y_coordinate);
  int weight = get_weight(tile_type, player_id);
  if (x_coordinate != 0)
      add_path(x_coordinate - 1, y_coordinate, x_coordinate, y_coordinate, weight);
  if (x_coordinate != total_of_rows - 1)
      add_path(x_coordinate + 1, y_coordinate, x_coordinate, y_coordinate, weight);
  if (y_coordinate != 0)
      add_path(x_coordinate, y_coordinate - 1, x_coordinate, y_coordinate, weight);
  if (y_coordinate != total_of_columns - 1)
      add_path(x_coordinate, y_coordinate + 1, x_coordinate, y_coordinate, weight);
}
