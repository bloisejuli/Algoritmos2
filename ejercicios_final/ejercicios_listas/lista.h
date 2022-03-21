#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "nodo.h"

class Lista {

private:
    // atributos
    Nodo* primero;
    int longitud;

public:
    // Constructor sin parametros
    // PRE:
    // POS: crea una Lista de longitud 0 y primero apunta a NULL
    Lista ();

    // Constructor de copia
    // PRE: lista es una Lista valida
    // POS: crea una Lista igual a lista
    Lista (const Lista& lista);

    //////////////
    //Nodo* copiar(Nodo* origen);

    // Destructor
    // PRE:
    // POS: libera la memoria solicitada
    ~Lista ();

    // Lista vacia?
    // PRE:
    // POS: devuelve verdadero si la lista esta vacia, falso de lo contrario
    bool vacia();

    // obtener longitud de la lista
    // PRE:
    // POS: devuelve la longitud de la lista
    int obtener_longitud();

    // insertar un dato en cierta posicion
    // PRE: d dato valido y 0 < pos <= longitud + 1
    // POS: inserta el Dato d en la posicion pos (la 1 es la primera),
    //      inrementa en 1 la longitud
    void insertar(Dato d, int pos);

    // eliminar un Nodo en cierta posicion
    // PRE: 0 < pos <= longitud
    // POS: elimina el Nodo en la posicion pos (la 1 es la primera),
    //      libera memoria y decrementa en uno la longitud
    void eliminar(int pos);

    // obtiene el DAto en cierta posicion
    // PRE: 0 < pos <= longitud
    // POS: devuelve el dato que esta en la posicion pos (la 1 es la primera)
    Dato obtener_dato (int pos);

    // cambia el DAto que esta en cierta posicion
    // PRE: 0 < pos <= longitud
    // POS: cambia el dato que esta en la posicion pos (la 1 es la primera)
    void cambiar_dato (Dato d, int pos);

//////////////////////////////// Método necesario para imprimir por pantalla;
    void mostrar();

 /////////////////////////////// Ejercicio 1
 /////////////////////////////// Método que, dadas dos posiciones, intercambia sus datos
    //PRE: pos_1 y pos_2 son posiciones válidas
    //POS: intercambia los datos de los nodos en las posiciones recibidas por parametro.
    void intercambiar_datos(int pos_1, int pos_2);   

    void intercambiar(int x, int y);

/////////////////////////////// Ejercicio 2
/////////////////////////////// Método que une la lista original con otra que se pasa por parámetro, modificando a la
/////////////////////////////// lista que llama. La lista pasada por parámetro va al final
    //PRE: 
    //POS: Modifica a la lista original uniendo a la lista que pasa por parametro al final.
    void unir_listas(Lista& l);

    void unir(Lista& l);

/////////////////////////////// Ejercicio 3
/////////////////////////////// Método que une la lista original con otra que se pasa por parámetro y devuelve un
/////////////////////////////// puntero a la nueva lista. La lista pasada por parámetro va al final.
    Lista* unir_listas_en_una_nueva(Lista& l);

/////////////////////////////// Ejercicio 4
/////////////////////////////// Método que revierte la lista, modificándola (el último elemento pasa al primer lugar, etc).
    void invertir_lista();

    void cambiar_nodo(Nodo* nodo);
    void invertir();

/////////////////////////////// Ejercicio 5
/////////////////////////////// Método que revierte la lista en una nueva lista, y devuelve un puntero de la misma.
    Lista* revertir_lista();
    
/////////////////////////////// Ejercicio 6
/////////////////////////////// Método que recibe una lista por parámetro, ambas (la original y la del parámetro) están
/////////////////////////////// ordenadas, se hace un merge entre las dos, modificando la original, que tiene que quedar
/////////////////////////////// ordenada y sin elementos repetidos. Para comparar se usa un método de Dato
/////////////////////////////// (comparar), ejemplo a.comparar_con(b). Este método devuelve -1 si a es menor que b; 1,
/////////////////////////////// si a es mayor que b; y 0 si son iguales.
    int comparar(Dato a, Dato b);
    void merge_lista(Lista& l);


/////////////////////////////// Ejercicio 7
/////////////////////////////// Método que elimina un dato: se pasa un dato por parámetro y se elimina la primera
/////////////////////////////// ocurrencia. Usar el método comparar. Si no lo encuentra no hace nada.
    void eliminar_dato(Dato d);

/////////////////////////////// Ejercicio 8
/////////////////////////////// Método que elimina todas las ocurrencias del dato.
    void eliminar_ocurrencias(Dato d);

    void eliminar_datos(Dato d);

/////////////////////////////// Ejercicio 9
/////////////////////////////// Método que recibe una lista por parámetro y devuelve un puntero a una nueva lista que
/////////////////////////////// es A – B (los elementos de A que no están en B), donde A es la lista original y B es la del
/////////////////////////////// parámetro.
    Lista* restar(Lista& l);
    Lista* interseccion(Lista lista);
    bool dato_encontrado(Dato en_comun);

private:
    // devuelve un puntero al Nodo en cierta posicion
    // PRE: 0 < pos <= longitud
    // POS: devuelve un puntero al Nodo que esta en la posicion pos (la 1 es la primera)
    Nodo* obtener_nodo (int pos);

};



#endif // LISTA_H_INCLUDED
