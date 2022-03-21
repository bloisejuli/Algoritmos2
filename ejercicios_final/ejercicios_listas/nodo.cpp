#include "nodo.h"
    
Nodo::Nodo(Dato d) {
    dato = d;
    siguiente = 0;
}

void Nodo::cambiar_dato(Dato d) {
    dato = d;
}

void Nodo::cambiar_siguiente(Nodo* pn) {
    siguiente = pn;
}

Dato Nodo::obtener_dato() {
    return dato;
}

Nodo* Nodo::obtener_siguiente() {
    return siguiente;
}

int Nodo::comparar_dato(Dato d) {
    if(dato < d)
        return -1;
    else if (dato == d)
        return 0;
    else 
        return 1;
}