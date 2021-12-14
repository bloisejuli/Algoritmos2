#ifndef NODE_H
#define NODE_H

template <class T>
class Node {

private:

  T* value;
  Node* next_node;

public:
  //PRE: -
  //POS: Creates a node with it's value pointing to 'value'.
  Node(T* value){
    this->value = value;
  }

  //PRE: -
  //POS: Destroys the node and the object it points to.
  ~Node() {

    delete value;

  }


  //PRE: 'pointer' must be a valid node pointer.
  //POS: Makes the node point to passed pointer.
  void set_next_node(Node* pointer);

  //PRE: -
  //POS: Returns the pointer "next_node".
  Node* get_next_node();

  //PRE: -
  //POS: Returns the value the node its pointing to.
  T* get_value();

  //PRE: -
  //POS: Changes the value of the node.
  void set_value(T new_value);

  // PRE: -
  // POS: Returns 'next_node' != 0.
  bool next_node_not_null();

};



template <class T>
void Node<T>::set_next_node(Node* pointer) {

  next_node = pointer;

}

template <class T>
Node<T>* Node<T>::get_next_node() {

  return next_node;

}

template <class T>
T* Node<T>::get_value() {

  return value;

}

template <class T>
void Node<T>::set_value(T new_value) {

  value = new_value;

}

template <class T>
bool Node<T>::next_node_not_null() {

  return (next_node != 0);

}

#endif //NODE_H
