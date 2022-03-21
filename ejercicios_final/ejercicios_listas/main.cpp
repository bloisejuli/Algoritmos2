#include <iostream>
#include "lista.h"

using namespace std;

int main() {
   /*std::cout << "Ejercicio 1 de modelo de final." << endl;
    Lista l;

    l.insertar(2, 1);
    l.insertar(10, 2);
    l.insertar(4, 3);
    l.insertar(3, 4);
    l.mostrar();

    std::cout << endl;

    l.intercambiar_datos(2, 4);
    l.mostrar();*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*std::cout << "Ejercicio 2 de modelo de final." << endl;
    Lista l1;
    Lista l2;
    Lista l3;

    l1.insertar(6, 1);
    l1.insertar(10, 2);
    l1.insertar(4, 3);
    l1.insertar(3, 4);
    l1.mostrar();

    l2.insertar(0, 1);
    l2.insertar(1, 2);
    l2.insertar(2, 3);
    l2.insertar(3, 4);
    l2.mostrar();

    l3.mostrar();

    std::cout << endl;
    l2.unir_listas(l3);
    l2.mostrar();*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*std::cout << "Ejercicio 3 de modelo de final." << endl;
    Lista l1;
    Lista l2;
    Lista* l3;

    l1.insertar(2, 1);
    l1.insertar(10, 2);
    l1.insertar(4, 3);
    l1.insertar(3, 4);
    l1.mostrar();

    l2.insertar(0, 1);
    l2.insertar(1, 2);
    l2.insertar(2, 3);
    l2.insertar(3, 4);
    l2.insertar(3, 5);
    l2.mostrar();
    
    l3 = l1.unir_listas_en_una_nueva(l2);
    l3->mostrar();*/

    /*std::cout << "Ejercicio 4 de modelo de final." << endl;
    Lista l;

    l.insertar(1, 1);
    l.insertar(2, 2);
    l.insertar(3, 3);
    l.insertar(4, 4);
    l.insertar(5, 5);
    l.mostrar();

    l.invertir();
    l.mostrar();*/

    /*std::cout << "Ejercicio 5 de modelo de final." << endl;
    Lista l1;
    Lista* l2;

    l1.insertar(1, 1);
    l1.insertar(2, 2);
    l1.insertar(3, 3);
    l1.insertar(4, 4);
    l1.insertar(5, 5);
    l1.mostrar();

    l2 = l1.revertir_lista();
    l2->mostrar();*/

    /*std::cout << "Ejercicio 6 de modelo de final." << endl;
    Lista l1;
    Lista l2;
    
    l1.insertar(1, 1);
    l1.insertar(4, 2);
    l1.insertar(5, 3);
    l1.insertar(7, 4);
    l1.insertar(9, 5);
    l1.mostrar();

    l2.insertar(2, 1);
    l2.insertar(5, 2);
    l2.insertar(6, 3);
    l2.insertar(10, 4);
    l2.mostrar();
    
    l1.merge_lista(l2);
    l1.mostrar();*/

    /*std::cout << "Ejercicio 7 de modelo de final." << endl;
    Lista l;
    
    l.insertar(1, 1);
    l.insertar(4, 2);
    l.insertar(5, 3);
    l.insertar(7, 4);

    l.mostrar();

    l.eliminar_dato(7);
    l.mostrar();*/

    /*std::cout << "Ejercicio 8 de modelo de final." << endl;
    Lista l;

    l.insertar(1, 1);
    l.insertar(1, 2);
    l.insertar(4, 3);
    l.insertar(1, 4);
    l.insertar(5, 5);
    l.insertar(7, 6);
    l.insertar(1, 7);
    l.insertar(1, 8);
    l.insertar(2, 9);
    

    l.mostrar();

    l.eliminar_ocurrencias(1);
    l.mostrar();*/

    std::cout << "Ejercicio 9 de modelo de final." << endl;
    Lista a;
    Lista b;
    Lista* c;


    a.insertar(1, 1);
    a.insertar(2, 2);
    a.insertar(3, 3);
    a.insertar(4, 4);        
    a.insertar(5, 5);
    a.insertar(6, 6);
    std::cout << "Lista A: " << endl;
    a.mostrar();

    b.insertar(1, 1);
    b.insertar(3, 2);
    b.insertar(5, 3);
    b.insertar(7, 4);
    b.insertar(6, 5);
    b.insertar(10, 6);
    b.mostrar();

    c = a.restar(b);
    c->mostrar();

    return 0;
}