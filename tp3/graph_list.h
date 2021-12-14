#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H
#include <string>
#include "graph_node.h"
#include "constants.h"

using namespace std;

template < typename T >
class GraphList{

private:
    int elements_amount;
    GraphNode<T>* first;
    GraphNode<T>* latest;

public:

    //PRE: -
    //POS: Creates GraphList object.
    GraphList();

    //PRE: -
    //POS: Returns the elements amount of the list.
    int get_elements_amount();

    //PRE: -
    //POS: Returns the position of the node who has said coordinates or -1 if cannot find it.
    int get_position(int x_coordinate, int y_coordinate);

    //PRE: -
    //POS: Returns the name found in the received position or NOT_FOUND_NAME if it cannot be found.
    string get_name(int position);

    T* get_vertex(int position);

    //PRE: - 
    //POS: Returns coordinates 
    string get_coordinates(int position);

    //PRE: - 
    //POS: Returns type element
    char get_type(int x_coordinate, int y_coordinate);

    //PRE:
    //POS: Adds a new element at the list
    void add(int x_coordinate, int y_coordinate, char type);

    //PRE: -
    //POS: Destroys GraphList object.
    ~GraphList();
};

template < typename T >
GraphList<T>::GraphList(){
    elements_amount = 0;
    latest = nullptr;
    first =  nullptr;
}

template < typename T >
int GraphList<T>::get_elements_amount() {
    return elements_amount;
}

template < typename T >
int GraphList<T>::get_position(int x_coordinate, int y_coordinate) {
    bool found_element = false;
    int i = 0;
    GraphNode<T>* aux= first;

    while(!found_element && i < elements_amount){
        if(aux->get_x_coordinate() == x_coordinate &&
                aux->get_y_coordinate() == y_coordinate){
            found_element = true;
        }
        i++;
        aux = aux -> get_next_node();
    }

    if(!found_element){
        return NOT_FOUND_POSITION;
    }
    return i - 1;
}

template < typename T >
void GraphList<T>::add(int x_coordinate, int y_coordinate, char type) {
    GraphNode<T>* new_node = new GraphNode<T>(x_coordinate, y_coordinate, type);
    if(first == nullptr){
        first = new_node;
        latest = first;
    } else {
        latest -> set_next_node(new_node);
        latest = new_node;
    }
    elements_amount++;
}

template<typename T>
GraphList<T>::~GraphList() {
    GraphNode<T>* next;
    while(first != nullptr){
        next = first -> get_next_node();
        delete first;
        first = next;
    }
}

template<typename T>
string GraphList<T>::get_name(int position) {
    int i = 0;
    GraphNode<T>* aux = first;

    if(position > elements_amount){
        return NOT_FOUND_NAME;
    }

    while(i != position - 1){
        aux = aux -> get_next_node();
        i++;
    }
    return aux -> get_name();
}

template < typename T >
T* GraphList<T>::get_vertex(int position) {
    int i = 0;
    GraphNode<T>* aux = first;

    if(position > elements_amount){
        return 0;
    }

    while(i != position - 1){
        aux = aux -> get_next_node();
        i++;
    }
    return aux->get_vertex();
}

template<typename T>
string GraphList<T>::get_coordinates(int position) {
    int i = 0;
    GraphNode<T>* aux = first;

    if(position > elements_amount){
        return NOT_FOUND_NAME;
    }

    while(i != position - 1){
        aux = aux -> get_next_node();
        i++;
    }
    return aux->get_coordinates();
}

template < typename T >
char GraphList<T>::get_type(int x_coordinate, int y_coordinate) {
    bool found_element = false;
    char element_type;
    int i = 0;
    GraphNode<T>* aux = first;

    while(!found_element && i < elements_amount){
        if(aux->get_x_coordinate() == x_coordinate &&
            aux->get_y_coordinate() == y_coordinate){
            found_element = true;
            element_type = aux->get_type();
        }

        i++;
        aux = aux -> get_next_node();
    }

    if(!found_element){
        return 'Z';
    }
    return element_type;
}

#endif //GRAPH_LIST_H