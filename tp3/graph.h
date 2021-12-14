#ifndef GRAFOS_GRAFO_H
#define GRAFOS_GRAFO_H
#include <string>
#include "vertex.h"
#include "dijkstra.h"
#include "utils.h"

using namespace std;

class Graph {
/*ATRIBUTOS*/
private:
    int ** adjacency_matrix;
    GraphList<Vertex> * vertexes;
    Dijkstra * minimum_path_algorithm;

/*MÃ‰TODOS*/

    //pre: tienen que existir tanto el origen como el destino. Ademas se deben haber calculado las matrices de Floyd
    //post: muestra el camino minimo entre el origen y el destino
    stack<Vertex> minimum_path(int origin, int destiny, int player_energy, int &movement_cost);

    //post: agranda dinamicamente la matriz de adyacencia
    void expand_adjacency_matrix(); //YES

    //pre: la matriz que se le envie ya debe tener memoria reservada
    //post: copia la matriz de adyacencia en la nueva matriz
    void copy_adjacency_matrix(int** new_adjacent); //YES

    //post inicializa un nuevo vertice en la matriz de adyacencia con un valor de infinito
    void initialize_new_vertex(int** new_adjacent); //YES

    //post libera la memoria de la matriz de adyacencia
    void break_free_adjacency_matrix(); //YES

public:

    Graph(); //yes
    //pre: No hay vertices repetidos en nombre
    //post: agrega un nuevo vertice al grafo
    void add_vertex(int x_coordinate, int y_coordinate, char type); //YES

    //pre: se debe tener un algortimo para calcular el camino mÃ­nimo previamente elegido
    //post: muestra por terminal el camino mÃ­nimo desde un origen a un destino
    stack<Vertex> minimum_path(int starting_x_coordinate, int starting_y_coordinate, int end_x_coordinate,
                                int end_y_coordinate, int player_energy, int &movement_cost); //YES

    //pre: el peso es un valor positivo
    //post: Ajusta la matriz de adyacencia con el peso ingresado
    void add_path(int starting_x_coordinate, int starting_y_coordinate, int end_x_coordinate, int end_y_coordinate, int peso); //YES

    char get_tile_type(int x_coordinate, int y_coordinate);

    //post: selecciona el algortimo de Floyd para calcular el camino mÃ­nimo
    // void usarFloyd(); //YES

    //post: selecciona el algortimo de Dijkstra para calcular el camino mÃ­nimo
    void use_dijkstra();

    void add_obstacle(int x_coordinate, int y_coordinate, int total_of_rows, int total_of_columns);

    void remove_obstacle(int x_coordinate, int y_coordinate, int total_of_rows, int total_of_columns, int player_id);


    ~Graph();
};


#endif //GRAFOS_GRAFO_H