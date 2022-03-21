#include "lista.h"

Lista::Lista() {
    primero = 0;
    longitud = 0;
}

Lista::Lista(const Lista& lista) : Lista() {
    *this = lista;
}

bool Lista::vacia() {
    return (longitud == 0);
}

int Lista::obtener_longitud() {
    return longitud;
}

void Lista::insertar(Dato d, int pos) {
    Nodo* nuevo = new Nodo(d);
    Nodo* siguiente = primero;    

    if(pos == 1)
        primero = nuevo;
    else {
        Nodo* anterior = obtener_nodo(pos - 1);
        siguiente = anterior->obtener_siguiente();
        anterior->cambiar_siguiente(nuevo);
    }
    
    nuevo->cambiar_siguiente(siguiente);
    longitud++;
}

void Lista::eliminar(int pos) {
    Nodo* baja = primero;
    
    if (pos == 1) 
        primero = baja->obtener_siguiente();
    else {
        Nodo* anterior = obtener_nodo(pos - 1);
        baja = anterior->obtener_siguiente();
        anterior->cambiar_siguiente(baja->obtener_siguiente());
    }
    
    longitud--;
    delete baja;
}

Dato Lista::obtener_dato(int pos) {
    Nodo* aux = obtener_nodo(pos);
    return aux->obtener_dato();
}

void Lista::cambiar_dato(Dato d, int pos) {
    Nodo* aux = obtener_nodo(pos);
    aux->cambiar_dato(d);
}

Nodo* Lista::obtener_nodo(int pos) {
    Nodo* aux = primero;
    
    for(int i = 1; i < pos; i++)  
        aux = aux->obtener_siguiente();

    return aux;
}

Lista::~Lista() {
    while(!vacia()) 
        eliminar(1);
};

//////////////////////////////// Método necesario para imprimir por pantalla;
    void Lista::mostrar() {
        Nodo* aux = primero;
        std::cout << "[";
        while (aux) {
            std::cout << aux->obtener_dato() << " ";
            aux = aux->obtener_siguiente();
        }
        std::cout << "]";
        std::cout << std::endl;
    }


 /////////////////////////////// Ejercicio 1
    void Lista::intercambiar_datos(int pos_1, int pos_2) {
        Dato dato_1 = obtener_dato(pos_1);
        Dato dato_2 = obtener_dato(pos_2);

        cambiar_dato(dato_2, pos_1);
        cambiar_dato(dato_1, pos_2);

    }

// Forma, al parecer, más eficiente
    void Lista::intercambiar(int x, int y) {
        Dato elemento1 = this->obtener_dato(x);
        Dato elemento2 = this->obtener_dato(y);

        this->cambiar_dato(elemento1, y);
        this->cambiar_dato(elemento2, x);
    }

/////////////////////////////// Ejercicio 2
    void Lista::unir_listas(Lista& l) {
        int posicion = longitud;
        Dato d;

        for(int i = 1; i <= l.longitud; i++) {
            d = l.obtener_dato(i);
            posicion++;
            insertar(d, posicion);
        }

        longitud = posicion;
    }

// Forma mas eficiente
void Lista::unir(Lista& l) {
    int posicion = obtener_longitud();
    Nodo* actual = primero;

    while(actual != nullptr) {
        Dato d = actual->obtener_dato();
        posicion++;

        insertar(d, posicion);

        actual = actual->obtener_siguiente();
    }
}


/////////////////////////////// Ejercicio 3
    Lista* Lista::unir_listas_en_una_nueva(Lista& l)  {
        Lista* nueva = new Lista();

        Nodo* actual = primero;
        int posicion = 1;

        while(actual != nullptr) {
            Dato d = actual->obtener_dato();
            nueva->insertar(d, posicion);
            posicion++;

            actual = actual->obtener_siguiente();
            
            if(posicion == obtener_longitud())
                actual = l.primero;
        }
    
        return nueva;
    }

/////////////////////////////// Ejercicio 4
    void Lista::invertir_lista() {
        int cantidad = obtener_longitud();
        int contador = 1;

        while(contador < cantidad) {
            Dato d = obtener_dato(contador);
            Dato aux = obtener_dato(cantidad);

            cambiar_dato(d, cantidad);
            cambiar_dato(aux, contador);

            cantidad --;
            contador++;
        }
    }

// Forma recursiva (más eficiente)
void Lista::cambiar_nodo(Nodo* nodo) {
    Nodo* actual = nodo->obtener_siguiente();

    if(actual != nullptr) {
        cambiar_nodo(actual);
        actual->cambiar_siguiente(nodo);
    } else 
        primero = nodo;
}

void Lista::invertir() {
    Nodo* ultimo = primero;
    cambiar_nodo(primero);
    ultimo->cambiar_siguiente(nullptr);
}


/////////////////////////////// Ejercicio 5
    Lista* Lista::revertir_lista() {
        Lista* nueva = new Lista;
        Nodo* actual = primero;

        while(actual != nullptr) { 
            Dato d = actual->obtener_dato();
            /* insertamos todos los elementos en la primera posicion, de esta manera, si hay un elemento en la primera posicion, 
            *  dicho elemento pasa a la segunda posicion, el de la segunda posicion a la tercera (si es que hay algun elemento 
            *  en la segunda posicion) y asi sucesivamente, hasta que nos quede la lista al revés.
            */
            nueva->insertar(d, 1);
            actual = actual->obtener_siguiente();
        }

        return nueva;
    }

/////////////////////////////// Ejercicio 6 --- NO SALIO
    int Lista::comparar(Dato a, Dato b) {
        if (a < b)
            return -1;
        else if (a == b)
            return 0;
        else 
            return 1;
    }
    
    
    void Lista::merge_lista(Lista& l) {
        Nodo* actual = primero;
        Nodo* puntero = l.primero;
        int i = 1;

        while(actual != nullptr) {
            std::cout << "Dentro del while, iteración: " << i << std::endl;
            Dato d = actual->obtener_dato();

            if(puntero != nullptr) {
                std::cout << "Dentro del if" << std::endl;
                Dato aux = puntero->obtener_dato();
                int orden = comparar(d, aux);

                if (orden == -1) {
                    insertar(aux, i+1);
                    puntero = puntero->obtener_siguiente();
                    actual = actual->obtener_siguiente();
                }
                else if (orden == 1) {
                    insertar(aux, i);
                    puntero = puntero->obtener_siguiente();
                    actual = actual->obtener_siguiente();
                }
                else 
                    eliminar(i);
            
                std::cout << "a: " << d << " b " << aux << " orden: " << orden << std::endl;

            }

            i++;
            actual = actual->obtener_siguiente();

        }

    }

/////////////-> CODE EFICIENCIA <-

/*
*Pre: Que los parametros no sean null.
*Post: Insertara ordenadamente un nodo, en la lista.
*/
void insertar_ordenado(Nodo* primero, Nodo* nuevo) {
    if (this -> primero == nullptr || nuevo -> obtener_dato() < this -> primero -> obtener_dato()) {
        nuevo -> cambiar_siguiente(primero);
        primero = nuevo;
    } else {
        Nodo* aux = this -> primero;
        while (!aux -> obtener_siguiente() && aux -> obtener_siguiente() -> obtener_dato() < nuevo -> obtener_dato()){
            aux = aux -> obtener_siguiente();
        }
        nuevo -> cambiar_siguiente(aux -> obtener_siguiente());
        aux -> cambiar_siguiente(nuevo);
    }
}

/*
*Pre: Que la lista no sea vacía.
*Post: Lo que dice el enunciado.
*/
void Lista::unir_listas(Lista* nueva){
    Nodo* actual_lista_original = this -> primero;
    Nodo* actual_lista_nueva = nueva -> obtener_dato(1); // Obtengo el nodo que apunta a la primera posicion de la lista nueva.

    while( !actual_lista_original -> obtener_siguiente() && !actual_lista_nueva -> obtener_siguiente() ){

        int resultado_comparacion = this -> obtener_nodo(i) -> comparar_con(nueva_lista -> obtener_dato(j));

        if(resultado_comparacion == 0){

            /* 
            *  obtengo el siguiente nodo de ambas listas, ya que el elemento de la nueva lista, esta en la original,
            *  con lo cual como el enunciado me dice que no debe haber repetidos, simplemente avanzo en ambas listas.
            */
            actual_lista_original = actual_lista_original -> obtener_siguiente();
            actual_lista_nueva = actual_lista_nueva -> obtener_siguiente();
        } else if(resultado_comparacion < 0) {
            
            actual_lista_original = actual_lista_original -> obtener_siguiente();
        } else {

            this -> insertar_ordenadamente(this -> primero, actual_lista_nueva);
            actual_lista_nueva = actual_lista_nueva -> obtener_siguiente();
        }

    }

    // Agrega los elementos de la lista nueva en la original, ya que la lista original se quedo sin mas elementos para comparar.
    while( !actual_lista_nueva -> obtener_siguiente() ){
        this -> insertar_ordenadamente(this -> primero, actual_nueva_lista);
        actual_lista_nueva = actual_lista_nueva -> obtener_siguiente();
    }
    
}


/////////////////////////////// Ejercicio 7
    void Lista::eliminar_dato(Dato d) {
        int i = 1;
        bool encontrado = false;
        
        Nodo* aux = primero;

        while(!encontrado && aux != nullptr){
            Dato auxiliar = aux->obtener_dato();
            
            if (comparar(d, auxiliar) == 0){
                eliminar(i);
                encontrado = true;
            }
            aux = aux->obtener_siguiente();
            i++;
        }
    }

/////////////////////////////// Ejercicio 8
    void Lista::eliminar_ocurrencias(Dato d) {
        int i = 1;
        Nodo* aux = primero;

        while(aux != 0){
            Dato auxiliar = aux->obtener_dato();  
            
            if (comparar(d, auxiliar) == 0)
                eliminar(i);
        
            i++;
            aux = aux->obtener_siguiente();
            
        }
    }

/////////////////////////////// Ejercicio 9 
    bool Lista::dato_encontrado(Dato d){
        Nodo* puntero = primero;
        bool encontrado = false;
        
        while ((puntero != nullptr) && (!encontrado)){
            if (puntero->obtener_dato() == d)
                encontrado = true;
            else
                puntero = puntero->obtener_siguiente();
        }

        return encontrado;
    }
    
    Lista* Lista::restar(Lista& l) {
        Lista* nueva = new Lista;
        Nodo* actual = primero;

        while(actual != nullptr) {
            Dato en_comun = actual->obtener_dato();

            if(!l.dato_encontrado(en_comun))
                nueva->insertar(en_comun, nueva->obtener_longitud() + 1);

            actual= actual->obtener_siguiente();
        }

        return nueva;

    }

///////////////////////////////// elementos en comun


    Lista* Lista::interseccion(Lista lista){
        Lista* nueva_lista = new Lista;
        Dato en_comun;
        Nodo* puntero = primero;
        while (puntero != nullptr){
            en_comun = puntero->obtener_dato();
            
            if (lista.dato_encontrado(en_comun))
                nueva_lista->insertar( en_comun, nueva_lista->obtener_longitud() + 1 );
        
        puntero = puntero->obtener_siguiente();
        }
        return nueva_lista;
    }   


