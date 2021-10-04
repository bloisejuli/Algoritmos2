#include "herramientas.h"

int main () {
    int opcion;
    Material materiales[MAX_MATERIALES];
    int tope_materiales = 0;
    
    Edificio edificios[MAX_EDIFICIOS];
    int tope_edificios = 0;

    cargar_materiales(materiales, tope_materiales);
    cargar_ciudad(edificios, tope_edificios);

    mostrar_menu();
    opcion = pedir_opcion();
    validar_opcion(opcion);

    while(opcion != GUARDAR_Y_SALIR){
        procesar_opcion(materiales, tope_materiales, edificios, tope_edificios, opcion);

        mostrar_menu();
        opcion = pedir_opcion();
        validar_opcion(opcion);
        
        system(CLR_SCREEN);
    }

    actualizar_datos(materiales, tope_materiales, edificios, tope_edificios);

    return 0;
}