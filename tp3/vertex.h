
#ifndef GRAFOS_VERTICE_H
#define GRAFOS_VERTICE_H

#include <string>

using namespace std;

class Vertex {
    
private:
    int x_coordinate;
    int y_coordinate;
    char type;

public:
    Vertex(int x_coordinate, int y_coordinate, char type);

    string get_name();
    string get_coordinates();

    int get_x_coordinate();
    int get_y_coordinate();

    char get_type();

    ~Vertex();
};


#endif //GRAFOS_VERTICE_H
