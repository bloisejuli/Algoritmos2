

// void Dijkstra::show_path(int origin, int destiny, int &tiles_visited, int &coordinates_traversed) {
//     if (distance[destiny] == INFINITO){
//         // cout << "No hay un camino que conecte " <<  vertices->obtenerNombre(origen + 1) << " con " << vertices->obtenerNombre(destino + 1);
//     }else {

//         // cout << "El camino minimo que une " <<  vertices->obtenerNombre(origen + 1) << " con " << vertices->obtenerNombre(destino + 1);
//         // cout << " tiene un costo de: " << distancia[destino] << " y es el siguiente: ";
//         // cout << vertices->obtenerNombre(destino + 1);
//         do {
//             tiles_visited += vertexes->get_name(destiny + 1) + " <- ";
//             coordinates_traversed += vertexes->get_coordinates(destino + 1);
//             destiny = path[destiny];
//         } while(origin != destiny);

//         tiles_visited += vertexes->get_name(origin + 1);

//         coordinates_traversed.pop_back();
//     }
//     cout << endl;
// }

#include "dijkstra.h"

Dijkstra::Dijkstra(GraphList<Vertex> *vertexes, int **adjacency_matrix) {
    this -> vertexes = vertexes;
    this -> adjacency_matrix = adjacency_matrix;
    vertexes_amount = vertexes -> get_elements_amount();

    visited_vertexes = new bool[vertexes_amount];
    distance = new int[vertexes_amount];
    path = new int[vertexes_amount];
}

Dijkstra::~Dijkstra() {
    delete[] visited_vertexes;
    delete[] distance;
    delete[] path;
}

stack<Vertex> Dijkstra::minimum_path(int origin, int destiny, int player_energy, int &movement_cost) {
    initialize_visiteds(origin);
    initialize_distance(adjacency_matrix[origin]);
    initialize_path(origin);

    int minimum_vertex;
    bool arrived_destiny = origin == destiny;
    int travesed_vertexes = 1;

    while(!arrived_destiny){
        minimum_vertex = vertex_minimum_distance();
        arrived_destiny = minimum_vertex == destiny;

        if(!arrived_destiny){
            visited_vertexes[minimum_vertex] = true;
            update_distance(minimum_vertex);
        }
        travesed_vertexes++;
    }

    movement_cost = distance[destiny];

    if (distance[destiny] <= player_energy)
        return show_path(origin, destiny);
    else {
        stack<Vertex> vertex_traversed;
        return vertex_traversed;
    }    
}

// stack<Vertice> Dijkstra::caminoMinimo(int origen, int destino, int player_energy, int &movement_cost) {
//     inicializarVisitados(origen);
//     inicializarDistancia(matrizAdyacencia[origen]);
//     inicializarRecorrido(origen);

//     int minimoVertice;

//     bool destinoArribado = origen == destino;
//     int verticesRecorridos = 1;
//     while(!destinoArribado){
//         minimoVertice = verticeMinimaDistancia();
//         destinoArribado = minimoVertice == destino;

//         if(!destinoArribado){
//             verticesVisitados[minimoVertice] = true;
//             actualizarDistancia(minimoVertice);
//         }
//         verticesRecorridos++;
//     }

//     movement_cost = distancia[destino];

//     if (distancia[destino] <= player_energy)
//         return mostrarRecorrido(origen, destino);
//     else {
//         stack<Vertice> vertex_traversed;
//         return vertex_traversed;
//     }
// }


int Dijkstra::vertex_minimum_distance() {
    int minimum_distance = INFINITY;
    int minimum_vertex;

    for(int i = 0; i < vertexes_amount; i++){
        if(!visited_vertexes[i] && distance[i] <= minimum_distance){
            minimum_distance = distance[i];
            minimum_vertex = i;
        }
    }
    return minimum_vertex;
}

void Dijkstra::initialize_visiteds(int origin) {
    for(int i = 0; i < vertexes_amount; i++)
        visited_vertexes[i] = false;

    visited_vertexes[origin] = true;
}


void Dijkstra::initialize_path(int origin) {
    for(int i = 0; i < vertexes_amount; i++)
        path[i] = origin;
}


void Dijkstra::initialize_distance(const int *origin_distance) {
    for(int i = 0; i < vertexes_amount; i++)
        distance[i] = origin_distance[i];
}

void Dijkstra::update_distance(int vertex) {
    for(int i = 0; i < vertexes_amount; i++){
        if(!visited_vertexes[i] && distance[vertex] != INFINITY && distance[i] > adjacency_matrix[vertex][i] + distance[vertex]){
            distance[i] = adjacency_matrix[vertex][i] + distance[vertex];
            path[i] = vertex;
        }
    }
}

stack<Vertex> Dijkstra::show_path(int origin, int destiny) {
    stack<Vertex> vertex_traversed;

    if (distance[destiny] == INFINITY){ }
    else {
        do {
            vertex_traversed.push(*(vertexes->get_vertex(destiny + 1)));
            destiny = path[destiny];
        } while(origin != destiny);
        
        vertex_traversed.push(*(vertexes->get_vertex(origin + 1)));
    }
    return vertex_traversed;
}

// stack<Vertice> Dijkstra::mostrarRecorrido(int origen, int destino) {
//     stack<Vertice> vertex_traversed;

//     if (distancia[destino] == INFINITO){}
//     else {
//         do {
//             vertex_traversed.push(* ( vertices->obtenerVertice(destino + 1) ) );
//             destino = recorrido[destino];
//         } while(origen != destino);
//         vertex_traversed.push(* ( vertices->obtenerVertice(origen + 1) ) );
//     }
//     return vertex_traversed;
// }