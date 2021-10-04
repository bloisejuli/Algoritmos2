#include "herramientas.h"

#include <iostream>
#include <fstream>

using namespace std;

const string PATH_MATERIALES = "materiales.txt";
const string PATH_EDIFICIOS = "edificios.txt";

const int ERROR = -1;

const int OPCIONES_VALIDAS = 6;


const string PIEDRA = "piedra";
const string MADERA = "madera";
const string METAL = "metal";


const int MAX_MATERIALES_NECESARIOS = 3;

const int LISTAR_MATERIALES = 1, CONSTRUIR_EDIFICIO = 2, LISTAR_EDIFICIOS_CONSTRUIDOS = 3;
const int LISTAR_TODOS_LOS_EDIFICIOS = 4, DEMOLER_EDIFICIO = 5;  

const string COLOR_AMARILLO = "\e[1;33m";
const string COLOR_POR_DEFECTO = "\e[0m";
const string SUBRAYADO_AMARILLO = "\e[43;1;37m";
const string LETRA_EN_NEGRITA = "\e[;1;37m";


void cargar_materiales(Material materiales[MAX_MATERIALES], int &tope) {
    ifstream archivo_materiales(PATH_MATERIALES);
    string cantidad;
    
    if(!archivo_materiales.fail()){
        while(archivo_materiales >> materiales[tope].material){
            archivo_materiales >> cantidad;
            materiales[tope].cantidad_de_material = stoi(cantidad);
            tope++;
        }
        
        archivo_materiales.close();

    } else {
        cout << "El archivo no se abrio correctamente" << endl;
    }
}


void cargar_ciudad(Edificio edificios[MAX_EDIFICIOS], int &tope) {
    ifstream archivo_edificios(PATH_EDIFICIOS);
    
    string cantidad;

    if(!archivo_edificios.fail()){
        while(archivo_edificios >> edificios[tope].nombre){
            archivo_edificios >> cantidad;
            edificios[tope].cant_piedra = stoi(cantidad);
            archivo_edificios >> cantidad;
            edificios[tope].cant_madera = stoi(cantidad);
            archivo_edificios >> cantidad;
            edificios[tope].cant_metal = stoi(cantidad);
            archivo_edificios >> cantidad; 
            edificios[tope].cant_construidos = stoi(cantidad);
            archivo_edificios >> cantidad;
            edificios[tope].max_permitidos = stoi(cantidad);

            tope++;
        }
        
        archivo_edificios.close();

    } else {
        cout << "El archivo no se abrio correctamente" << endl;
    }
}


void mostrar_menu() {
    cout << endl << endl;
    cout << SUBRAYADO_AMARILLO << "MENU" << COLOR_POR_DEFECTO << endl
    << '\t' << LETRA_EN_NEGRITA << "(1) Listar materiales de construcción." << endl
    << '\t' << "(2) Construir edificio por nombre." << endl
    << '\t' << "(3) Listar los edificios construidos." << endl
    << '\t' << "(4) Listar todos los edificios." << endl
    << '\t' << "(5) Demoler un edificio." << endl
    << '\t' << "(6) Guardar y salir." << COLOR_POR_DEFECTO << endl;
    cout << endl;
}


int pedir_opcion() {
    int opcion_elegida;
    cout << "Ingrese el número de la accion que desea realizar: ";
    cin >> opcion_elegida;
    cout << endl;
    return opcion_elegida;
}


void validar_opcion(int &opcion_elegida) {
    bool es_opcion_valida = opcion_elegida > 0 && opcion_elegida <= OPCIONES_VALIDAS;
    while(!es_opcion_valida){
        cout << "La opción elegida no es una opcion válida, por favor ingrese otra opción: ";
        cin >> opcion_elegida;
        es_opcion_valida = opcion_elegida > 0 && opcion_elegida <= OPCIONES_VALIDAS;
    }
}


void listar_materiales(Material materiales[MAX_MATERIALES], int tope) {
    cout << COLOR_AMARILLO << "---------- LISTA DE MATERIALES ---------- " << COLOR_POR_DEFECTO << endl;
    for (int i = 0; i < tope; i++) {
        cout << "Nombre: " << materiales[i].material << ", cantidad: " << materiales[i].cantidad_de_material << endl;
    }    

    cout << COLOR_AMARILLO << "----------------------------------------- " << COLOR_POR_DEFECTO << endl;
}


int buscar_edificio(Edificio edificios[MAX_EDIFICIOS], int tope, string edificio_buscado) {
    bool es_encontrado = false;
    int contador = 0;
    int pos_encontrada = 0;

    while(contador < tope && !es_encontrado) {
        if(edificios[contador].nombre == edificio_buscado) {
            es_encontrado = true;
            pos_encontrada = contador;
        }
        contador ++;
    }

    if(es_encontrado == false) {
        pos_encontrada = ERROR;
    }

    return (pos_encontrada);
}


string pedir_edificio() {
    string edificio;
    cout << "Ingrese el nombre del edificio: ";
    cin >> edificio;
    return edificio;
}


void encontrar_materiales_principales(Material materiales[MAX_MATERIALES], int tope, int &piedra, int &madera, int &metal) {
    int cant_materiales_encontrados = 0;
    int i = 0;

    while (i < tope && cant_materiales_encontrados < MAX_MATERIALES_NECESARIOS) {
        if(materiales[i].material == PIEDRA) {
            piedra = i;
            cant_materiales_encontrados ++;
        } else if (materiales[i].material == MADERA) {
            madera = i;
            cant_materiales_encontrados ++;
        } else if (materiales[i].material == METAL) {
            metal = i;
            cant_materiales_encontrados ++;
        }

        i++;
    }
    
}


void realizar_obra(Material materiales[MAX_MATERIALES], int tope_materiales, Edificio &obra, int piedra, int madera, int metal) {
    materiales[piedra].cantidad_de_material -= obra.cant_piedra;
    materiales[madera].cantidad_de_material -= obra.cant_madera;
    materiales[metal].cantidad_de_material -= obra.cant_metal;

    obra.cant_construidos ++;

} 


void verificar_construccion(Material materiales[MAX_MATERIALES], int tope_materiales, Edificio &obra) {
    int pos_piedra = -1, pos_madera = -1, pos_metal = -1;
    encontrar_materiales_principales(materiales, tope_materiales, pos_piedra, pos_madera, pos_metal);

    if(materiales[pos_piedra].cantidad_de_material > obra.cant_piedra && materiales[pos_madera].cantidad_de_material > obra.cant_madera &&
       materiales[pos_metal].cantidad_de_material > obra.cant_metal) {
        
        realizar_obra(materiales, tope_materiales, obra, pos_piedra, pos_madera, pos_metal);
        cout << "Se construyó " << obra.nombre << " exitosamente." << endl;

        
    } else {
        cout << "No es posible construir " << obra.nombre << " ya que no posee la cantidad necesaria de materiales" << endl;
    }   
} 


void construir_edificio(Material materiales[MAX_MATERIALES], int tope_materiales, Edificio edificios[MAX_EDIFICIOS], int tope_edificios) {
    string edificio_buscado = pedir_edificio();
    int posicion = buscar_edificio(edificios, tope_edificios, edificio_buscado);
   
    if (posicion == ERROR) {
        cout << "El edificio ingresado no se encuentra en la lista de edificios permitidos para construir en Andypolis" << endl;

    } else {
        if (edificios[posicion].cant_construidos < edificios[posicion].max_permitidos) {
            verificar_construccion(materiales, tope_materiales, edificios[posicion]); 

        } else if (edificios[posicion].cant_construidos >= edificios[posicion].max_permitidos){
            cout << "No es posible construir " << edificios[posicion].nombre << " en Andypolis porque ya alcanzo el maximo de " << 
            edificios[posicion].nombre << "s permitido." << endl;
        }
    }
}


void listar_edificios_construidos(Edificio edificios[MAX_EDIFICIOS], int tope_edificios) {
    cout << COLOR_AMARILLO << "---------- LISTA DE EDIFICIOS EXISTENTES EN ANDYPOLIS ---------- " << COLOR_POR_DEFECTO << endl;
    for (int i = 0; i < tope_edificios; i++) {
        if (edificios[i].cant_construidos > 0) {
            cout << LETRA_EN_NEGRITA << edificios[i].nombre << COLOR_POR_DEFECTO << endl
            << '\t' << "Cantidad de " << edificios[i].nombre << "s construidos hasta el momento: " << edificios[i].cant_construidos << endl;
            cout << COLOR_AMARILLO << "----------------------------------------------------------------" << COLOR_POR_DEFECTO << endl;
        }
    }
}


void listar_todos_los_edificios(Edificio edificios[MAX_EDIFICIOS], int tope_edificios) {
    cout << COLOR_AMARILLO << "---------- LISTA DE TODOS LOS EDIFICIOS DE ANDYPOLIS ---------- " << COLOR_POR_DEFECTO << endl;
    for (int i = 0; i < tope_edificios; i++) {
        cout << LETRA_EN_NEGRITA << edificios[i].nombre << COLOR_POR_DEFECTO << endl
        << '\t' << "Piedra necesaria para construir: " << edificios[i].cant_piedra << endl
        << '\t' << "Madera necesaria para construir: " << edificios[i].cant_madera << endl
        << '\t' << "Metal necesario para construir: " << edificios[i].cant_metal << endl
        << '\t' << "Cantidad de " << edificios[i].nombre << "s construidos hasta el momento: " << edificios[i].cant_construidos << endl
        << '\t' << "Maxima cantidad de " << edificios[i].nombre << "s permitidas construir: " << edificios[i].max_permitidos << endl;
    cout << endl;

    cout << COLOR_AMARILLO << "----------------------------------------------------------------" << COLOR_POR_DEFECTO << endl;

    }    
}


void eliminar_edificio (Edificio edificios[MAX_EDIFICIOS], int tope_edificios, int posicion) {
    edificios[posicion].cant_construidos --;
}


void recuperar_materiales(Material materiales[MAX_MATERIALES], int tope_materiales, Edificio edificio_demolido) {
    int pos_piedra = -1, pos_madera = -1, pos_metal = -1;
    encontrar_materiales_principales(materiales, tope_materiales, pos_piedra, pos_madera, pos_metal);
    materiales[pos_piedra].cantidad_de_material += edificio_demolido.cant_piedra/2;
    materiales[pos_madera].cantidad_de_material += edificio_demolido.cant_madera/2;
    materiales[pos_metal].cantidad_de_material += edificio_demolido.cant_metal/2;

    cout << "Se recuperan " << edificio_demolido.cant_piedra/2 << " de piedra, " << edificio_demolido.cant_madera/2 << " de madera y " <<
    edificio_demolido.cant_metal/2 << " de metal." << endl;
}


void demoler_edificio(Material materiales[MAX_MATERIALES], int tope_materiales, Edificio edificios[MAX_EDIFICIOS], int tope_edificios) {
    string edificio_a_demoler = pedir_edificio();
    int posicion = buscar_edificio(edificios, tope_edificios, edificio_a_demoler);
    if (posicion == ERROR) {
        cout << "El edificio ingresado no se encuentra en la lista de edificios construidos en Andypolis" << endl;
    } else {
        cout << "El edificio " << edificios[posicion].nombre << " fue destruido con exito." << endl;
        eliminar_edificio(edificios, tope_edificios, posicion);
        recuperar_materiales(materiales, tope_materiales, edificios[posicion]);
    }
}


void procesar_opcion(Material materiales[MAX_MATERIALES], int tope_materiales, Edificio edificios[MAX_EDIFICIOS], int tope_edificios, int opcion) { 
    switch (opcion) {
    case LISTAR_MATERIALES:
        listar_materiales(materiales, tope_materiales);
        break;
    case CONSTRUIR_EDIFICIO:
        construir_edificio(materiales, tope_materiales, edificios, tope_edificios);
        break;
    case LISTAR_EDIFICIOS_CONSTRUIDOS:
        listar_edificios_construidos(edificios, tope_edificios);
        break;
    case LISTAR_TODOS_LOS_EDIFICIOS:
        listar_todos_los_edificios(edificios, tope_edificios);
        break;
    case DEMOLER_EDIFICIO:
        demoler_edificio(materiales, tope_materiales, edificios, tope_edificios);
        break;
    }
}


void actualizar_datos(Material materiales[MAX_MATERIALES], int &tope_materiales, Edificio edificios[MAX_EDIFICIOS], int tope_edificios) {
    ofstream archivo_materiales(PATH_MATERIALES);
    ofstream archivo_edificios(PATH_EDIFICIOS);

    for(int i = 0; i < tope_materiales; i++) {
        archivo_materiales << materiales[i].material << " " << materiales[i].cantidad_de_material << "\n";
    }

    for (int j = 0; j < tope_edificios; j++) {
        archivo_edificios << edificios[j].nombre << " " << edificios[j].cant_piedra << " " << edificios[j].cant_madera << " " << 
        edificios[j].cant_metal << " " << edificios[j].cant_construidos << " " << edificios[j].max_permitidos << "\n";
    }
}
