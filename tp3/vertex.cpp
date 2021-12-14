#include "vertex.h"

Vertex::Vertex(int x_coordinate, int y_coordinate, char type) {
    this->x_coordinate = x_coordinate;
    this->y_coordinate = y_coordinate;
    this->type = type;
}

string Vertex::get_name() {
    string coordinates = "(" + to_string(x_coordinate) + ", " + to_string(y_coordinate) + ")";
    return coordinates;
}

string Vertex::get_coordinates() {
    string coordinates = to_string(x_coordinate) + " " + to_string(y_coordinate) + " ";
    return coordinates;
}

int Vertex::get_x_coordinate() {
  return x_coordinate;
}

int Vertex::get_y_coordinate() {
  return y_coordinate;
}

char Vertex::get_type() {
  return type;
}

Vertex::~Vertex() {

}