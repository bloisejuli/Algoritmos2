#ifndef HERRAMIENTAS_H
#define HERRAMIENTAS_H

#include <string>

using namespace std;

const int MAX_MATERIALES = 50, MAX_EDIFICIOS = 200;

const int GUARDAR_Y_SALIR = 6;

struct Material {
    string material;
    int cantidad_de_material;
};

struct Edificio {
    string nombre;
    int cant_piedra; 
    int cant_madera;
    int cant_metal; 
    int cant_construidos; 
    int max_permitidos;
};

#ifdef __linux__
#define CLR_SCREEN "clear"
#endif // __linux__

#ifdef __MINGW32__
#define CLR_SCREEN "CLS"
#endif // __MINGW32__

/*
 * PRE: Recibe un vector de materiales sin inicializar, con un tope inicializado en cero.
 * POST: Carga el vector con los datos del archivo PATH_MATERIALES, si el archivo no se abre imprime por pantalla un mensaje.
 */
void cargar_materiales(Material materiales[MAX_MATERIALES], int &tope);

/*
 * PRE: Recibe un vector de edificios sin inicializar, con su tope inicializado en cero.
 * POST: Carga el vector con los datos del archivo PATH_EDIFICIOS, si el archivo no se abre imprime por pantalla un mensaje.
 */
void cargar_ciudad(Edificio edificios[MAX_EDIFICIOS], int &tope);

/*
 * PRE: -
 * POST: Imprime por pantalla el menu de opciones.
 */
void mostrar_menu();

/*
 * PRE: -
 * POST: Devuelve un entero con la opción ingresada por el usuario.
 */
int pedir_opcion();

/*
 * PRE: Recibe la opcion elegida precargada
 * POST: Si la opcion esta fuera del rango de las OPCIONES_VALIDAS, imprime por pantaLLA un mensaje al usuario pidiendole que ingrese un nuevo número.
 */
void validar_opcion(int &opcion_elegida);

/*
 * PRE: Recibe un vector de materiales y su respectivo tope, correctamente cargados.
 * POST: Imprime por pantalla los nombres y la cantidad de cada material.
 */
void listar_materiales(Material materiales[MAX_MATERIALES], int tope);


/*
 * PRE: Recibe un vector de edificios y su respectivo tope, correctamente cargados, y además, un edificio_buscado.
 * POST: Devuelve la posicion en la que se encuentra edificio_buscado en el vector edificios y sino se encuentra devuelve ERROR.
 */
int buscar_edificio(Edificio edificios[MAX_EDIFICIOS], int tope, std::string edificio_buscado);

/*
 * PRE: - 
 * POST: Devuelve un string edificio que el usuario ingreso.
 */
std::string pedir_edificio();

/*
 * PRE: Recibe un vector de materiales y su respectivo tope correctamente cargados, además las posiciones de piedra, madera y metal, precargadas.
 * POST: Modifica el valor de las variables piedra, madera y metal poniendo las posiciones en las que se encuentran en el vector de materiales.
 */
void encontrar_materiales_principales(Material materiales[MAX_MATERIALES], int tope_materiales, int &piedra, int &madera, int &metal);

/*
 * PRE: Recibe un vector de materiales y su tope correctamente cargados, la obra que se construye y los enteros piedra, madera y metal que indican  las posiciones de los 
 *      mismos en el vector de materiales 
 * POST: Modifica las cantidades de los materiales PIEDRA, MADERA y METAL del vector de materiales y aumenta en 1 la cantidad de obra en Andypolis.
 */
void realizar_obra(Material materiales[MAX_MATERIALES], int tope_materiales, Edificio &obra, int piedra, int madera, int metal);

/*
 * PRE: Recibe un vector de materiales y su respectivo tope, correctamento cargados, y además, recibe la obra que se desea construir previamente cargada. 
 * POST: Imprime por pantalla si la obra se construyó o si no fue posible construirla.
 */
void verificar_construccion(Material materiales[MAX_MATERIALES], int tope_materiales, Edificio &obra);

/*
 * PRE: Recibe un vector de materiales y un vector de edificios con sus respectivos topes, todo correctamente cargado.
 * POST: Imprime por panralla si el edificio ingresado no se encuentra o si no se pudo construir, y sino lo construye. 
 */
void construir_edificio(Material materiales[MAX_MATERIALES], int tope_materiales, Edificio edificios[MAX_EDIFICIOS], int tope_edificios);

/*
 * PRE: Recibe un vector de edificios y su tope, correctamente cargados.
 * POST: Imprime por pantalla los edificios construidos hasta el momento en Andypolis.
 */
void listar_edificios_construidos(Edificio edificios[MAX_EDIFICIOS], int tope_edificios);

/*
 * PRE: Recibe un vector de edificios y su tope, correctamente cargados.
 * POST: Imprime por pantalla los edificios que se encuentran en PATH_EDIFICIOS, la cantidad de PIEDRA, MADERA y METAL que se necesita para construir,
  * la cantidad que ya hay construida y la cantidad máxima permitida de cada edificio.
 */
void listar_todos_los_edificios(Edificio edificios[MAX_EDIFICIOS], int tope_edificios);
/*
 * PRE: Recibe un vector de edificios y su tope, correctamente cargados y la posicion del edificio que se desea eliminar.
 * POST: Decrementa en uno la cantidad de edificios.
 */
void eliminar_edificio (Edificio edificios[MAX_EDIFICIOS], int tope_edificios, int posicion);

/*
 * PRE: Recibe un vector de materiales y su tope, correctamente cargados, y el edificio que fue eliminado.
 * POST: Aumenta la cantidad de PIEDRA, MADERA y METAL en la mitad de la que es necesaria para construir el edificio que fue demolido y lo imprime por pantalla.
 */
void recuperar_materiales(Material materiales[MAX_MATERIALES], int tope_materiales, Edificio edificio_demolido);

/*
 * PRE: Recibe un vector de materiales y un vector de edificios con sus respectivos topes, todo correctamente cargado.
 * POST: Imprime por pantalla si el edificio se puede demoler o no.
 */
void demoler_edificio(Material materiales[MAX_MATERIALES], int tope_materiales, Edificio edificios[MAX_EDIFICIOS], int tope_edificios);


/*
 * PRE: Recibe un vector de materiales y un vector de edificios con sus respectivos topes, todo correctamente cargado, y la opcion ingresada por el usuario.
 * POST: Según haya sido la opción ingresada realiza lo indicado.
 */
void procesar_opcion(Material materiales[MAX_MATERIALES], int tope_materiales, Edificio edificios[MAX_EDIFICIOS], int tope_edificios, int opcion);

/*
 * PRE: Recibe un vector de materiales y un vector de edificios con sus respectivos topes, todo correctamente cargado.
 * POST: Sobre escribe los archivos PHAT_MATERIALES y PATH_EDIFICIOS con los datos actualizados.
 */
void actualizar_datos(Material materiales[MAX_MATERIALES], int &tope_materiales, Edificio edificios[MAX_EDIFICIOS], int tope_edificios);

#endif //HERAMIENTAS_H