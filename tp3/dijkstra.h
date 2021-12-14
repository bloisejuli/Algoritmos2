#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <string>
#include "graph_list.h"
#include "vertex.h"
#include "constants.h"
#include <iostream>
#include <stack>

using namespace std;

class Dijkstra{

private:
    int ** adjacency_matrix;
    GraphList<Vertex> * vertexes;
    int vertexes_amount;

    bool * visited_vertexes;
    int * distance;
    int * path;

//Métodos
    

public:
    Dijkstra(GraphList<Vertex> * vertexes, int ** adjacency_matrix);

    //post: muestra por pantalla el camino mínimo entre el origen y el destino, detallando su recorrido y peso
    stack<Vertex> minimum_path(int origin, int destiny, int player_energy, int &movement_cost);

    ~Dijkstra(); //YES

private:

 //post: pone todos los valores del vector de verticesVisitados en "false" menos el origen
    void initialize_visiteds(int origin);

    //post: pone las distancias exactamente igual que la distanciaOrigen
    void initialize_distance(const int * origin_distance);

    //post: llena el vector de recorrido con el origen
    void initialize_path(int origin);

    //post: devuelve el número de vértice con menor distancia al origen
    int vertex_minimum_distance();
    
    //post: actualiza el vector de distancias y el de recorrido con los valores que impone vertice.
    void update_distance(int vertex);

    //pre: para que tenga sentido, debe ejecutarse un recorrido previamente
    //post: muestra por pantalla el resultado del recorrido.
    stack<Vertex> show_path(int origin, int destiny);
};


#endif //DIJKSTRA_H