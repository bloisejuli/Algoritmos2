#ifndef LIST_H
#define LIST_H
#include <fstream>
#include <iostream>
#include "constants.h"
#include "utils.h"
#include "node.h"

template <class T>
class List {

private:
    Node<T>* first_node;
    Node<T>* current_node;
    Node<T>* previous_node;

public:
    
    //PRE: -
    //POS: Creates an empty list.
    List(){

      first_node = 0;
      current_node = 0;
      previous_node = 0;

    }

    //PRE: -
    //POS: Empties the list and then deletes it.
    ~List(){

      while(first_node != 0){

        Node<T>* aux = first_node->get_next_node();

        delete first_node;

        first_node = aux;

      }

    }

    //PRE: -
    //POS: Creates a new node poiting to 'value' and adds it to the beginning of the list.
    void add_node(T* value);

    //PRE: -
    //POS: 'current_node' = 'previous_node'.
    void reset_current_node();

    //PRE: -
    //POS: Returns 'first_node'
    Node<T>* get_first_node();

    //PRE: -
    //POS: Returns 'current_node' == 0
    bool current_node_null();

    //PRE: -
    //POS: Returns a pointer to the value that current node is pointing or 0 if 'current_node' = 0
    T* get_current_value();

    //PRE: -
    //POS: 'previous_node' = 'current_node' and current_node to the next node on the list.
    void next_node();

    //PRE: -
    //POS: Deletes current node.
    void delete_current_node();

};

template <class T>
void List<T>::add_node(T* value) {

  Node<T>* new_node = new Node<T>(value);

  new_node->set_next_node(first_node);

  first_node = new_node;

  reset_current_node();

}

template <class T>
void List<T>::reset_current_node() {

  previous_node = 0;
  current_node = first_node;

}

template<class T>
Node<T>* List<T>::get_first_node() {

  return first_node;

}

template <class T>
bool List<T>::current_node_null() {

  return current_node == 0;

}

template <class T>
T* List<T>::get_current_value() {

  if(current_node != 0)
    return current_node->get_value();

  return 0;

}

template <class T>
void List<T>::next_node() {

  previous_node = current_node;
  current_node = current_node->get_next_node();

}

template <class T>
void List<T>::delete_current_node() {

  //Case the node to delete is the first one on the list.
  if (current_node == first_node) {

    first_node = first_node->get_next_node();

    delete current_node;

  }

  //Case the node to delete is not the first one on the list.
  else {

    previous_node->set_next_node(current_node->get_next_node());

    delete current_node;

  }

  reset_current_node();

}

#endif //LIST_H
