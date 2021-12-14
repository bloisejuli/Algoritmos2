#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H
#include <string>

using namespace std;

template < typename T >
class GraphNode {

private:
    T* element;
    GraphNode<T>* next;

public:
    
    //PRE: - 
    //POS: Creates GraphNode object.
    GraphNode(int x_coordinate, int y_coordinate, char type);

    //PRE: -
    //POS: Returns the next node.
    GraphNode<T>* get_next_node();

    //PRE: -
    //POS: Returns name node.
    string get_name();

    T* get_vertex();

    //PRE: -
    //POS: Returns coordinates.
    string get_coordinates();

    //PRE: -
    //POS: Returns x coordinate.
    int get_x_coordinate();

    //PRE: -
    //POS: Returns y coordinate.
    int get_y_coordinate();

    //PRE: -
    //POS: Returns element type.
    char get_type();

    //PRE: -
    //POS: Sets the GraphNode received as the next one.
    void set_next_node(GraphNode<T>* next);

    //PRE: -
    //POS: Destroys GraphNode object.
    ~GraphNode();
};

template<typename T>
GraphNode<T>::GraphNode(int x_coordinate, int y_coordinate, char type) {
    element = new T(x_coordinate, y_coordinate, type);
    next = nullptr;
}

template<typename T>
GraphNode<T> *GraphNode<T>::get_next_node() {
    return next;
}

template<typename T>
string GraphNode<T>::get_name() {
    return element -> get_name();
}

template<typename T>
T* GraphNode<T>::get_vertex() {
    return element;
}

template<typename T>
string GraphNode<T>::get_coordinates() {
    return element->get_coordinates();
}

template<typename T>
int GraphNode<T>::get_x_coordinate() {
  return element -> get_x_coordinate();
}

template<typename T>
int GraphNode<T>::get_y_coordinate() {
  return element -> get_y_coordinate();
}

template<typename T>
char GraphNode<T>::get_type() {
  return element -> get_type();
}

template<typename T>
void GraphNode<T>::set_next_node(GraphNode<T> *next) {
    this -> next = next;
}

template<typename T>
GraphNode<T>::~GraphNode() {
    delete element;
}


#endif //GRAPH_NODE_H