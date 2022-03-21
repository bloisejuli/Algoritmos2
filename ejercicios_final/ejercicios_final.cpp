///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// USOS DE LISTAS
// Ejercicio 1

//Considerar como implementada la clase Alimento a partir de la siguiente interfaz:
class Alimento {
public:
    // Crea un alimento con su nombre, la cantidad de calorías y una lista
    // de los ingredientes que lo conforman
    Alimento (string nombre, unsigned int calorias, Lista<string>* ingredientes);

    // devuelve el nombre del alimento
    string obtener_nombre(); 

    // devuelve la cantidad de calorías
    unsigned int obtener_calorias (); 
    
    // devuelve un ptr la lista de ingredientes
    Lista<string>* obtener_ingredientes (); 
};

//Implementar el método comidas_para_celiacos de la clase Buscador_de_comidas:
class Buscador_de_comidas {
public:
    // Post: busca en “comidas” aquellas que tienen algún ingrediente de la
    // lista “ingredientes_permitidos” y ninguno de la lista “ingredientes_no_permitidos”
    // y tienen una caloría menor a “caloría_maxima”.
    // Devuelve una lista con los alimentos que cumplen con estas características.
    Lista<Alimento *>* comidas_para_celiacos (Lista<Alimento *>* comidas, Lista<string>* ingredientes_permitidos, 
                                              Lista<string>* ingredientes_no_permitidos, unsigned int caloria_maxima);
};

bool Buscador_de_comidas::tiene_ingredientes_aptos(Lista<string>* ingredientes, Lista<string>* ingredientes_permitidos, Lista<string>* ingredientes_no_permitidos) {
    bool tinene_ingredientes_no_aptos = false;
    bool cumple_con_ingredientes = false;

    while(!tinene_ingredientes_no_aptos && !cumple_con_ingredientes && ingredientes->hay_siguiente()) {
        string ingrediente_buscado = ingredientes->siguiente();

        ingredientes_no_permitidos->reiniciar();

        while(!tinene_ingredientes_no_aptos && ingredientes_no_permitidos->hay_siguiente()) {
            if(ingrediente_buscado == ingredientes_no_permitidos->siguiente())
                tinene_ingredientes_no_aptos = true;
        }

        ingredientes_permitidos->reiniciar();

        while(!tinene_ingredientes_no_aptos && !cumple_con_ingredientes && ingredientes_permitidos->hay_siguiente()) {
            if(ingrediente_buscado == ingredientes_permitidos->siguiente())
                cumple_con_ingredientes = true;
        }        
    }

    return(!tinene_ingredientes_no_aptos && cumple_con_ingredientes);
}


Lista<Alimento *>* Buscador_de_comidas::comidas_para_celiacos (Lista<Alimento *>* comidas, Lista<string>* ingredientes_permitidos, 
                                              Lista<string>* ingredientes_no_permitidos, unsigned int caloria_maxima) {
    
    Lista <Alimento *>* comidas_celiacos = new Lista<Alimento*>();

    comidas->reiniciar();
    while(comidas->hay_siguiente()) {
        Alimento* alimento_celiaco = comidas->siguiente();
        
        if(alimento_celiaco->obtener_calorias() < caloria_maxima) {
            Lista<string>* ingredientes = alimento_celiaco->obtener_ingredientes();

            if(tiene_ingredientes_aptos(ingredientes, ingredientes_permitidos, ingredientes_no_permitidos))
                comidas_celiacos->insertar(alimento_celiaco, 1);
        }
    
    }

    return comida_celiacos;
}
 


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ejercicio 2

//Dada la clase implementada segun la interfaz:
class Universidad {
public:
    // Crea una universidad con su nombre, el ranking y una lista de carreras
    Universidad (string nombre, int ranking, Lista<string>* carreras);

    // devuelve el nombre de la universidad
    string obtener_nombre(); 

    // devuelve el ranking
    unsigned int obtener_ranking ();

    // devuelve ptr a lista de carreras
    Lista<string>* obtener_carreras (); 
};

//Implementar el método recomendar_universidades de la clase Buscador_universidades:
class Buscador_universidades {
public:
    // Post: busca en “universidades” aquellas que tienen alguna carrera de la
    // lista “vocaciones” y un ranking mayor o igual a ranking_minimo.
    // Devuelve una lista con las universidades que cumplen con estas características.
    Lista<Universidad *>* recomendar_universidades (Lista<Universidad *>* universidades, Lista<string>* vocaciones, int ranking_minimo);
};

bool Buscador_universidades::tiene_vocaciones(Lista<string>* carreras, Lista<string>* vocaciones) {
    bool carrera_encontrada = false;

    while(!carrera_encontrada && carreras->hay_siguiente()) {
        string carrera_buscada = carreras->siguiente();

        vocaciones->reiniciar();

        while(!carrera_encontrada && vocaciones->hay_siguiente()){
            if(carrera_buscada == vocaciones->siguiente())
                carrera_encontrada = true;
        }
    }
    return carrera_encontrada;
}

Lista<Universidad *>* Buscador_universidades::recomendar_universidades(Lista<Universidad *>* universidades, Lista<string>* vocaciones, int ranking_minimo) {
    Lista<Universidad *>* universidades_recomendadas = new Lista<Universidad*>();

    universidades->reiniciar();
    while(universidades->hay_siguiente()) {
        Universidad* universidad = universidades->siguiente();

        if(universidad->obtener_ranking() >= ranking_minimo) {
            Lista<string>* carreras = universidad->obtener_carreras();

            if(tiene_vocaciones(carreras, vocaciones))
                insertar(universidad, 1);
        }        
    }
    return universidades_recomendadas;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ejercicio 3

//Dada la clase implementada segun la interfaz:
class Restaurante {
public:
    // Crea un restaurante con su nombre, el precio promedio por cubierto y
    // una lista de platos que sirve
    Restaurante (string nombre, int precio_promedio, Lista<string>* platos);

    // devuelve el nombre del restaurante
    string obtener_nombre(); 

    // devuelve el precio promedio
    int obtener_precio_promedio ();

    // devuelve ptr a la lista de platos 
    Lista<string>* obtener_platos (); 
};

//Implementar el metodo recomendar_restaurantes de la clase Buscador_restaurantes:
class Buscador_restaurantes {
public:
    // Post: busca en “restaurantes” aquellos que tienen por lo menos dos platos de la
    // lista “platos_deseados” y un precio promedio menor o igual a precio_maximo.
    // Devuelve una lista con los restaurantes que cumplen con estas características.
    Lista<Restaurante *>* recomendar_restaurantes (Lista<Restaurante *>* restaurantes, Lista<string>* platos_deseados, int precio_maximo);
};

bool Buscador_restaurantes::hay_platos_deseados(Lista<string>* platos, Lista<string>* platos_deseados) {
    int cant_platos_deseados = 0;

    while(cant_platos_desados < 2 && platos->hay_siguiente()) {
        string plato_buscado = platos->siguiente();
        bool plato_encontrado = false;

        platos_deseados->reiniciar();

        while(!plato_encontrado && cant_platos_desados < 2 && platos_deseados->hay_siguiente()) {
            if(plato_buscado == platos_deseados->siguiente()) {
                cant_platos_desados++;
                plato_encontrado = true;
            }
        }
    }

    return (cant_platos_desados >= 2)
}

Lista<Restaurante *>* Buscador_restaurantes::recomendar_restaurantes (Lista<Restaurante *>* restaurantes, Lista<string>* platos_deseados, int precio_maximo) {
    Lista<Restaurante *>* retaurantes_recomendados = new Lista<Restaurante*>();

    while(restaurantes->hay_siguiente()) {
        Restaurante* retaurant = restaurantes->siguiente();

        if(restaurant->obtener_precio_promedio() <= precio_maximo) {
            Lista<string>* platos = restaurant->obtener_platos();

            if(hay_platos_deseados(platos, platos_deseados))
                retaurantes_recomendados->insertar(restaurant, 1);
        }
    }
    return retaurantes_recomendados;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  EJERCICIOS DE FINAL

//La clase Lista tiene implementados los metodos que figuran en el archivo lista_con_actual.h que incluye nodo.h (notar que, con respecto al ej. 1, se le agrega un atributo (actual) y tres metodos).
//Considerar como implementada la clase Carrera a partir de la siguiente interfaz:

class Carrera {
public:

    /* Crea una Carrera con su nombre, cantidad de horas totales y una lista de materias */
    Carrera (string nombre, int horas_totales, Lista<string>* materias);

    /* devuelve el nombre de la Carrera */
    string obtener_nombre(); 

    /* devuelve las horas que insume la Carrera */
    unsigned int obtener_horas_totales (); 

    /* devuelve un ptr a lista de materias */
    Lista<string>* obtener_materias (); 

};


//Implementar el método recomendar_carreras de la clase Buscador_carreras, según:

class Buscador_carreras {
public:

/* 
    Post: busca en “carreras” aquellas que tienen por lo menos cinco materias de la lista “pretendidas” 
          y una cantidad de horas menor o igual a horas_maxima.
          Devuelve un puntero a una lista con las carreras que cumplen con estas características.
*/
    Lista<Carrera *>* recomendar_carreras (Lista<Carrera *>* carreras, Lista<string>* pretendidas, int horas_maxima);
};

bool Buscador_carreras::hay_pretendidas(Lista<string>* materias, Lista<string>* pretendidas) {
    int cantidad_materias = 0;

    while(cantidad_materias < 5 && materias->hay_siguiente()) {
        string materia_buscada = materias->siguiente();
        bool materia_encontrada = false;

        pretendidas->reiniciar();

        while(!materia_encontrada && cantidad_materias < 5 && pretendidas->hay_siguiente()) {
            if(materia_buscada == pretendidas->siguiente()) {
                cantidad_materias++;
                materia_encontrada = true;
            }
        }
    }

    return (cantidad_materias >= 5);
}

Lista<Carrera *>* Buscador_carreras::recomendar_carreras (Lista<Carrera *>* carreras, Lista<string>* pretendidas, int horas_maxima) {
    Lista<Carrera *>* carreras_recomendadas = new Lista<Carrera*>();

    carreras->reiniciar();

    while(carreras->hay_siguiente()) {
        Carrera* nueva_carrera = carreras->siguiente();

        if (nueva_carrera->obtener_horas_totales() <= horas_maxima) {
            Lista<string>* materias = nueva_carrera->obtener_materias();

            if(hay_pretendidas(materias, pretendidas)) 
                carreraras_recomendadas->insertar(nueva_carrera, 1);
            
        }
    }
    return carreras_recomendadas;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Class Club:
    public:
        /*Crea un Club con su nombre, precio de cuota y una lista de actividades*/
        Club(string nombre, int precio_cuota, Lista<string>* actividades);

        /*devuelve el nombre del Club*/
        string obtener_nombre();

        /*devuelve el precio de la cuota*/
        int obtener_precio_cuota();

        /*devuelve un ptr a lista de actividades*/
        Lista<string>* obtener_actividades();
}

Class Buscador_clubes {
    public:
        /*
        * Busca en "clubes" aquellos que tienen por lo menos tres actividades de la lista
        * "actividades_deseadas" y una cuota mensual menor o igual a cuota máxima.
        * Devuelve un puntero a una lista con los clubes que cumplen con estas caracteristicas.
        */
        Lista<Club*>* recomendar_clubes(Lista<Club*>* clubes, Lista<string>* actividades_deseadas, int cuota_maxima);
     
}

bool Buscador_clubes::tiene_actividades_deseadas(Lista<string>* actividades, Lista<string>* actividades_deseadas) {
    int cantidad_actividades = 0;

    while(cantidad_actividades < 3 && actividades->hay_siguiente()) {
        string actividad_buscada = actividades->siguiente();
        bool actividad_encontrada = false;

        actividades_deseadas->reiniciar(),

        while(!actividad_encontrada && cantidad_actividades < 3 && actividades_deseadas->hay_siguiente()) {
            if(actividad_buscada == actividades_deseadas->siguiente()) {
                cantidad_actividades++;
                actividad_encontrada = true;
            }
        }
    }
    return (cantidad_actividades >= 2)
}

Lista<Club*>* Buscador_clubes::recomendar_clubes(Lista<Club*>* clubes, Lista<string>* actividades_deseadas, int cuota_maxima){
    Lista<Club*>* clubes_recomendados = new Lista<Clubes*>();

    clubes->reiniciar();

    while(clubes->hay_siguiente()) {
        Club club = clubes->siguiente();

        if(club->obtener_precio_cuota() <= cuota_maxima) {
            Lista<string>* actividades = club->obtener_actividades();

            if(tiene_actividades_deseadas(actividades, actividades_deseadas))
                insertar(club, 1);
        }
    }
    return clubes_recomendados;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Class Pelicula {
    Public:
        /* Crea una Pelicula con su nombre, puntaje y una lista de actores*/
        Pelicula(string nombre, int puntaje, List<string>* actores);

        /*devuelve el nombre de la pelicula*/
        string obtener_nombre();

        /*devuelve el puntaje*/
        int obtener_puntaje();

        /*devuelve un ptr a lista de actores*/
        Lista<string>* obtener_actores();
}


Class Servicio_streaming {
    public:

    /*
    Post: busca en "peliculas_ofrecidas" aquellas que tienen por lo menos un actor de la lista "peliculas_vistas"
    y un puntaje mayor o igual a puntaje_minimo.
    Devuelve un puntero a una lista con las películas que cumplen con estas caracteristicas.
    */
    Lista<Pelicula*>* recomendar_peliculas(Lista<Pelicula*>* peliculas_ofrecidas, Lista<Pelicula*>* peliculas_vistas, int puntaje_minimo);
}

bool Servicio_streaming::tiene_actor((Lista<string>* actores, (Lista<Pelicula*>* peliculas_vistas) {
    bool actor_encontrado = false;

    while(!actor_encontrado && actores->hay_siguiente()) {
        string actor_buscado = actores->siguiente();

        peliculas_vistas->reiniciar();

        while(!actor_encontrado && peliculas_vistas->hay_siguiente()) {
            Pelicula pelicula_vista = peliculas_vistas->siguiente();    
            Lista<string>* actores_favoritos = pelicula_vista->obtener_actores(); 

            while(!actor_encontrado && actores_favoritos->hay_siguiente()) {
                if(actor_buscado == actores_favoritos->siguiente())
                    actor_encontrado = true;
            }
        }
    }
    return actor_encontrado;
}

Lista<Pelicula*>* Servicio_streaming::recomendar_peliculas(Lista<Pelicula*>* peliculas_ofrecidas, Lista<Pelicula*>* peliculas_vistas, int puntaje_minimo){
    Lista<Pelicula*>* peliculas_recomendadas = new Lista<Peliculas*>();

    peliculas_ofrecidas->reiniciar();

    while(peliculas_ofrecidas->hay_siguiente()) {
        Pelicula pelicula = peliculas_ofrecidas->siguiente();

        if(pelicula->obtener_puntaje() >= puntaje_minimo){
            Lista<string>* actores = pelicula->obtener_actores();

            if(tiene_actor(actores, peliculas_vistas)) 
                peliculas_recomendadas->insertar(pelicula, 1);
        }
    }
}