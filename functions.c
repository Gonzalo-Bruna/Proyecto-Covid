#include "functions.h"

char * _strdup (const char *s) {
    size_t len = strlen (s) + 1;
    void *new = malloc (len);

    if (new == NULL)
    	return NULL;

    return (char *) memcpy (new, s, len);
}

const char *get_csv_field (char * tmp, int i) {
    //se crea una copia del string tmp
    char * line = _strdup (tmp);
    const char * tok;
    for (tok = strtok (line, ","); tok && *tok; tok = strtok (NULL, ",\n")) {
        if (!--i) {
            return tok;
        }
    }
    return NULL;
}

void mostrarLetraPorLetra(char * texto){

    int i;
    size_t len = strlen(texto);

    for(i = 0 ; i < len ; i++){

        Sleep(18);
        printf("%c", texto[i]);

    }

}

void mostrarAccionPelea(char * texto){

    clrscr();
    printf("\n\n\n\n\n\n\n                                     ");
    mostrarLetraPorLetra(texto);
    Sleep(700);

}

void mostrarHistoria (int primeraLinea, int ultimaLinea){

    FILE * fp = fopen("prueba.txt", "r");

    clrscr();
    int i;
    size_t len;
    int leidas=0;
    int n;
    char linea[512];
    char key;

    while(fgets(linea, 511, fp) != NULL){

        leidas++;

        if (leidas >= primeraLinea){

            len = strlen(linea);

            for(n = 0 ; n < 5 ; n++){

                if(linea[n] == '/') break;

            }

            for(i = n + 1 ; i < len ; i++){

                if(kbhit()){

                    key = getch();

                    if(key == 32){

                        for(i; i < len ; i++){

                            printf("%c", linea[i]);

                        }

                    }
                    else{
                        Sleep(16);
                        printf("%c", linea[i]);
                        if(linea[i] == ',') Sleep(350);
                        else if(linea[i] == '.') Sleep(450);
                    }

                }
                else{

                    Sleep(16);
                    printf("%c", linea[i]);
                    if(linea[i] == ',') Sleep(350);
                    else if(linea[i] == '.') Sleep(400);

                }

            }

        Sleep(450);

        }

        if (leidas == ultimaLinea) break;

    }

}

void mostrarHistoriaSinPausas (int primeraLinea, int ultimaLinea){

    FILE * fp = fopen("pruebaNoNumbers.txt", "r");
    int leidas=0;
    int n, i;
    size_t len;
    char linea[512];

    while(fgets(linea, 511, fp) != NULL){
        leidas++;
        if (leidas >= primeraLinea){

             len = strlen(linea);

            printf("%s", linea);

        }

        if (leidas == ultimaLinea) break;

    }

    fclose(fp);
}

void guardarPersonaje(Personaje * personaje){

    FILE * estadisticas = fopen("estadisticas.csv", "w");
    fprintf(estadisticas,"%s,", personaje->nombre);
    fprintf(estadisticas,"%d,", personaje->fuerza);
    fprintf(estadisticas,"%d,", personaje->agilidad);
    fprintf(estadisticas,"%d,", personaje->vitalidad);
    fprintf(estadisticas,"%d,", personaje->inteligencia);
    fprintf(estadisticas,"%d,", personaje->nivel);
    fprintf(estadisticas,"%d,", personaje->puntosDeHabilidad);
    fprintf(estadisticas,"%.1f,", personaje->ataqueFisico);
    fprintf(estadisticas,"%.1f,", personaje->ataqueDistancia);
    fprintf(estadisticas,"%.1f,", personaje->ataqueCriticoDistancia);
    fprintf(estadisticas,"%.1f,", personaje->ataqueCriticoCuerpo);
    fprintf(estadisticas,"%.1f,", personaje->vidaMaxima);
    fprintf(estadisticas,"%.1f,", personaje->vidaActual);
    fprintf(estadisticas,"%.1f,", personaje->ataqueMagico);
    fprintf(estadisticas,"%.1f,", personaje->puntosDefensa);
    fprintf(estadisticas,"%d,", personaje->exp);
    fprintf(estadisticas,"%d,", personaje->expMaxima);
    fprintf(estadisticas,"%d", personaje->oro);

    FILE * inventario = fopen("inventario.csv", "w");
    if(inventario == NULL) return;

    int i;
    int cont = 0;
    for (i = 0 ; i < 6 ; i++){

        if(personaje->inventario[i]){

            if (cont > 0) fprintf(inventario,"\n");

            fprintf(inventario, "%s,%s", personaje->inventario[i]->nombre, personaje->inventario[i]->tipo, personaje->inventario[i]->nombre);

            if(personaje->inventario[i]->equipado == false){

                fprintf(inventario, ",%d", 0);

            }
            else{

                fprintf(inventario, ",%d", 1);

            }

            cont++;

        }

    }

}

Personaje * cargarPersonaje(Personaje * personaje, HashTable * armas, HashTable * armaduras, HashTable * pociones){

    FILE * estadisticas = fopen("estadisticas.csv", "r");
    FILE * inventario = fopen("inventario.csv", "r");

    char linea[256];
    int i = 0;

    personaje = (Personaje *) malloc (sizeof(Personaje));

    fgets(linea, 255, estadisticas);

    char * nombrePersonaje = get_csv_field(linea, 1);

    strcpy(personaje->nombre, nombrePersonaje);
    personaje->fuerza = atoi(get_csv_field(linea, 2));
    personaje->agilidad = atoi(get_csv_field(linea, 3));
    personaje->vitalidad = atoi(get_csv_field(linea, 4));
    personaje->inteligencia = atoi(get_csv_field(linea, 5));
    personaje->nivel = atoi(get_csv_field(linea, 6));
    personaje->puntosDeHabilidad = atoi(get_csv_field(linea, 7));
    personaje->ataqueFisico = atof(get_csv_field(linea, 8));
    personaje->ataqueDistancia = atof(get_csv_field(linea, 9));
    personaje->ataqueCriticoDistancia = atof(get_csv_field(linea, 10));
    personaje->ataqueCriticoCuerpo = atof(get_csv_field(linea, 11));
    personaje->vidaMaxima = atof(get_csv_field(linea, 12));
    personaje->vidaActual = atof(get_csv_field(linea, 13));
    personaje->ataqueMagico = atof(get_csv_field(linea, 14));
    personaje->puntosDefensa = atof(get_csv_field(linea, 15));
    personaje->exp = atoi(get_csv_field(linea, 16));
    personaje->expMaxima = atoi(get_csv_field(linea, 17));
    personaje->oro = atoi(get_csv_field(linea, 18));

    personaje->inventario = (Item **) calloc (6, sizeof(Item *));

    while(fgets(linea, 255, inventario) != NULL){

        Item * item;

        char * nombre = get_csv_field(linea, 1);
        char * tipo = get_csv_field(linea, 2);
        bool equipado = atoi(get_csv_field(linea, 3));

        if(strcmp(tipo, "Arma") == 0){

            item = crearItem(armas, nombre, 1);
            if(equipado == true) item->equipado = true;

        }
        else if(strcmp(tipo, "Armadura") == 0){

            item = crearItem(armaduras, nombre, 2);
            if(equipado == true) item->equipado = true;

        }
        else item = crearItem(pociones, nombre, 3);

        personaje->inventario[i] = item;
        i++;

    }

    fclose(estadisticas);
    fclose(inventario);

    return personaje;

}

void cargarArmas(HashTable * armas){

    FILE * fp = fopen("armas.csv", "r");
    if(fp == NULL) return;
    char linea[128];

    while(fgets(linea, 127, fp) != NULL){

        Arma * nueva = (Arma *) malloc (sizeof(Arma));

        nueva->nombre = get_csv_field(linea, 1);
        nueva->ataqueFisico = atof(get_csv_field(linea, 2));
        nueva->ataqueDistancia = atof(get_csv_field(linea, 3));
        nueva->ataqueCriticoDistancia = atof(get_csv_field(linea, 4));
        nueva->ataqueCriticoCuerpo = atof(get_csv_field(linea, 5));
        nueva->ataqueMagico = atof(get_csv_field(linea, 6));

        nueva->requisitoMinimoFuerza = atoi(get_csv_field(linea, 7));
        nueva->requisitoMinimoAgilidad = atoi(get_csv_field(linea, 8));
        nueva->requisitoMinimoVitalidad = atoi(get_csv_field(linea, 9));
        nueva->requisitoMinimoInteligencia = atoi(get_csv_field(linea, 10));

        insertHashTable(armas, nueva->nombre, nueva);
    }

}

void cargarArmaduras(HashTable * armaduras){

    FILE * fp = fopen("armaduras.csv", "r");
    if(fp == NULL) return;
    char linea[128];

    while(fgets(linea, 127, fp) != NULL){

        Armadura * nueva = (Armadura *) malloc (sizeof(Armadura));

        nueva->nombre = get_csv_field(linea, 1);
        nueva->puntosDefensa = atof(get_csv_field(linea, 2));
        nueva->requisitoMinimoFuerza = atoi(get_csv_field(linea, 3));
        nueva->requisitoMinimoAgilidad = atoi(get_csv_field(linea, 4));
        nueva->requisitoMinimoVitalidad = atoi(get_csv_field(linea, 5));
        nueva->requisitoMinimoInteligencia = atoi(get_csv_field(linea, 6));

        insertHashTable(armaduras, nueva->nombre, nueva);
    }

}

void cargarPociones(HashTable * pociones){

    FILE * fp = fopen("pociones.csv", "r");
    if(fp == NULL) return;
    char linea[128];

    while(fgets(linea, 127, fp) != NULL){

        Pocion * nueva = (Pocion *) malloc (sizeof(Pocion));

        nueva->nombre = get_csv_field(linea, 1);
        nueva->puntosDeVida = atof(get_csv_field(linea, 2));

        insertHashTable(pociones, nueva->nombre, nueva);
    }

}

void cargarEnemigos(HashTable * enemigos){

    FILE * fp = fopen("enemigos.csv", "r");
    if(fp == NULL) return;
    char linea[128];

    while(fgets(linea, 127, fp) != NULL){

        Enemigo * nuevo = (Enemigo *) malloc (sizeof(Enemigo));

        nuevo->nombre = get_csv_field(linea, 1);
        nuevo->ataque = atof(get_csv_field(linea, 2));
        nuevo->ataqueCritico = atof(get_csv_field(linea, 3));

        nuevo->vidaMaxima = atof(get_csv_field(linea, 4));
        nuevo->vidaActual = atof(get_csv_field(linea, 4));
        nuevo->puntosDefensa = atof(get_csv_field(linea, 5));
        nuevo->resistenciaMagica = atof(get_csv_field(linea, 6));

        insertHashTable(enemigos, nuevo->nombre, nuevo);
    }

}

Personaje * crearPersonaje(char nombre[]){

    Personaje * personaje = (Personaje *) malloc (sizeof(Personaje));
    strcpy(personaje->nombre, nombre);

    personaje->nivel = 0;
    personaje->puntosDeHabilidad = 0;

    personaje->fuerza = 1;
    personaje->agilidad = 1;
    personaje->vitalidad = 1;
    personaje->inteligencia = 1;

    personaje->ataqueFisico = 1.5;
    personaje->ataqueDistancia = 1;
    personaje->ataqueCriticoDistancia = 1;
    personaje->ataqueCriticoCuerpo = 2;
    personaje->vidaMaxima = 6;
    personaje->vidaActual = 6;
    personaje->ataqueMagico = 2;

    personaje->puntosDefensa = 0;

    personaje->exp = 0;
    personaje->expMaxima = 500;
    personaje->oro = 0;

    personaje->inventario = (Item **) calloc (6, sizeof(Item *));

    return personaje;

}

Item * crearItem(HashTable * items, char * nombre, int opcion){

    Item * item = (Item *) malloc (sizeof(Item));

    if(opcion == 1){

        Arma * arma = searchHashTable(items, nombre);

        if(arma == NULL) return NULL;

        item->tipo = "Arma";
        item->nombre = arma->nombre;
        item->arma = arma;

        item->armadura = NULL;
        item->pocion = NULL;

    }
    else if(opcion == 2){

        Armadura * armadura = searchHashTable(items, nombre);

        if(armadura == NULL) return NULL;

        item->tipo = "Armadura";
        item->nombre = armadura->nombre;
        item->armadura = armadura;

        item->arma = NULL;
        item->pocion = NULL;


    }
    else if(opcion == 3){

        Pocion * pocion = searchHashTable(items, nombre);

        if(pocion == NULL) return NULL;

        item->tipo = "Pocion";
        item->nombre = pocion->nombre;
        item->pocion = pocion;

        item->arma = NULL;
        item->armadura = NULL;

    }

    item->equipado = false;
    item->comprado = false;
    item->precio = 0;
    return item;

}

void subirNivel(Personaje * personaje){

     clrscr();

    int expMaximaAntigua = personaje->expMaxima;
    int puntosHabilidadAntiguos = personaje->puntosDeHabilidad;

    if (personaje->exp > personaje->expMaxima){

        personaje->exp = personaje->exp - personaje->expMaxima;

    }
    else{

        personaje->exp = 0;

    }

    personaje->expMaxima = personaje->expMaxima * 1.2;

    personaje->nivel++;
    personaje->puntosDeHabilidad = personaje->puntosDeHabilidad + 5;

    char * texto = "Felicidades, has subido de nivel!";
    mostrarLetraPorLetra(texto);

    Sleep(800);

    printf("\n\n    Tu nuevo nivel: %d\n", personaje->nivel);
    printf("    Tu nueva experiencia: %d\n", personaje->exp);
    printf("    Exp para subir al siguiente nivel: %d -> %d\n", expMaximaAntigua, personaje->expMaxima);
    printf("    Puntos de habilidad: %d -> %d\n", puntosHabilidadAntiguos, personaje->puntosDeHabilidad);
    printf("    Puedes utilizar los puntos de habilidad en el menu de estadisticas presionando la letra e al tomar una decision.\n\n");
    system("pause");

}

void equiparArma(Item * item, Personaje * personaje){

    bool cumpleFuerza = false;
    bool cumpleAgilidad = false;
    bool cumpleVitalidad = false;
    bool cumpleInteligencia = false;

    if( personaje->fuerza >= item->arma->requisitoMinimoFuerza ) cumpleFuerza = true;

    if ( personaje->agilidad >= item->arma->requisitoMinimoAgilidad ) cumpleAgilidad = true;

    if( personaje->vitalidad >= item->arma->requisitoMinimoVitalidad ) cumpleVitalidad = true;

    if( personaje->inteligencia >= item->arma->requisitoMinimoInteligencia ) cumpleInteligencia = true;

    if( cumpleFuerza == false ){
        printf("\nTe faltan %d puntos de fuerza para poder equipar esta arma", item->arma->requisitoMinimoFuerza - personaje->fuerza);
    }

    if ( cumpleAgilidad == false ){
        printf("\nTe faltan %d puntos de agilidad para poder equipar esta arma", item->arma->requisitoMinimoAgilidad - personaje->agilidad);
    }

    if( cumpleVitalidad == false ){
        printf("\nTe faltan %d puntos de vitalidad para poder equipar esta arma", item->arma->requisitoMinimoVitalidad - personaje->vitalidad);
    }

    if( cumpleInteligencia == false){
        printf("\nTe faltan %d puntos de inteligencia para poder equipar esta arma", item->arma->requisitoMinimoInteligencia - personaje->inteligencia);
    }

    if( cumpleFuerza && cumpleAgilidad && cumpleVitalidad && cumpleInteligencia ){

        item->equipado = true;

        personaje->ataqueFisico = personaje->ataqueFisico + item->arma->ataqueFisico;
        personaje->ataqueDistancia = personaje->ataqueDistancia + item->arma->ataqueDistancia;
        personaje->ataqueCriticoDistancia = personaje->ataqueCriticoDistancia + item->arma->ataqueCriticoDistancia;
        personaje->ataqueCriticoCuerpo = personaje->ataqueCriticoCuerpo + item->arma->ataqueCriticoCuerpo;
        personaje->ataqueMagico = personaje->ataqueMagico + item->arma->ataqueMagico;

        printf("\nEl arma \"%s\" ha sido equipada correctamente.", item->arma->nombre);

    }

}

void desequiparArma(Item * item, Personaje * personaje){

    item->equipado = false;

    personaje->ataqueFisico = personaje->ataqueFisico - item->arma->ataqueFisico;
    personaje->ataqueDistancia = personaje->ataqueDistancia - item->arma->ataqueDistancia;
    personaje->ataqueCriticoDistancia = personaje->ataqueCriticoDistancia - item->arma->ataqueCriticoDistancia;
    personaje->ataqueCriticoCuerpo = personaje->ataqueCriticoCuerpo - item->arma->ataqueCriticoCuerpo;
    personaje->ataqueMagico = personaje->ataqueMagico - item->arma->ataqueMagico;

    printf("\nEl arma \"%s\" ha sido desequipada correctamente.", item->arma->nombre);

}

void equiparArmadura(Item * item, Personaje * personaje){

    bool cumpleFuerza = false;
    bool cumpleAgilidad = false;
    bool cumpleVitalidad = false;
    bool cumpleInteligencia = false;

    if( personaje->fuerza >= item->armadura->requisitoMinimoFuerza ) cumpleFuerza = true;

    if ( personaje->agilidad >= item->armadura->requisitoMinimoAgilidad ) cumpleAgilidad = true;

    if( personaje->vitalidad >= item->armadura->requisitoMinimoVitalidad ) cumpleVitalidad = true;

    if( personaje->inteligencia >= item->armadura->requisitoMinimoInteligencia ) cumpleInteligencia = true;

    if( cumpleFuerza == false ){
        printf("\nTe faltan %d puntos de fuerza para poder equipar esta armadura", item->armadura->requisitoMinimoFuerza - personaje->fuerza);
    }

    if ( cumpleAgilidad == false ){
        printf("\nTe faltan %d puntos de agilidad para poder equipar esta armadura", item->armadura->requisitoMinimoAgilidad - personaje->agilidad);
    }

    if( cumpleVitalidad == false ){
        printf("\nTe faltan %d puntos de vitalidad para poder equipar esta armadura", item->armadura->requisitoMinimoVitalidad - personaje->vitalidad);
    }

    if( cumpleInteligencia == false){
        printf("\nTe faltan %d puntos de inteligencia para poder equipar esta armadura", item->armadura->requisitoMinimoInteligencia - personaje->inteligencia);
    }

    if( cumpleFuerza && cumpleAgilidad && cumpleVitalidad && cumpleInteligencia ){

        item->equipado = true;

        personaje->puntosDefensa = personaje->puntosDefensa + item->armadura->puntosDefensa;

        printf("\nLa armadura \"%s\" ha sido equipada correctamente.", item->armadura->nombre);

    }

}

void desequiparArmadura(Item * item, Personaje * personaje){

    item->equipado = false;

    personaje->puntosDefensa = personaje->puntosDefensa - item->armadura->puntosDefensa;

    printf("\nLa armadura \"%s\" ha sido desequipada correctamente.", item->armadura->nombre);

}

void mostrarObjeto(Item * item, int n){

    if (strcmp(item->tipo, "Arma") == 0){

        if (n == 1) printf("->  %s\n", item->arma->nombre);
        else printf("    %s\n", item->arma->nombre);

        printf("        Stats: \n");

        if(item->arma->ataqueFisico != 0){

            if(item->arma->ataqueFisico > 0) printf("        Ataque Fisico: +%.1f\n", item->arma->ataqueFisico);
            else printf("        Ataque Fisico: %.1f\n", item->arma->ataqueFisico);

        }
        if(item->arma->ataqueDistancia != 0){

            if(item->arma->ataqueDistancia > 0) printf("        Ataque Distancia: +%.1f\n", item->arma->ataqueDistancia);
            else printf("        Ataque Distancia: %.1f\n", item->arma->ataqueDistancia);

        }
        if(item->arma->ataqueCriticoDistancia != 0){

            if(item->arma->ataqueCriticoDistancia > 0) printf("        Ataque Critico a Distancia: +%.1f%\n", item->arma->ataqueCriticoDistancia);
            else printf("        Ataque Critico a Distancia: : %.1f%\n", item->arma->ataqueCriticoDistancia);

        }
        if(item->arma->ataqueCriticoCuerpo != 0){

            if(item->arma->ataqueCriticoCuerpo > 0) printf("        Ataque Critico a Cuerpo: +%.1f\n", item->arma->ataqueCriticoCuerpo);
            else printf("        Ataque Critico a Cuerpo: %.1f\n", item->arma->ataqueCriticoCuerpo);

        }

        if(item->arma->ataqueMagico != 0){

            if(item->arma->ataqueMagico > 0)  printf("        Ataque Magico: +%.1f\n", item->arma->ataqueMagico);
            else printf("        Ataque Magico: %.1f\n", item->arma->ataqueMagico); //es pal futuro uwu

        }

        if(item->arma->requisitoMinimoFuerza != 0){

            printf("        Requisito minimo de Fuerza: %d\n", item->arma->requisitoMinimoFuerza);

        }
        if(item->arma->requisitoMinimoAgilidad != 0){

            printf("        Requisito minimo de Agilidad: %d\n", item->arma->requisitoMinimoAgilidad);

        }
        if(item->arma->requisitoMinimoVitalidad != 0){

            printf("        Requisito minimo de Vitalidad: %d\n", item->arma->requisitoMinimoVitalidad);

        }
        if(item->arma->requisitoMinimoInteligencia != 0){

            printf("        Requisito minimo de Inteligencia: %d\n", item->arma->requisitoMinimoInteligencia);

        }

    }
    else if(strcmp(item->tipo, "Armadura") == 0){

        if (n == 1) printf("->  %s\n", item->armadura->nombre);
        else printf("    %s\n", item->armadura->nombre);

        printf("        Stats: \n");

        if(item->armadura->puntosDefensa != 0){

            if(item->armadura->puntosDefensa > 0) printf("        Puntos de defensa: +%.1f", item->armadura->puntosDefensa);
            else printf("        Puntos de defensa: %.1f", item->armadura->puntosDefensa);

        }

        printf("\n");

        if(item->armadura->requisitoMinimoFuerza != 0){

            printf("        Requisito minimo de Fuerza: %d\n", item->armadura->requisitoMinimoFuerza);

        }
        if(item->armadura->requisitoMinimoAgilidad != 0){

            printf("        Requisito minimo de Agilidad: %d\n", item->armadura->requisitoMinimoAgilidad);

        }
        if(item->armadura->requisitoMinimoVitalidad != 0){

            printf("        Requisito minimo de Vitalidad: %d\n", item->armadura->requisitoMinimoVitalidad);

        }
        if(item->armadura->requisitoMinimoInteligencia != 0){

            printf("        Requisito minimo de Inteligencia: %d\n", item->armadura->requisitoMinimoInteligencia);

        }

    }
    else{

        printf("->  %s\n", item->pocion->nombre);
        printf("        Stats: \n");

        printf("        Puntos de vida: +%.1f\n", item->pocion->puntosDeVida);

    }

}

void verOpcionesDelObjeto(Item * item, int pos, Personaje * personaje){

    Item ** objetosEquipados = (Item **) calloc (2, sizeof(Item *));
    bool hayArma = false;
    bool hayArmadura = false;
    int i;
    int cont = 0;

    for (i = 0 ; i < 6 ; i++){

        if(personaje->inventario[i] != NULL && personaje->inventario[i]->equipado == true){

            if( strcmp(personaje->inventario[i]->tipo, "Arma") == 0 ) hayArma = true;
            else if( strcmp(personaje->inventario[i]->tipo, "Armadura") == 0 ) hayArmadura = true;

            objetosEquipados[cont] = personaje->inventario[i];
            cont++;

        }

    }

    char key;
    int opcion = 1;

    do{

        clrscr();

        if (strcmp(item->tipo, "Arma") == 0){

            printf("    %s\n", item->arma->nombre);
            printf("    Stats: \n");

            if(item->arma->ataqueFisico != 0){

                if(item->arma->ataqueFisico > 0) printf("        Ataque Fisico: +%.1f\n", item->arma->ataqueFisico);
                else printf("        Ataque Fisico: %.1f\n", item->arma->ataqueFisico);

            }
            if(item->arma->ataqueDistancia != 0){

                if(item->arma->ataqueDistancia > 0) printf("        Ataque Distancia: +%.1f\n", item->arma->ataqueDistancia);
                else printf("        Ataque Distancia: %.1f\n", item->arma->ataqueDistancia);

            }
            if(item->arma->ataqueCriticoDistancia != 0){

                if(item->arma->ataqueCriticoDistancia > 0) printf("        Ataque Critico a Distancia: +%.1f%\n", item->arma->ataqueCriticoDistancia);
                else printf("        Ataque Critico a Distancia: %.1f%\n", item->arma->ataqueCriticoDistancia);

            }
            if(item->arma->ataqueCriticoCuerpo != 0){

                if(item->arma->ataqueCriticoCuerpo > 0) printf("        Ataque Critico a Cuerpo: %.1f\n", item->arma->ataqueCriticoCuerpo);
                else printf("        Ataque Critico a Cuerpo: %.1f\n", item->arma->ataqueCriticoCuerpo);

            }

            if(item->arma->ataqueMagico != 0){

                if(item->arma->ataqueMagico > 0)  printf("        Ataque Magico: %.1f\n", item->arma->ataqueMagico);
                else printf("        Ataque Magico: %.1f\n", item->arma->ataqueMagico);

            }

            if(item->arma->requisitoMinimoFuerza != 0){

                printf("        Requisito minimo de Fuerza: %d\n", item->arma->requisitoMinimoFuerza);

            }
            if(item->arma->requisitoMinimoAgilidad != 0){

                printf("        Requisito minimo de Agilidad: %d\n", item->arma->requisitoMinimoAgilidad);

            }
            if(item->arma->requisitoMinimoVitalidad != 0){

                printf("        Requisito minimo de Vitalidad: %d\n", item->arma->requisitoMinimoVitalidad);

            }
            if(item->arma->requisitoMinimoInteligencia != 0){

                printf("        Requisito minimo de Inteligencia: %d\n", item->arma->requisitoMinimoInteligencia);

            }

        }
        else if(strcmp(item->tipo, "Armadura") == 0){

            printf("    %s\n\n", item->armadura->nombre);
            printf("    Stats: \n");

            if(item->armadura->puntosDefensa != 0){

                if(item->armadura->puntosDefensa > 0) printf("        Puntos de defensa: +%.1f", item->armadura->puntosDefensa);
                else printf("        Puntos de defensa: %.1f", item->armadura->puntosDefensa);

            }

            printf("\n");

            if(item->armadura->requisitoMinimoFuerza != 0){

                printf("        Requisito minimo de Fuerza: %d\n", item->armadura->requisitoMinimoFuerza);

            }
            if(item->armadura->requisitoMinimoAgilidad != 0){

                printf("        Requisito minimo de Agilidad: %d\n", item->armadura->requisitoMinimoAgilidad);

            }
            if(item->armadura->requisitoMinimoVitalidad != 0){

                printf("        Requisito minimo de Vitalidad: %d\n", item->armadura->requisitoMinimoVitalidad);

            }
            if(item->armadura->requisitoMinimoInteligencia != 0){

                printf("        Requisito minimo de Inteligencia: %d\n", item->armadura->requisitoMinimoInteligencia);

            }

        }
        else{

            printf("    %s\n", item->pocion->nombre);
            printf("    Stats: \n");

            printf("        Curacion: +%.1f", item->pocion->puntosDeVida);
            if(personaje->vidaActual == personaje->vidaMaxima){

                printf("\n\n        Tu vida esta completa");
                printf("\n\n        Vida actual: %.1f / %.1f\n", personaje->vidaActual, personaje->vidaMaxima);

            }
            else{

                printf("\n\n        Vida actual: %.1f / %.1f\n", personaje->vidaActual, personaje->vidaMaxima);
                if ( (personaje->vidaActual + item->pocion->puntosDeVida) >= personaje->vidaMaxima ){

                    printf("        Al curarse: %.1f / %.1f", personaje->vidaMaxima, personaje->vidaMaxima);

                }
                else{

                    printf("        Al curarse: %.1f / %.1f", personaje->vidaActual + item->pocion->puntosDeVida, personaje->vidaMaxima);

                }

            }
            printf("\n\n");

        }

        if(opcion == 1){

            if ( strcmp (item->tipo, "Pocion") != 0 ) {

                if(item->equipado == true) printf("->  Desequipar\n");
                else printf("->  Equipar\n");

            }
            else{

                 printf("->  Usar pocion\n");

            }

        }
        else{

            if ( strcmp (item->tipo, "Pocion") != 0 ) {

                if(item->equipado == true) printf("     Desequipar\n");
                else printf("     Equipar\n");

            }
            else{

                 printf("     Usar pocion\n");

            }

        }
        if(opcion == 2) printf("->  Tirar\n");
        else printf("     Tirar\n");
        if(opcion == 3) printf("->  Volver atras\n");
        else printf("     Volver atras\n");

        do{
            key = getch();
        }while(key != 72 && key != 80 && key != 13);

        switch(key){
            case 72: if(opcion == 1) opcion = 3;
                    else opcion--;
                break;
            case 80: if(opcion == 3) opcion = 1;
                    else opcion++;
                break;
        }

        if(key == 13) break;

    }while(1);

    if(opcion == 1){

        if ( strcmp (item->tipo, "Pocion") == 0 ) {

            clrscr();
            printf("\n\n\n\n\n\n");
            if(personaje->vidaActual == personaje->vidaMaxima){

                printf("                         Tu vida ya se encuentra llena");

            }
            else if ( (personaje->vidaActual + item->pocion->puntosDeVida) >= personaje->vidaMaxima ){

                personaje->vidaActual = personaje->vidaMaxima;
                printf("                          Te has curado por completo");
                free(personaje->inventario[pos]);
                personaje->inventario[pos] = NULL;

            }
            else{

                personaje->vidaActual = personaje->vidaActual + item->pocion->puntosDeVida;
                printf("                          Te has curado %.1f puntos de vida", item->pocion->puntosDeVida);
                free(personaje->inventario[pos]);
                personaje->inventario[pos] = NULL;

            }

            printf("\n\n\n\n");

        }
        else{

            if( strcmp(item->tipo, "Arma") == 0 ){

                if( item->equipado == true ){

                    desequiparArma(item, personaje);

                }
                else{

                    if(hayArma == true){

                        //se busca el arma equipada y se quita
                        for (i = 0 ; i < 2 ; i++){

                            if( objetosEquipados[i] != NULL && strcmp(objetosEquipados[i]->tipo, "Arma") == 0 ){

                                desequiparArma(objetosEquipados[i], personaje);
                                break;

                            }

                        }

                        equiparArma(item, personaje);
                        if(item->equipado == false){

                            printf("\nComo no cumple los requisitos para equipar, se volvera a equipar su arma anterior.");
                            equiparArma(objetosEquipados[i], personaje);

                        }

                    }
                    else{

                        equiparArma(item, personaje);

                    }

                }

            }
            else{

                if( item->equipado == true){

                    desequiparArmadura(item, personaje);

                }
                else{

                    if(hayArmadura == true){

                        //se busca el arma equipada y se quita
                        for (i = 0 ; i < 2; i++){

                            if( objetosEquipados[i] != NULL && strcmp(objetosEquipados[i]->tipo, "Armadura") == 0 ){

                                desequiparArmadura(objetosEquipados[i], personaje);
                                break;

                            }

                        }

                        equiparArmadura(item, personaje);
                        if(item->equipado == false){

                            printf("\nComo no cumple los requisitos para equipar, se volvera a equipar su armadura anterior.");
                            equiparArmadura(objetosEquipados[i], personaje);

                        }

                    }
                    else{

                        equiparArmadura(item, personaje);

                    }

                }

            }

        }

    }
    else if(opcion == 2){

        if(item->equipado == true){

            if( strcmp(item->tipo, "Arma") == 0 ){

                desequiparArma(item, personaje);
            }
            else{

                desequiparArmadura(item, personaje);
            }


            printf(" Has tirado el objeto.");

        }
        else{

            printf("\nHas tirado el objeto.");

        }

        free(personaje->inventario[pos]);
        personaje->inventario[pos] = NULL;

    }
    else if (opcion == 3) return;

    printf("\n\n");
    system("pause");
    return;

}

void abrirInventario(Personaje * personaje){

    Item ** objetosEquipados = (Item **) calloc (2, sizeof(Item *));
    int opcion = 1;
    char key;
    bool hayObjetos;
    bool hayArma;
    bool hayArmadura;
    int cont;
    int i;

    do{

        clrscr();

        cont = 0;
        hayObjetos = false;
        hayArma = false;
        hayArmadura = false;

        for (i = 0 ; i < 6 ; i++){

            if(personaje->inventario[i] != NULL && personaje->inventario[i]->equipado == true){

                if( strcmp(personaje->inventario[i]->tipo, "Arma") == 0 ) hayArma = true;
                else if( strcmp(personaje->inventario[i]->tipo, "Armadura") == 0 ) hayArmadura = true;

                objetosEquipados[cont] = personaje->inventario[i];
                cont++;

            }

        }
        if(hayArma || hayArmadura) hayObjetos = true;

        printf("Oro: %d\n\n", personaje->oro);

        printf("Equipo: \n");

        if(hayObjetos == false){

            printf("No hay objetos equipados\n\n");

        }
        else{

            for (i = 0 ; i < cont; i++){

                printf("%s\n", objetosEquipados[i]->nombre);

            }

            printf("\n");

        }

        if(personaje->inventario[0] == NULL){

            if (opcion == 1) printf("->  Vacio\n");
            else printf("    Vacio\n");

        }
        else{

            if(opcion == 1){

                mostrarObjeto(personaje->inventario[0], 1);

            }
            else printf("    %s\n", personaje->inventario[0]->nombre);

        }

        if(personaje->inventario[1] == NULL){

            if (opcion == 2) printf("->  Vacio\n");
            else printf("    Vacio\n");

        }
        else{

            if(opcion == 2){

                mostrarObjeto(personaje->inventario[1], 1);

            }
            else printf("    %s\n", personaje->inventario[1]->nombre);

        }

        if(personaje->inventario[2] == NULL){

            if (opcion == 3) printf("->  Vacio\n");
            else printf("    Vacio\n");

        }
        else{

            if(opcion == 3){

                mostrarObjeto(personaje->inventario[2],1);

            }
            else printf("    %s\n", personaje->inventario[2]->nombre);

        }

        if(personaje->inventario[3] == NULL){

            if (opcion == 4) printf("->  Vacio\n");
            else printf("    Vacio\n");

        }
        else{

            if(opcion == 4){

                mostrarObjeto(personaje->inventario[3],1);
            }
            else printf("    %s\n", personaje->inventario[3]->nombre);

        }

        if(personaje->inventario[4] == NULL){

            if (opcion == 5) printf("->  Vacio\n");
            else printf("    Vacio\n");

        }
        else{

            if(opcion == 5){

                mostrarObjeto(personaje->inventario[4],1);

            }
            else printf("    %s\n", personaje->inventario[4]->nombre);

        }

        if(personaje->inventario[5] == NULL){

            if (opcion == 6) printf("->  Vacio\n");
            else printf("    Vacio\n");

        }
        else{

            if(opcion == 6){

                mostrarObjeto(personaje->inventario[5],1);

            }
            else printf("    %s\n", personaje->inventario[5]->nombre);

        }

        printf("\n\nPresione enter para ver las opciones del objeto.\n");
        printf("Presione i o esc para cerrar el inventario.");

        do{

            key = getch();

        }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 27);

        if(key == 27) return;

        switch(key){
            case 72: if(opcion == 1) opcion = 6;
                    else opcion--;
                break;
            case 80: if(opcion == 6) opcion = 1;
                    else opcion++;
                break;
        }

        if(key == 105 || key == 73) break;

        if(key == 13 && personaje->inventario[opcion - 1]){

            verOpcionesDelObjeto(personaje->inventario[opcion - 1], opcion - 1, personaje);

        }

    }while(1);

    free(objetosEquipados);

}

void abrirEstadisticas(Personaje * personaje){

    int opcion = 1;
    char key;

    do{

        clrscr();
        printf("Estadisticas: \n\n");
        printf("    Nombre: %s                                         Puntos de habilidad: %d\n", personaje->nombre, personaje->puntosDeHabilidad);
        printf("    Vida Actual: %.1f / %.1f\n", personaje->vidaActual, personaje->vidaMaxima);
        printf("    Nivel: %d\n\n", personaje->nivel);

        if(personaje->puntosDeHabilidad == 0){

            if(opcion == 1) printf("    ->  Fuerza: %d\n", personaje->fuerza);
            else printf("         Fuerza: %d\n", personaje->fuerza);
            if(opcion == 2) printf("    ->  Agilidad: %d\n", personaje->agilidad);
            else printf("         Agilidad: %d\n", personaje->agilidad);
            if(opcion == 3) printf("    ->  Vitalidad: %d\n", personaje->vitalidad);
            else printf("         Vitalidad: %d\n", personaje->vitalidad);
            if(opcion == 4) printf("    ->  Inteligencia: %d\n\n", personaje->inteligencia);
            else printf("         Inteligencia: %d\n\n", personaje->inteligencia);

        }
        else{

            if(opcion == 1) printf("    ->  Fuerza: %d          +1\n", personaje->fuerza);
            else printf("         Fuerza: %d\n", personaje->fuerza);
            if(opcion == 2) printf("    ->  Agilidad: %d        +1\n", personaje->agilidad);
            else printf("         Agilidad: %d\n", personaje->agilidad);
            if(opcion == 3) printf("    ->  Vitalidad: %d       +1\n", personaje->vitalidad);
            else printf("         Vitalidad: %d\n", personaje->vitalidad);
            if(opcion == 4) printf("    ->  Inteligencia: %d    +1\n\n", personaje->inteligencia);
            else printf("         Inteligencia: %d\n\n", personaje->inteligencia);

        }

        printf("    Ataque Fisico: %.1f\n", personaje->ataqueFisico);
        printf("    Ataque a Distancia: %.1f\n", personaje->ataqueDistancia);
        printf("    Ataque Magico: %.1f\n", personaje->ataqueMagico);
        printf("    Probabilidad de Critico Cuerpo a Cuerpo: %.1f\n", personaje->ataqueCriticoCuerpo);
        printf("    Probabilidad de Critico a Distancia: %.1f\n", personaje->ataqueCriticoDistancia);
        printf("\nExplicacion de estadisticas: \n");
        printf("\n    La Fuerza aumenta tu ataque fisico");
        printf("\n    La Agilidad aumenta tu ataque a distancia y tu probabilidad de acertar un golpe critico.");
        printf("\n    La Inteligencia aumenta tu ataque magico.");
        printf("\n    La Vitalidad aumenta tu vida maxima.");
        printf("\n    La probabilidad de golpe critico es mayor para el ataque fisico");
        printf("\n    El ataque magico no tiene probabilidad de acertar un golpe critico.\n");
        printf("\nPresione e o esc para cerrar las estadisticas");
        printf("\nPresione enter para aumentar sus estadisticas");

        do{
           key  = getch();
        }while(key != 72 && key != 80 && key != 13 && key != 101 && key != 69 && key != 27);

        if(key == 101 || key == 69 || 27) return;

        switch(key){
            case 72: if(opcion == 1) opcion = 4;
                    else opcion--;
                break;
            case 80: if(opcion == 4) opcion = 1;
                    else opcion++;
                break;
        }

        if(key == 13){

            if(personaje->puntosDeHabilidad == 0){

                clrscr();

                char * texto = "No tienes puntos de habilidad disponibles";
                printf("\n\n\n              ");
                mostrarLetraPorLetra(texto);
                printf("\n\n               ");

                system("pause");

            }
            else{

                if(opcion == 1){

                    personaje->fuerza++;
                    personaje->ataqueFisico += 1.5;
                    personaje->puntosDeHabilidad--;

                }
                else if(opcion == 2){

                    personaje->agilidad++;
                    personaje->ataqueDistancia += 1;
                    personaje->ataqueCriticoCuerpo += 2;
                    personaje->ataqueCriticoDistancia += 1;
                    personaje->puntosDeHabilidad--;

                }
                else if(opcion == 3){

                    personaje->vitalidad++;
                    personaje->vidaMaxima += 6;
                    personaje->vidaActual += 6;
                    personaje->puntosDeHabilidad--;

                }
                else{

                    personaje->inteligencia++;
                    personaje->ataqueMagico += 2;
                    personaje->puntosDeHabilidad--;

                }

            }


        }

    }while(1);

}

void mostrarOpcionesObjetoTienda(Item * item, Personaje * personaje){

    bool hayArma = false;
    bool hayArmadura = false;
    bool esArma = false;
    bool esArmadura = false;
    int i;

    clrscr();

    if (strcmp(item->tipo, "Arma") == 0){

         esArma = true;

         for (i = 0 ; i < 6 ; i++){

            if(personaje->inventario[i] != NULL && personaje->inventario[i]->equipado == true){

                if( strcmp(personaje->inventario[i]->tipo, "Arma") == 0 ){

                    hayArma = true;
                    break;

                }

            }

        }

    }
    else if(strcmp(item->tipo, "Armadura") == 0){

        esArmadura = true;

        for (i = 0 ; i < 6 ; i++){

            if(personaje->inventario[i] != NULL && personaje->inventario[i]->equipado == true){

                if( strcmp(personaje->inventario[i]->tipo, "Armadura") == 0 ){

                    hayArmadura = true;
                    break;

                }

            }

        }

    }

    int opcion = 1;
    char key;

    do{

        clrscr();

        printf("\nStats del objeto:\n\n");
        mostrarObjeto(item, 2);

        if(esArma && hayArma){

            printf("\nTu equipo actual: \n\n");
            mostrarObjeto(personaje->inventario[i], 2);

        }
        else if(esArmadura && hayArmadura){

            printf("\nTu equipo actual: \n\n");
            mostrarObjeto(personaje->inventario[i], 2);

        }

        printf("\n Que desea hacer?\n");

        if(opcion == 1) printf(" -> Comprar\n");
        else printf("     Comprar\n");
        if(opcion == 2) printf(" -> Salir\n");
        else printf("     Salir\n");

        do{
           key  = getch();
        }while(key != 72 && key != 80 && key != 13);

        switch(key){
            case 72: if(opcion == 1) opcion = 2;
                    else opcion--;
                break;
            case 80: if(opcion == 2) opcion = 1;
                    else opcion++;
                break;

        }

        if(key == 13) break;

    }while(1);

    if (opcion == 1){

        if(personaje->oro < item->precio){

            printf("\nNo tienes oro suficiente para comprar este item");

        }
        else{

            for (i = 0 ; i < 6 ; i++){

                if(personaje->inventario[i] == NULL){

                    if(strcmp(item->tipo, "Pocion") != 0) item->comprado = true;
                    personaje->inventario[i] = item;
                    break;

                }

            }

            if(i == 6){

                printf("\nNo tiene espacio en el inventario para comprar este objeto, bote alguno");

            }
            else{

                printf("\nEl objeto ha sido comprado correctamente y agregado a su inventario");
                personaje->oro -= item->precio;

            }

        }

    }
    else return;

    printf("\n\n");
    system("pause");

}

void abrirTienda(Personaje * personaje, char * nombreArchivo, HashTable * armas, HashTable * armaduras, HashTable * pociones){

    Item ** inventarioTienda = (Item **) malloc (12 * sizeof(Item *));

    FILE * fp = fopen(nombreArchivo, "r");
    if (fp == NULL){
        printf("error al abrir el archivo");
        return;
    }

    char linea[128];

    char * nombre;
    int precio;
    char * tipo;
    int cantidadObjetos = 0;

    while(fgets(linea, 127, fp) != NULL){

        nombre = get_csv_field(linea, 1);
        precio = atoi(get_csv_field(linea,2));
        tipo = get_csv_field(linea,3);
        Item * nuevo;
        if(strcmp(tipo, "Arma") == 0) nuevo = crearItem(armas, nombre, 1);
        else if(strcmp(tipo, "Armadura") == 0) nuevo = crearItem(armaduras, nombre, 2);
        else nuevo = crearItem(pociones, nombre, 3);

        if(nuevo == NULL) return;

        nuevo->precio = precio;
        inventarioTienda[cantidadObjetos] = nuevo;
        cantidadObjetos++;

    }

    int opcion = 1;
    char key;

    do{

        clrscr();

        printf("                                                     ~  Tienda  ~\n");
        printf("         ------------------------------------------------------------------------------------------------------\n");
        printf("                                                      [ Oro: %d ]\n\n", personaje->oro);

        if(opcion == 1){

            if (!inventarioTienda[0]->comprado) printf("                 ->  %-25s", inventarioTienda[0]->nombre);
            else printf("                 ->  Comprado                 ");
        }
        else{

            if (!inventarioTienda[0]->comprado) printf("                     %-25s", inventarioTienda[0]->nombre);
            else printf("                     Comprado                 ");
        }

        if(opcion == 2){

            if(!inventarioTienda[1]->comprado) printf(" ->  %-25s", inventarioTienda[1]->nombre);
            else printf(" ->  Comprado                 ");

        }
        else{

            if(!inventarioTienda[1]->comprado) printf("     %-25s", inventarioTienda[1]->nombre);
            else printf("     Comprado                 ");
        }

        if(opcion == 3){

            if(!inventarioTienda[2]->comprado) printf(" ->  %-25s\n", inventarioTienda[2]->nombre);
            else printf(" ->  Comprado                 \n");

        }
        else{

            if(!inventarioTienda[2]->comprado) printf("     %-25s\n", inventarioTienda[2]->nombre);
            else printf("     Comprado                 \n");

        }

        if(!inventarioTienda[0]->comprado) printf("                     [ costo: %4d ]", inventarioTienda[0]->precio);
        else printf("                     [ costo: ---- ]");
        if(!inventarioTienda[1]->comprado) printf("               [  costo: %4d ]", inventarioTienda[1]->precio);
        else printf("               [  costo: ---- ]");
        if (!inventarioTienda[2]->comprado) printf("              [  costo: %4d ]\n\n", inventarioTienda[2]->precio);
        else printf("              [  costo: ---- ]\n\n");


        if(opcion == 4){

            if (!inventarioTienda[3]->comprado) printf("                 ->  %-25s", inventarioTienda[3]->nombre);
            else printf("                 ->  Comprado                 ");
        }
        else{

            if (!inventarioTienda[3]->comprado) printf("                     %-25s", inventarioTienda[3]->nombre);
            else printf("                     Comprado                 ");
        }

        if(opcion == 5){

            if(!inventarioTienda[4]->comprado) printf(" ->  %-25s", inventarioTienda[4]->nombre);
            else printf(" ->  Comprado                 ");

        }
        else{

            if(!inventarioTienda[4]->comprado) printf("     %-25s", inventarioTienda[4]->nombre);
            else printf("     Comprado                 ");
        }

        if(opcion == 6){

            if(!inventarioTienda[5]->comprado) printf(" ->  %-25s\n", inventarioTienda[5]->nombre);
            else printf(" ->  Comprado                 \n");

        }
        else{

            if(!inventarioTienda[5]->comprado) printf("     %-25s\n", inventarioTienda[5]->nombre);
            else printf("     Comprado                 \n");

        }

        if(!inventarioTienda[3]->comprado) printf("                     [ costo: %4d ]", inventarioTienda[3]->precio);
        else printf("                     [ costo: ---- ]");
        if(!inventarioTienda[4]->comprado) printf("               [  costo: %4d ]", inventarioTienda[4]->precio);
        else printf("               [  costo: ---- ]");
        if (!inventarioTienda[5]->comprado) printf("              [  costo: %4d ]\n\n", inventarioTienda[5]->precio);
        else printf("              [  costo: ---- ]\n\n");

        if(opcion == 7){

            if (!inventarioTienda[6]->comprado) printf("                 ->  %-25s", inventarioTienda[6]->nombre);
            else printf("                 ->  Comprado                 ");
        }
        else{

            if (!inventarioTienda[6]->comprado) printf("                     %-25s", inventarioTienda[6]->nombre);
            else printf("                     Comprado                 ");
        }

        if(opcion == 8){

            if(!inventarioTienda[7]->comprado) printf(" ->  %-25s", inventarioTienda[7]->nombre);
            else printf(" ->  Comprado                 ");

        }
        else{

            if(!inventarioTienda[7]->comprado) printf("     %-25s", inventarioTienda[7]->nombre);
            else printf("     Comprado                 ");
        }

        if(opcion == 9){

            if(!inventarioTienda[8]->comprado) printf(" ->  %-25s\n", inventarioTienda[8]->nombre);
            else printf(" ->  Comprado                 \n");

        }
        else{

            if(!inventarioTienda[8]->comprado) printf("     %-25s\n", inventarioTienda[8]->nombre);
            else printf("     Comprado                 \n");

        }

        if(!inventarioTienda[6]->comprado) printf("                     [ costo: %4d ]", inventarioTienda[6]->precio);
        else printf("                     [ costo: ---- ]");
        if(!inventarioTienda[7]->comprado) printf("               [  costo: %4d ]", inventarioTienda[7]->precio);
        else printf("               [  costo: ---- ]");
        if(!inventarioTienda[8]->comprado) printf("              [  costo: %4d ]\n\n", inventarioTienda[8]->precio);
        else printf("              [  costo: ---- ]\n\n");

        if(opcion == 10){

            if (!inventarioTienda[9]->comprado) printf("                 ->  %-25s", inventarioTienda[9]->nombre);
            else printf("                 ->  Comprado                 ");
        }
        else{

            if (!inventarioTienda[9]->comprado) printf("                     %-25s", inventarioTienda[9]->nombre);
            else printf("                     Comprado                 ");
        }

        if(opcion == 11){

            if(!inventarioTienda[10]->comprado) printf(" ->  %-25s", inventarioTienda[10]->nombre);
            else printf(" ->  Comprado                 ");

        }
        else{

            if(!inventarioTienda[10]->comprado) printf("     %-25s", inventarioTienda[10]->nombre);
            else printf("     Comprado                 ");
        }

        if(opcion == 12){

            if(!inventarioTienda[11]->comprado) printf(" ->  %-25s\n", inventarioTienda[11]->nombre);
            else printf(" ->  Comprado                 \n");

        }
        else{

            if(!inventarioTienda[11]->comprado) printf("     %-25s\n", inventarioTienda[11]->nombre);
            else printf("     Comprado                 \n");

        }

        if(!inventarioTienda[9]->comprado) printf("                     [ costo: %4d ]", inventarioTienda[9]->precio);
        else printf("                     [ costo: ---- ]");
        if(!inventarioTienda[10]->comprado) printf("               [  costo: %4d ]", inventarioTienda[10]->precio);
        else printf("               [  costo: ---- ]");
        if (!inventarioTienda[11]->comprado) printf("              [  costo: %4d ]\n\n", inventarioTienda[11]->precio);
        else printf("              [  costo: ---- ]\n\n");

        printf("         ------------------------------------------------------------------------------------------------------\n\n");

        printf("                                                   Inventario\n\n");

        if(personaje->inventario[0] == NULL){

            if(opcion == 13) printf("             ->  [1] Vacio                    ");
            else printf("                 [1] Vacio                    ");

        }
        else{

            if(opcion == 13) printf("             ->  [1] %-25s", personaje->inventario[0]->nombre);
            else printf("                 [1] %-25s", personaje->inventario[0]->nombre);

        }

        if(personaje->inventario[1] == NULL){

            if(opcion == 14) printf(" ->  [2] Vacio                    ");
            else printf("     [2] Vacio                    ");

        }
        else{

            if(opcion == 14) printf(" ->  [2] %-25s", personaje->inventario[1]->nombre);
            else printf("     [2] %-25s", personaje->inventario[1]->nombre);

        }

        if(personaje->inventario[2] == NULL){

            if(opcion == 15) printf(" ->  [3] Vacio\n\n");
            else printf("     [3] Vacio\n\n");

        }
        else{

            if(opcion == 15) printf(" ->  [3] %-25s\n", personaje->inventario[2]->nombre);
            else printf("     [3] %-25s\n", personaje->inventario[2]->nombre);

        }

        printf("\n");

        if(personaje->inventario[3] == NULL){

            if(opcion == 16) printf("             ->  [4] Vacio                    ");
            else printf("                 [4] Vacio                    ");

        }
        else{

            if(opcion == 16) printf("             ->  [4] %-25s", personaje->inventario[3]->nombre);
            else printf("                 [4] %-25s", personaje->inventario[3]->nombre);

        }

        if(personaje->inventario[4] == NULL){

            if(opcion == 17) printf(" ->  [5] Vacio                    ");
            else printf("     [5] Vacio                    ");

        }
        else{

            if(opcion == 17) printf(" ->  [5] %-25s", personaje->inventario[4]->nombre);
            else printf("     [5] %-25s", personaje->inventario[4]->nombre);

        }

        if(personaje->inventario[5] == NULL){

            if(opcion == 18) printf(" ->  [6] Vacio\n\n");
            else printf("     [6] Vacio\n\n");

        }
        else{

            if(opcion == 18) printf(" ->  [6] %-25s\n", personaje->inventario[5]->nombre);
            else printf("     [6] %-25s\n", personaje->inventario[5]->nombre);

        }


        printf("\n\n                             Puede ingresar al menu del inventario presionando la letra i");

        do{
            key = getch();
        }while(key != 13 && key != 72 && key != 80 && key != 77 && key != 75 && key != 73 && key != 105 && key != 27); //derecha 77 izquierda 75

        if(key == 27) return;

        if(key == 13){

            if(opcion >= 1 && opcion <= 12){

                if(!inventarioTienda[opcion-1]->comprado) mostrarOpcionesObjetoTienda(inventarioTienda[opcion-1], personaje);

            }
            else{

                if(personaje->inventario[opcion-13]) verOpcionesDelObjeto(personaje->inventario[opcion-13], opcion - 13, personaje);

            }

        }
        else if(key == 105 || key == 73){
                if(opcion >= 1 && opcion <= 12) opcion = 13;
                else opcion = 1;
        }else{

            switch(key){

                case 72: if(opcion >= 1 && opcion <= 12) {

                        if (opcion == 1 || opcion == 2 || opcion == 3) opcion += 9;//arriba
                        else opcion -= 3;

                    }
                    else{

                        if (opcion == 13 || opcion == 14 || opcion == 15) opcion += 3;//arriba
                        else opcion -= 3;

                    }
                    break;

                case 80: if(opcion >= 1 && opcion <= 12) {

                        if (opcion == 10 || opcion == 11 || opcion == 12) opcion -= 9; //abajo
                        else opcion += 3;

                     }
                    else{

                        if (opcion == 16 || opcion == 17 || opcion == 18) opcion -= 3; //abajo
                        else opcion += 3;

                    }
                    break;

                case 75:if(opcion >= 1 && opcion <= 12){

                        if (opcion == 1 || opcion == 4 || opcion == 7 || opcion == 10) opcion += 2; //izquierda
                        else opcion--;

                    }
                    else{

                        if (opcion == 13 || opcion == 16) opcion += 2; //izquierda
                        else opcion--;

                    }

                    break;

                case 77:if(opcion >= 1 && opcion <= 12){

                        if (opcion == 3 || opcion == 6 || opcion == 9 || opcion == 12) opcion -= 2; //derecha
                        else opcion++;

                    }
                    else{

                        if (opcion == 15 || opcion == 18) opcion -= 2; //derecha
                        else opcion++;

                    }
                    break;
            }

        }

    }while(1);

    free(inventarioTienda);

    printf("\n\n");
    system("pause");


}

int pelear(Personaje * personaje, Enemigo * enemigo){

    srand(time(0));

    if(!personaje || !enemigo){

        printf("\n\nse produjo un error\n\n"); return 0;

    }

    char key;
    int opcion = 1;
    int numero;
    int danoExtra;
    char texto[100];

    //esto es para buscar el arma y armadura equipadas (siempre que lo haya)

    Item * armaEquipada = NULL;
    Item * armaduraEquipada = NULL;
    int i;

    for (i = 0 ; i < 6 ; i++){

        if(personaje->inventario[i] != NULL){

            if( strcmp (personaje->inventario[i]->tipo, "Arma") == 0) armaEquipada = personaje->inventario[i];
            else if( strcmp(personaje->inventario[i]->tipo, "Armadura") == 0) armaduraEquipada = personaje->inventario[i];

        }

    }

    strcpy(texto, "");

    do{

        clrscr();

        printf("-----------------------------------------------------------------------------------------------------------\n");
        printf("                                       %s\n\n", enemigo->nombre);
        printf("                                       Vida: %.1f / %.1f\n\n\n\n", enemigo->vidaActual, enemigo->vidaMaxima);
        printf("                                     %s                    \n\n\n\n", texto);
        printf("                                       %s\n\n", personaje->nombre);
        printf("                                          Nivel: %d\n\n", personaje->nivel);
        printf("                                       Vida: %.1f / %.1f\n", personaje->vidaActual, personaje->vidaMaxima);
        printf("                                       Exp: %d / %d\n", personaje->exp, personaje->expMaxima);
        if(armaEquipada != NULL) printf("                                       Arma: %s\n", armaEquipada->nombre);
        else printf("                                       Arma: No posee arma equipada\n");
        if(armaduraEquipada != NULL) printf("                                       Armadura: %s\n", armaduraEquipada->nombre);
        else printf("                                       Armadura: No posee armadura equipada\n");
        printf("-----------------------------------------------------------------------------------------------------------\n\n");
        if (opcion == 1) printf("          -> Ataque Fisico");
        else printf("             Ataque Fisico");     //
        if (opcion == 2) printf("           -> Ataque A Distancia");
        else printf("              Ataque A Distancia");
        if (opcion == 3) printf("           -> Ataque Magico\n\n");
        else printf("              Ataque Magico\n\n");
        if (opcion == 4) printf("                                        -> Inventario\n");
        else printf("                                           Inventario\n");

        do{
            key = getch();

        }while(key != 13 && key != 72 && key != 80 && key != 77 && key != 75); //derecha 77 izquierda 75

        switch(key){

            case 72: if (opcion == 2) opcion = 4;
                    else if (opcion == 4) opcion = 2;
                break;
            case 80: if (opcion == 4) opcion = 2;
                     else opcion = 4;
                break;
            case 75: if (opcion == 1) opcion = 3;
                     else if (opcion != 4) opcion--;
                break;
            case 77: if (opcion == 3) opcion = 1;
                     else if (opcion != 4) opcion++;
                break;

        }

        if(key == 13){

            strcpy(texto, "");

            if(opcion == 1){

                danoExtra = 1;

                numero = rand() % 1001;

                if(numero <= (personaje->ataqueCriticoCuerpo * 10) ){

                    danoExtra = 2;

                }

                if(personaje->ataqueFisico > enemigo->puntosDefensa){

                    enemigo->vidaActual = enemigo->vidaActual - ( (personaje->ataqueFisico * danoExtra) - enemigo->puntosDefensa);
                    if (danoExtra != 2) strcpy(texto, "Has herido al enemigo");
                    else strcpy(texto, "Has dado un golpe crtico!");

                }
                else{

                    strcpy(texto, "Tu ataque fisico es insuficiente para herir al enemigo");

                }

                mostrarAccionPelea(texto);

                if(enemigo->vidaActual <= 0){

                    strcpy(texto, "Has derrotado al enemigo!");
                    mostrarAccionPelea(texto);
                    Sleep(1000);
                    return 1;
                }

                clrscr();

                printf("-----------------------------------------------------------------------------------------------------------\n");
                printf("                                       %s\n\n", enemigo->nombre);
                printf("                                       Vida: %.1f / %.1f\n\n\n\n", enemigo->vidaActual, enemigo->vidaMaxima);
                printf("                                     %s                    \n\n\n\n", texto);
                printf("                                       %s\n\n", personaje->nombre);
                printf("                                          Nivel: %d\n\n", personaje->nivel);
                printf("                                       Vida: %.1f / %.1f\n", personaje->vidaActual, personaje->vidaMaxima);
                printf("                                       Exp: %d / %d\n", personaje->exp, personaje->expMaxima);
                if(armaEquipada != NULL) printf("                                       Arma: %s\n", armaEquipada->nombre);
                else printf("                                       Arma: No posee arma equipada\n");
                if(armaduraEquipada != NULL) printf("                                       Armadura: %s\n", armaduraEquipada->nombre);
                else printf("                                       Armadura: No posee armadura equipada\n");
                printf("-----------------------------------------------------------------------------------------------------------\n\n");
                printf("                                           TURNO DEL ENEMIGO                                                  ");

                Sleep(2500);

                danoExtra = 1;

                numero = rand() % 1001;

                if(numero <= (enemigo->ataqueCritico * 10) ){

                    danoExtra = 2;
                    strcpy(texto, "Has recibido un golpe crtico!");

                }

                personaje->vidaActual = personaje->vidaActual - ((enemigo->ataque * danoExtra) - personaje->puntosDefensa);
                if (danoExtra != 2) strcpy(texto, "El enemigo te ha herido");

                mostrarAccionPelea(texto);

                if(personaje->vidaActual <= 0){

                    strcpy(texto, "Has sido derrotado..");
                    mostrarAccionPelea(texto);
                    Sleep(1000);
                    return 0;

                }

            }
            else if(opcion == 2){

                danoExtra = 1;

                numero = rand() % 1001;

                if(numero <= (personaje->ataqueCriticoDistancia * 10) ){

                    danoExtra = 2;

                }

                if(personaje->ataqueDistancia >= enemigo->puntosDefensa){

                    enemigo->vidaActual = enemigo->vidaActual - ( (personaje->ataqueDistancia * danoExtra) - enemigo->puntosDefensa );
                    if (danoExtra != 2) strcpy(texto, "Has herido al enemigo");
                    else strcpy(texto, "Has dado un golpe crtico!");
                }
                else{

                    strcpy(texto, "Tu ataque a distancia es insuficiente para herir al enemigo");

                }

                mostrarAccionPelea(texto);

                if(enemigo->vidaActual <= 0){

                    strcpy(texto, "Has derrotado al enemigo!");
                    mostrarAccionPelea(texto);
                    Sleep(1000);
                    return 1;

                }

                clrscr();

                printf("-----------------------------------------------------------------------------------------------------------\n");
                printf("                                       %s\n\n", enemigo->nombre);
                printf("                                       Vida: %.1f / %.1f\n\n\n\n", enemigo->vidaActual, enemigo->vidaMaxima);
                printf("                                     %s                    \n\n\n\n", texto);
                printf("                                       %s\n\n", personaje->nombre);
                printf("                                          Nivel: %d\n\n", personaje->nivel);
                printf("                                       Vida: %.1f / %.1f\n", personaje->vidaActual, personaje->vidaMaxima);
                printf("                                       Exp: %d / %d\n", personaje->exp, personaje->expMaxima);
                if(armaEquipada != NULL) printf("                                       Arma: %s\n", armaEquipada->nombre);
                else printf("                                       Arma: No posee arma equipada\n");
                if(armaduraEquipada != NULL) printf("                                       Armadura: %s\n", armaduraEquipada->nombre);
                else printf("                                       Armadura: No posee armadura equipada\n");
                printf("-----------------------------------------------------------------------------------------------------------\n\n");
                printf("                                           TURNO DEL ENEMIGO                                                  ");

                Sleep(2500);

                danoExtra = 1;

                numero = rand() % 1001;

                if(numero <= (enemigo->ataqueCritico * 10) ){

                    danoExtra = 2;
                    strcpy(texto, "Has recibido un golpe crtico!");

                }

                personaje->vidaActual = personaje->vidaActual - ((enemigo->ataque * danoExtra ) - personaje->puntosDefensa);
                if (danoExtra != 2) strcpy(texto, "El enemigo te ha herido");

                mostrarAccionPelea(texto);

                if(personaje->vidaActual <= 0){

                    strcpy(texto, "Has sido derrotado..");
                    mostrarAccionPelea(texto);
                    Sleep(1000);
                    return 0;

                }

            }
            else if( opcion == 3){

                if(personaje->ataqueMagico >= enemigo->resistenciaMagica){

                    enemigo->vidaActual = enemigo->vidaActual - (personaje->ataqueMagico - enemigo->resistenciaMagica);
                    strcpy(texto, "Has herido al enemigo");
                }
                else{

                    strcpy(texto, "Tu ataque magico es insuficiente para herir al enemigo");

                }

                mostrarAccionPelea(texto);

                if(enemigo->vidaActual <= 0){

                    strcpy(texto, "Has derrotado al enemigo!");
                    mostrarAccionPelea(texto);
                    Sleep(1000);
                    return 1;
                }

                clrscr();

                printf("-----------------------------------------------------------------------------------------------------------\n");
                printf("                                       %s\n\n", enemigo->nombre);
                printf("                                       Vida: %.1f / %.1f\n\n\n\n", enemigo->vidaActual, enemigo->vidaMaxima);
                printf("                                     %s                    \n\n\n\n", texto);
                printf("                                       %s\n\n", personaje->nombre);
                printf("                                          Nivel: %d\n\n", personaje->nivel);
                printf("                                       Vida: %.1f / %.1f\n", personaje->vidaActual, personaje->vidaMaxima);
                printf("                                       Exp: %d / %d\n", personaje->exp, personaje->expMaxima);
                if(armaEquipada != NULL) printf("                                       Arma: %s\n", armaEquipada->nombre);
                else printf("                                       Arma: No posee arma equipada\n");
                if(armaduraEquipada != NULL) printf("                                       Armadura: %s\n", armaduraEquipada->nombre);
                else printf("                                       Armadura: No posee armadura equipada\n");
                printf("-----------------------------------------------------------------------------------------------------------\n\n");
                printf("                                           TURNO DEL ENEMIGO                                                  ");

                Sleep(2500);

                danoExtra = 1;

                numero = rand() % 1001;

                if(numero <= (enemigo->ataqueCritico * 10) ){

                    danoExtra = 2;
                    strcpy(texto, "Has recibido un golpe crtico!");

                }

                personaje->vidaActual = personaje->vidaActual - ( (enemigo->ataque * danoExtra) - personaje->puntosDefensa );
                if (danoExtra != 2) strcpy(texto, "El enemigo te ha herido");

                mostrarAccionPelea(texto);

                if(personaje->vidaActual <= 0){

                    strcpy(texto, "Has sido derrotado..");
                    mostrarAccionPelea(texto);
                    Sleep(1000);
                    return 0;

                }

            }
            else{

                abrirInventario(personaje);

            }

        }

    }while(1);

}

void nuevaPartida(HashTable * armas, HashTable * armaduras, HashTable * pociones, HashTable * enemigos){

    FILE * save = fopen("save.csv", "w");
    fprintf(save, "%d", 0);
    fclose(save);

    clrscr();

    printf("\nIndicanos tu nombre: ");
    char nombreJugador[20];
    scanf("%[^\n]s",nombreJugador);
    fflush(stdin);

    Personaje * personaje = crearPersonaje(nombreJugador);
    clrscr();

    char texto[40] = "Aqui comienza tu aventura ";
    strcat(texto, nombreJugador);
    strcat(texto, "!");

    mostrarLetraPorLetra(texto);

    Sleep(1100);

    mostrarHistoria(2,6);

    char key;
    int opcion = 1;

    do{

        clrscr();

        mostrarHistoriaSinPausas(2,6);
        printf("\n");

        if(opcion == 1) printf("-> Pelear contra el monstruo\n");
        else printf("    Pelear contra el monstruo\n");
        if(opcion == 2) printf("-> Pasar por la puerta a tu derecha\n");
        else printf("    Pasar por la puerta a tu derecha\n");

        printf("\n\nPresione i para abrir el inventario");
        printf("\nPresione e para abrir las estadisticas");

        do{
           key  = getch();
        }while(key != 72 && key != 105 && key != 80 && key != 13 && key != 73 && key != 101 && key != 69);

        switch(key){
            case 72: if(opcion == 1) opcion = 2;
                    else opcion--;
                break;
            case 80: if(opcion == 2) opcion = 1;
                    else opcion++;
                break;
            case 73: abrirInventario(personaje);
                break;
            case 105: abrirInventario(personaje);
                break;
            case 69: abrirEstadisticas(personaje);
                break;
            case 101: abrirEstadisticas(personaje);

        }

        if(key == 13) break;

    }while(1);

    if(opcion == 1){

        Enemigo * esqueleto = searchHashTable(enemigos, "Esqueleto");


        if (pelear(personaje, esqueleto) == 0){

            mostrarHistoria(8,10);

            save = fopen("save.csv", "w");
            fprintf(save,"%d", 0);
            fclose(save);

            free(personaje);

            return;

        }

    }else{

        mostrarHistoria(12,16);

    }

    opcion = 1;

    do{

        clrscr();

        printf("Escoge una de las reliquias: \n\n");

        if(opcion == 1) printf("-> Espada de Bronce\n");
        else printf("    Espada de Bronce\n");
        if(opcion == 2) printf("-> Daga de Bronce\n");
        else printf("    Daga de Bronce\n");
        if(opcion == 3) printf("-> Arco Corto\n");
        else printf("    Arco de Attar\n");
        if(opcion == 4) printf("-> Baculo\n");
        else printf("    Baculo\n");

        do{
           key  = getch();
        }while(key != 72 && key != 80 && key != 13);

        switch(key){
            case 72: if(opcion == 1) opcion = 4;
                    else opcion--;
                break;
            case 80: if(opcion == 4) opcion = 1;
                    else opcion++;
                break;

        }

        if(key == 13) break;

    }while(1);

    if(opcion == 1){

        Item * espada = crearItem(armas, "Espada de Bronce", 1);
        personaje->inventario[0] = espada;

    }
    else if(opcion == 2){

        Item * daga = crearItem(armas,"Daga de Bronce", 1);
        personaje->inventario[0] = daga;

    }
    else if(opcion == 3){

        Item * arco = crearItem(armas,"Arco Corto", 1);
        personaje->inventario[0] = arco;

    }
    else{
        Item * baculo = crearItem(armas,"Baculo", 1);
        personaje->inventario[0] = baculo;

    }

    mostrarHistoria(18,19);
    Sleep(800);
    subirNivel(personaje);
    mostrarHistoria(20,22);

    save = fopen("save.csv", "w");
    fprintf(save,"%d", 1);
    fclose(save);

    guardarPersonaje(personaje);

    opcion = 1;

    do{

        clrscr();

        mostrarHistoriaSinPausas(20,22);
        printf("\n");

        if(opcion == 1) printf("-> Devolverte y atacar al monstruo\n");
        else printf("    Devolverte y atacar al monstruo\n");
        if(opcion == 2) printf("-> Seguir adelante\n\n");
        else printf("    Seguir adelante\n\n");
        printf("Presione i para abrir el inventario\n");
        printf("Presione e para abrir sus estadisticas");

        do{
           key  = getch();
        }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

        switch(key){
            case 72: if(opcion == 1) opcion = 2;
                    else opcion--;
                break;
            case 80: if(opcion == 2) opcion = 1;
                    else opcion++;
                break;
            case 105: abrirInventario(personaje);
                break;
            case 73: abrirInventario(personaje);
                break;
            case 101: abrirEstadisticas(personaje);
                break;
            case 69:  abrirEstadisticas(personaje);
                break;
        }

        if(key == 13) break;

    }while(1);

    if(opcion == 1){

        mostrarHistoria(24,28);

        Enemigo * esqueleto = searchHashTable(enemigos, "Esqueleto");
        if( pelear(personaje, esqueleto) == 0 ){

            save = fopen("save.csv", "w");
            fprintf(save,"%d", 0);
            fclose(save);

            free(personaje);

            mostrarHistoria(8,10);
            return;

        }
        else{

            //en caso de ganar, subes de nivel
            personaje->exp = personaje->expMaxima;
            subirNivel(personaje);

        }

        save = fopen("save.csv", "w");
        fprintf(save,"%d", 2);
        fclose(save);

        guardarPersonaje(personaje);

        //si es que se evita pelear, pasas directamente a la historia desde la linea 50, por lo tanto todo esto se hace solo si la opcion es 1

        mostrarHistoria(30,32);

        opcion = 1;

        do{

            clrscr();

            mostrarHistoriaSinPausas(30,32);
            printf("\n");

            if(opcion == 1) printf("-> Seguir adelante\n");
            else printf("    Seguir adelante\n");
            if(opcion == 2) printf("-> Intentar volver a la habitacion\n\n");
            else printf("    Intentar volver a la habitacion\n\n");
            printf("Presione i para abrir el inventario\n");
            printf("Presione e para abrir sus estadisticas");

            do{
               key  = getch();
            }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

            switch(key){
                case 72: if(opcion == 1) opcion = 2;
                        else opcion--;
                    break;
                case 80: if(opcion == 2) opcion = 1;
                        else opcion++;
                    break;
                case 105: abrirInventario(personaje);
                    break;
                case 73: abrirInventario(personaje);
                    break;
                case 101: abrirEstadisticas(personaje);
                    break;
                case 69:  abrirEstadisticas(personaje);
                    break;
            }

            if(key == 13){

                if(opcion == 1){

                    break;

                }
                else{

                    mostrarHistoria(34,35);

                }
            }

        }while(1);

        save = fopen("save.csv", "w");
        fprintf(save,"%d", 3);
        fclose(save);

        guardarPersonaje(personaje);

        mostrarHistoria(37,42);

        opcion = 1;

        do{

            clrscr();

            mostrarHistoriaSinPausas(37,42);
            printf("\n");

            if(opcion == 1) printf("-> Beber de la fuente\n");
            else printf("    Beber de la fuente\n");
            if(opcion == 2) printf("-> Desconfiar del liquido y seguir adelante\n\n");
            else printf("    Desconfiar del liquido y seguir adelante\n\n");
            printf("Presione i para abrir el inventario\n");
            printf("Presione e para abrir sus estadisticas");

            do{
               key  = getch();
            }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

            switch(key){
                case 72: if(opcion == 1) opcion = 2;
                        else opcion--;
                    break;
                case 80: if(opcion == 2) opcion = 1;
                        else opcion++;
                    break;
                case 105: abrirInventario(personaje);
                    break;
                case 73: abrirInventario(personaje);
                    break;
                case 101: abrirEstadisticas(personaje);
                    break;
                case 69:  abrirEstadisticas(personaje);
                    break;
            }

            if(key == 13){

                if(opcion == 1){

                    mostrarHistoria(44,45);
                    Sleep(400);
                    float vidaAntigua = personaje->vidaActual;
                    personaje->vidaActual = personaje->vidaMaxima;
                    printf("\nVida: %.1f -> %.1f", vidaAntigua, personaje->vidaActual);

                }
                else{

                    mostrarHistoria(47,48);

                }

                break;
            }

        }while(1);

    }

    save = fopen("save.csv", "w");
    fprintf(save,"%d", 4);
    fclose(save);

    guardarPersonaje(personaje);

    mostrarHistoria(50,56);

    opcion = 1;

    do{

        clrscr();

        mostrarHistoriaSinPausas(50,56);
        printf("\n");

        if(opcion == 1) printf("-> Ir por el camino de la izquierda\n");
        else printf("    Ir por el camino de la izquierda\n");
        if(opcion == 2) printf("-> Ir por el camino de en medio\n");
        else printf("    Ir por el camino de en medio\n");
        if(opcion == 3) printf("-> Ir por el camino de la derecha\n\n");
        else printf("    Ir por el camino de la derecha\n\n");
        printf("Presione i para abrir el inventario\n");
        printf("Presione e para abrir sus estadisticas");

        do{
           key  = getch();
        }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

        if(key == 13) break;

        switch(key){
            case 72: if(opcion == 1) opcion = 3;
                    else opcion--;
                break;
            case 80: if(opcion == 3) opcion = 1;
                    else opcion++;
                break;
            case 105: abrirInventario(personaje);
                break;
            case 73: abrirInventario(personaje);
                break;
            case 101: abrirEstadisticas(personaje);
                break;
            case 69:  abrirEstadisticas(personaje);
                break;
        }

    }while(1);

    save = fopen("save.csv", "w");
    fprintf(save,"%d", 5);
    fclose(save);

    guardarPersonaje(personaje);
    int ruta;

    if(opcion == 1){

        ruta = opcion;

        mostrarHistoria(58,64);

        opcion = 1;

        do{

            clrscr();

            mostrarHistoriaSinPausas(58,64);
            printf("\n");

            if(opcion == 1) printf("-> Pelar contra el bandido\n");
            else printf("    Pelear contra el bandido\n");
            if(opcion == 2) printf("-> Pasar por la puerta a tu izquierda\n\n");
            else printf("    Pasar por la puerta a tu izquierda\n\n");
            printf("Presione i para abrir el inventario\n");
            printf("Presione e para abrir sus estadisticas");

            do{
               key  = getch();
            }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

            if(key == 13) break;

            switch(key){
                case 72: if(opcion == 1) opcion = 2;
                        else opcion--;
                    break;
                case 80: if(opcion == 2) opcion = 1;
                        else opcion++;
                    break;
                case 105: abrirInventario(personaje);
                    break;
                case 73: abrirInventario(personaje);
                    break;
                case 101: abrirEstadisticas(personaje);
                    break;
                case 69:  abrirEstadisticas(personaje);
                    break;
            }

        }while(1);

        save = fopen("save.csv", "w");
        fprintf(save,"%d", 6);
        fclose(save);

        guardarPersonaje(personaje);

        if(opcion == 1){

            Enemigo * bandido = searchHashTable(enemigos, "Bandido");
            pelear(personaje, bandido);
            mostrarHistoria(66,70);
            personaje->oro += 500;
            printf("\n\n");
            system("pause");

        }

        mostrarHistoria(72,75);

        opcion = 1;

        do{

            clrscr();

            mostrarHistoriaSinPausas(72,75);
            printf("\n");

            if(opcion == 1) printf("-> Pelear contra el bandido\n");
            else printf("    Pelear contra el bandido\n");
            if(opcion == 2) printf("-> Pasar por la puerta a tu izquierda\n");
            else printf("    Pasar por la puerta a tu izquierda\n");
            if(opcion == 3) printf("-> Pasar por la puerta a tu derecha\n\n");
            else printf("    Pasar por la puerta a tu derecha\n\n");

            printf("Presione i para abrir el inventario\n");
            printf("Presione e para abrir sus estadisticas");

            do{
               key  = getch();
            }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

            if(key == 13) break;

            switch(key){
                case 72: if(opcion == 1) opcion = 3;
                        else opcion--;
                    break;
                case 80: if(opcion == 3) opcion = 1;
                        else opcion++;
                    break;
                case 105: abrirInventario(personaje);
                    break;
                case 73: abrirInventario(personaje);
                    break;
                case 101: abrirEstadisticas(personaje);
                    break;
                case 69:  abrirEstadisticas(personaje);
                    break;
            }

        }while(1);

        save = fopen("save.csv", "w");
        fprintf(save,"%d", 7);
        fclose(save);

        guardarPersonaje(personaje);

        if(opcion == 1){

            Enemigo * bandido2 = searchHashTable(enemigos, "Bandido2");
            pelear(personaje, bandido2);
            mostrarHistoria(77,78);
            personaje->oro += 500;
            printf("\n\n");
            system("pause");

            opcion = 1;

            do{

                clrscr();

                mostrarHistoriaSinPausas(72,75);
                printf("\n");

                if(opcion == 1) printf("-> Pasar por la puerta a tu izquierda\n");
                else printf("    Pasar por la puerta a tu izquierda\n");
                if(opcion == 2) printf("-> Pasar por la puerta a tu derecha\n\n");
                else printf("    Pasar por la puerta a tu derecha\n\n");

                printf("Presione i para abrir el inventario\n");
                printf("Presione e para abrir sus estadisticas");

                do{
                   key  = getch();
                }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

                if(key == 13) break;

                switch(key){
                    case 72: if(opcion == 1) opcion = 2;
                            else opcion--;
                        break;
                    case 80: if(opcion == 2) opcion = 1;
                            else opcion++;
                        break;
                    case 105: abrirInventario(personaje);
                        break;
                    case 73: abrirInventario(personaje);
                        break;
                    case 101: abrirEstadisticas(personaje);
                        break;
                    case 69:  abrirEstadisticas(personaje);
                        break;
                }

            }while(1);

               save = fopen("save.csv", "w");
            fprintf(save,"%d", 8);
            fclose(save);

            guardarPersonaje(personaje);

            if(opcion == 1) opcion = 2;
            else if(opcion == 2) opcion = 3;

        }

        if(opcion == 2){ //Camino a la izquierda

            mostrarHistoria(86,89);
            opcion = 1;

            do{

                clrscr();

                mostrarHistoriaSinPausas(86,89);
                printf("\n");

                if(opcion == 1) printf("-> Pelear contra el bandido\n");
                else printf("    Pelear contra el bandido\n");
                if(opcion == 2) printf("-> Hablar con el bandido\n\n");
                else printf("    Hablar con el bandido\n\n");

                printf("Presione i para abrir el inventario\n");
                printf("Presione e para abrir sus estadisticas");

                do{
                    key  = getch();
                }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

                if(key == 13) break;

                switch(key){
                    case 72: if(opcion == 1) opcion = 2;
                            else opcion--;
                        break;
                    case 80: if(opcion == 2) opcion = 1;
                            else opcion++;
                        break;
                    case 105: abrirInventario(personaje);
                        break;
                    case 73: abrirInventario(personaje);
                        break;
                    case 101: abrirEstadisticas(personaje);
                        break;
                    case 69:  abrirEstadisticas(personaje);
                        break;
                }

            }while(1);

            save = fopen("save.csv", "w");
            fprintf(save,"%d", 9);
            fclose(save);

            guardarPersonaje(personaje);

            if(opcion == 1){ //pelear contra el bandido

                Enemigo * bandido3 = searchHashTable(enemigos, "Bandido3");
                pelear(personaje, bandido3);

                mostrarHistoria(91,92);

                opcion = 1;

                do{

                    clrscr();

                    mostrarHistoriaSinPausas(91,92);
                    printf("\n");

                    if(opcion == 1) printf("-> Tomar su arma\n");
                    else printf("    Tomar su arma\n");
                    if(opcion == 2) printf("-> Tomar su oro\n\n");
                    else printf("    Tomar su oro\n\n");

                    printf("Presione i para abrir el inventario\n");
                    printf("Presione e para abrir sus estadisticas");

                    do{
                        key  = getch();
                    }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

                    if(key == 13) break;

                    switch(key){
                        case 72: if(opcion == 1) opcion = 2;
                                else opcion--;
                            break;
                        case 80: if(opcion == 2) opcion = 1;
                                else opcion++;
                            break;
                        case 105: abrirInventario(personaje);
                            break;
                        case 73: abrirInventario(personaje);
                            break;
                        case 101: abrirEstadisticas(personaje);
                            break;
                        case 69:  abrirEstadisticas(personaje);
                            break;
                    }

                }while(1);

                save = fopen("save.csv", "w");
                fprintf(save,"%d", 10);
                fclose(save);

                guardarPersonaje(personaje);

                if(opcion == 1){ //Recoges su arma

                    mostrarHistoria(94,94);
                    Item * nuevo = crearItem(armas, "Espada Oxidada", 1);
                    int i;
                    for (i = 0 ; i < 6 ; i++){

                        if(personaje->inventario[i] == NULL){

                            personaje->inventario[i] = nuevo;
                            break;
                        }

                    }
                }
                else{ //Recoges su oro

                    mostrarHistoria(96,96);
                    personaje->oro += 250;

                }

                printf("\n\n");
                system("pause");


            }
            else{ //Hablar con el bandido

                mostrarHistoria(98,102);

                opcion = 1;

                do{

                    clrscr();

                    mostrarHistoriaSinPausas(98,102);
                    printf("\n");

                    if(opcion == 1) printf("-> Escoger la informacion\n");
                    else printf("    Escoger la informacion\n");
                    if(opcion == 2) printf("-> Escoger el equipamiento\n\n");
                    else printf("    Escoger el equipamiento\n\n");

                    printf("Presione i para abrir el inventario\n");
                    printf("Presione e para abrir sus estadisticas");

                    do{
                        key  = getch();
                    }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

                    if(key == 13) break;

                    switch(key){
                        case 72: if(opcion == 1) opcion = 2;
                                else opcion--;
                            break;
                        case 80: if(opcion == 2) opcion = 1;
                                else opcion++;
                            break;
                        case 105: abrirInventario(personaje);
                            break;
                        case 73: abrirInventario(personaje);
                            break;
                        case 101: abrirEstadisticas(personaje);
                            break;
                        case 69:  abrirEstadisticas(personaje);
                            break;
                    }

                }while(1);

                save = fopen("save.csv", "w");
                fprintf(save,"%d", 11);
                fclose(save);

                guardarPersonaje(personaje);

                if(opcion == 1){ //se escoge la informacion

                    mostrarHistoria(104,109);

                }
                else{ // se escoge el equipamiento

                    mostrarHistoria(111,111);
                    Item * nuevo = crearItem(armas,"Espada Oxidada", 1);
                    int i;

                    for (i = 0 ; i < 6 ; i++){

                        if(personaje->inventario[i] == NULL){

                            personaje->inventario[i] = nuevo;
                            break;

                        }

                    }

                    personaje->oro += 250;

                }


            }


        }
        else if (opcion == 3){ //Camino a la derecha

            mostrarHistoria(80,84);
            Item * nuevo = crearItem(pociones, "Pocion Mediana", 3);
            int i;
            for (i = 0 ; i < 6 ; i++){

                if(personaje->inventario[i] == NULL){

                    personaje->inventario[i] = nuevo;
                    break;

                }

            }
            printf("\n\n");
            system("pause");

        }

        mostrarHistoria(113, 116);

    } // OPCION 1 CAMINO  A LA IZQUIERDA
    else if(opcion == 2){

        ruta = opcion;

        mostrarHistoria(166, 172);
        Item * nuevo = crearItem(pociones, "Pocion Mediana", 3);

        int i;
        for (i = 0 ; i < 6 ; i++){

            if(personaje->inventario[i] == NULL){

                personaje->inventario[i] = nuevo;
                break;

            }

        }

        Enemigo * centauro = searchHashTable(enemigos, "Centauro");

        if(pelear(personaje, centauro) == 0){

            mostrarHistoria(162,164);
            printf("\n\n");
            system("pause");
            return;

        }

        personaje->exp = personaje->expMaxima;
        subirNivel(personaje);

        mostrarHistoria(174,178);

        opcion = 1;

        do{

            clrscr();

            mostrarHistoriaSinPausas(174,178);
            printf("\n");

            if(opcion == 1) printf("-> Pasar por la puerta a la izquierda\n");
            else printf("    Pasar por la puerta a la izquierda\n");
            if(opcion == 2) printf("-> Pelear contra el enemigo\n");
            else printf("    Pelear contra el enemigo\n");
            if(opcion == 3) printf("-> Pasar por la puerta a la derecha\n\n");
            else printf("    Pasar por la puerta a la derecha\n\n");

            printf("Presione i para abrir el inventario\n");
            printf("Presione e para abrir sus estadisticas");

            do{
                key  = getch();
            }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

            if(key == 13) break;

            switch(key){
                case 72: if(opcion == 1) opcion = 3;
                        else opcion--;
                    break;
                case 80: if(opcion == 3) opcion = 1;
                        else opcion++;
                    break;
                case 105: abrirInventario(personaje);
                    break;
                case 73: abrirInventario(personaje);
                    break;
                case 101: abrirEstadisticas(personaje);
                    break;
                case 69:  abrirEstadisticas(personaje);
                    break;
            }

        }while(1);

        if(opcion == 1){ //puerta de la izquierda

            mostrarHistoria(180,183);
            Enemigo * centauro2 = searchHashTable(enemigos, "Centauro Menor");

            if(pelear (personaje, centauro2) == 0){

                mostrarHistoria(162,164);
                printf("\n\n");
                system("pause");
                return;

            }

            mostrarHistoria(185,189);
            personaje->oro += 625;

        }
        else if(opcion == 2){

            Enemigo * ladron = searchHashTable(enemigos, "Ladron");
            if(pelear(personaje, ladron) == 0){

                mostrarHistoria(162,164);
                printf("\n\n");
                system("pause");
                return;

            }

            personaje->oro += 250;
            personaje->exp += ( personaje->expMaxima / 2 );
            mostrarHistoria(196, 198);
            system("pause");

            opcion = 1;

            do{

                clrscr();

                mostrarHistoriaSinPausas(174,178);
                printf("\n");

                if(opcion == 1) printf("-> Pasar por la puerta a la izquierda\n");
                else printf("    Pasar por la puerta a la izquierda\n");
                if(opcion == 2) printf("-> Pasar por la puerta a la derecha\n\n");
                else printf("    Pasar por la puerta a la derecha\n\n");

                printf("Presione i para abrir el inventario\n");
                printf("Presione e para abrir sus estadisticas");

                do{
                    key  = getch();
                }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

                if(key == 13) break;

                switch(key){
                    case 72: if(opcion == 1) opcion = 2;
                            else opcion--;
                        break;
                    case 80: if(opcion == 2) opcion = 1;
                            else opcion++;
                        break;
                    case 105: abrirInventario(personaje);
                        break;
                    case 73: abrirInventario(personaje);
                        break;
                    case 101: abrirEstadisticas(personaje);
                        break;
                    case 69:  abrirEstadisticas(personaje);
                        break;
                }

            }while(1);

            if(opcion == 1){

                personaje->vidaActual /= 2;

                mostrarHistoria(180,183);
                Enemigo * centauro2 = searchHashTable(enemigos, "Centauro Menor");

                if(pelear (personaje, centauro2) == 0){

                    mostrarHistoria(162,164);
                    printf("\n\n");
                    system("pause");
                    return;

                }

                mostrarHistoria(185,189);
                personaje->oro += 625;

            }
            else{

                mostrarHistoria(200,205);
                personaje->oro += 250;
                printf("\n\n");
                system("pause");

            }

        }
        else if (opcion == 3){

            mostrarHistoria(192,194);
            personaje->oro += 250;
            printf("\n\n");
            system("pause");

            Enemigo * ladron = searchHashTable(enemigos, "Ladron");
            if(pelear(personaje, ladron) == 0){

                mostrarHistoria(162,164);
                printf("\n\n");
                system("pause");
                return;

            }

            personaje->oro += 250;
            personaje->exp += ( personaje->expMaxima / 2 );
            mostrarHistoria(196, 198);
            printf("\n\n");
            system("pause");

        }

        mostrarHistoria(207, 211);
        printf("\n\n");
        system("pause");

    } //OPCION 2 CAMINO DE AL MEDIO
    else if(opcion == 3){

        ruta = opcion;

        mostrarHistoria(118,125);

        int cont = 0;

        int i;
        for (i = 0; i < 6 ; i++){

            if(personaje->inventario[i] == NULL){

                cont++;
                if(cont > 3) break;
                else{

                    Item * pocion = crearItem(pociones, "Pocion Menor", 3);
                    personaje->inventario[i] = pocion;

                }

            }

        }

        Enemigo * centauro = searchHashTable(enemigos, "Centauro");

        if (pelear (personaje, centauro) == 0){

            mostrarHistoria(162,164);
            printf("\n\n");
            system("pause");
            return;

        }

        mostrarHistoria(127, 131);

        opcion = 1;

        do{

            clrscr();

            mostrarHistoriaSinPausas(127,131);
            printf("\n");

            if(opcion == 1) printf("-> Pasar por la puerta a la izquierda\n");
            else printf("    Pasar por la puerta a la izquierda\n");
            if(opcion == 2) printf("-> Pelear contra el enemigo\n");
            else printf("    Pelear contra el enemigo\n");
            if(opcion == 3) printf("-> Pasar por la puerta a la derecha\n\n");
            else printf("    Pasar por la puerta a la derecha\n\n");

            printf("Presione i para abrir el inventario\n");
            printf("Presione e para abrir sus estadisticas");

            do{
                key  = getch();
            }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

            if(key == 13) break;

            switch(key){
                case 72: if(opcion == 1) opcion = 3;
                        else opcion--;
                    break;
                case 80: if(opcion == 3) opcion = 1;
                        else opcion++;
                    break;
                case 105: abrirInventario(personaje);
                    break;
                case 73: abrirInventario(personaje);
                    break;
                case 101: abrirEstadisticas(personaje);
                    break;
                case 69:  abrirEstadisticas(personaje);
                    break;
            }

        }while(1);

        if(opcion == 1){ //puerta izquierda

            mostrarHistoria(133,136);
            personaje->vidaActual /= 2;

            Enemigo * centauro2 = searchHashTable(enemigos, "Centauro Menor");

            if(pelear (personaje, centauro2) == 0){

                mostrarHistoria(162,164);
                printf("\n\n");
                system("pause");
                return;

            }

            personaje->exp = personaje->expMaxima;
            subirNivel(personaje);

            personaje->oro += 250;

            mostrarHistoria(138,145);
            printf("\n\n");
            system("pause");


        }
        else if(opcion == 2){

            Enemigo * centauro3 = searchHashTable(enemigos, "Centauro Mayor");
            if(pelear(personaje, centauro3) == 0){

                mostrarHistoria(162,164);
                printf("\n\n");
                system("pause");
                return;

            }

            personaje->exp = personaje->expMaxima;
            subirNivel(personaje);
            personaje->exp = personaje->expMaxima;
            subirNivel(personaje);

            opcion = 1;

            do{

                clrscr();

                mostrarHistoriaSinPausas(127,131);
                printf("\n");

                if(opcion == 1) printf("-> Pasar por la puerta a la izquierda\n");
                else printf("    Pasar por la puerta a la izquierda\n");
                if(opcion == 2) printf("-> Pasar por la puerta a la derecha\n\n");
                else printf("    Pasar por la puerta a la derecha\n\n");

                printf("Presione i para abrir el inventario\n");
                printf("Presione e para abrir sus estadisticas");

                do{
                    key  = getch();
                }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

                if(key == 13) break;

                switch(key){
                    case 72: if(opcion == 1) opcion = 2;
                            else opcion--;
                        break;
                    case 80: if(opcion == 2) opcion = 1;
                            else opcion++;
                        break;
                    case 105: abrirInventario(personaje);
                        break;
                    case 73: abrirInventario(personaje);
                        break;
                    case 101: abrirEstadisticas(personaje);
                        break;
                    case 69:  abrirEstadisticas(personaje);
                        break;
                }

            }while(1);

            if(opcion == 1){ //camino a la izquierda

                mostrarHistoria(134,136);
                personaje->vidaActual /= 2;

                printf("\n\n");
                system("pause");

                Enemigo * centauro2 = searchHashTable(enemigos, "Centauro Menor");

                if(pelear (personaje, centauro2) == 0){

                    mostrarHistoria(162,164);
                    printf("\n\n");
                    system("pause");
                    return;

                }

                personaje->exp = personaje->expMaxima;
                subirNivel(personaje);
                personaje->oro += 250;

                mostrarHistoria(138,145);
                printf("\n\n");
                system("pause");

            }
            else{ //camino a la derecha

                mostrarHistoria(154,160);
                personaje->oro += 250;

            }

        }
        else if(opcion == 3){ //camino a la derecha

            mostrarHistoria(148,150);

            Enemigo * centauro3 = searchHashTable(enemigos, "Centauro Mayor");

            if(pelear(personaje, centauro3) == 0){

                mostrarHistoria(162,164);
                printf("\n\n");
                system("pause");
                return;

            }

            mostrarHistoria(152,160);
            personaje->oro += 250;

        }

        mostrarHistoria(207, 211);
        printf("\n\n");
        system("pause");

    } //OPCION 3 CAMINO DE LA DERECHA

    if(ruta == 1){

        mostrarHistoria(113, 116);
        opcion = 1;

        do{

            clrscr();

            mostrarHistoriaSinPausas(113,116);
            printf("\n");

            if(opcion == 1) printf("-> Mercado\n");
            else printf("    Mercado\n");
            if(opcion == 2) printf("-> Seguir por el pasillo\n\n");
            else printf("    Seguir por el pasillo\n\n");

            printf("Presione i para abrir el inventario\n");
            printf("Presione e para abrir sus estadisticas");

            do{
                key  = getch();
            }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

            if(key == 13) break;

            switch(key){
                case 72: if(opcion == 1) opcion = 2;
                        else opcion--;
                    break;
                case 80: if(opcion == 2) opcion = 1;
                        else opcion++;
                    break;
                case 105: abrirInventario(personaje);
                    break;
                case 73: abrirInventario(personaje);
                    break;
                case 101: abrirEstadisticas(personaje);
                    break;
                case 69:  abrirEstadisticas(personaje);
                    break;
            }

        }while(1);

    }
    else{

        opcion = 1;

        do{

            clrscr();

            mostrarHistoriaSinPausas(207,211);
            printf("\n");

            if(opcion == 1) printf("-> Mercado\n");
            else printf("    Mercado\n");
            if(opcion == 2) printf("-> Seguir por el pasillo\n\n");
            else printf("    Seguir por el pasillo\n\n");

            printf("Presione i para abrir el inventario\n");
            printf("Presione e para abrir sus estadisticas");

            do{
                key  = getch();
            }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

            if(key == 13) break;

            switch(key){
                case 72: if(opcion == 1) opcion = 2;
                        else opcion--;
                    break;
                case 80: if(opcion == 2) opcion = 1;
                        else opcion++;
                    break;
                case 105: abrirInventario(personaje);
                    break;
                case 73: abrirInventario(personaje);
                    break;
                case 101: abrirEstadisticas(personaje);
                    break;
                case 69:  abrirEstadisticas(personaje);
                    break;
            }

        }while(1);

    }

    if(opcion == 1){

        abrirTienda(personaje, "articulos_tienda.csv", armas, armaduras, pociones);

    }

    system("pause");
    free(personaje);
    return;

}

void cargarPartida(HashTable * armas, HashTable * armaduras, HashTable * pociones, HashTable * enemigos){

    FILE * save = fopen("save.csv", "r");
    char linea[10];
    fgets(linea, 9, save);
    int savePoint = atoi(get_csv_field(linea, 1));
    fclose(save);

    bool cargado = false;

    char key;
    int opcion;

    if(savePoint == 0){

        clrscr();
        char texto[64];
        strcpy(texto, "No existen datos guardados, por favor, cree una nueva partida.");
        mostrarLetraPorLetra(texto);
        printf("\n\n");
        system("pause");
        return;

    }

    Personaje * personaje = cargarPersonaje(personaje, armas, armaduras, pociones);

    if( (savePoint >= 1 && savePoint <= 4 ) || cargado == true){

        if(savePoint == 1 || cargado == true){

            mostrarHistoria(20,22);

            opcion = 1;

            do{

                clrscr();

                mostrarHistoriaSinPausas(20,22);
                printf("\n");

                if(opcion == 1) printf("-> Devolverte y atacar al monstruo\n");
                else printf("    Devolverte y atacar al monstruo\n");
                if(opcion == 2) printf("-> Seguir adelante\n\n");
                else printf("    Seguir adelante\n\n");
                printf("Presione i para abrir el inventario\n");
                printf("Presione e para abrir sus estadisticas");

                do{
                   key  = getch();
                }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

                switch(key){
                    case 72: if(opcion == 1) opcion = 2;
                            else opcion--;
                        break;
                    case 80: if(opcion == 2) opcion = 1;
                            else opcion++;
                        break;
                    case 105: abrirInventario(personaje);
                        break;
                    case 73: abrirInventario(personaje);
                        break;
                    case 101: abrirEstadisticas(personaje);
                        break;
                    case 69:  abrirEstadisticas(personaje);
                        break;
                }

                if(key == 13) break;

            }while(1);

            if(opcion == 1){

                mostrarHistoria(24,28);

                Enemigo * esqueleto = searchHashTable(enemigos, "Esqueleto");
                if( pelear(personaje, esqueleto) == 0 ){

                    save = fopen("save.csv", "w");
                    fprintf(save,"%d", 0);
                    fclose(save);

                    free(personaje);

                    mostrarHistoria(8,10);
                    return;

                }
                else{

                    //en caso de ganar, subes de nivel
                    personaje->exp = personaje->expMaxima;
                    subirNivel(personaje);

                }

                save = fopen("save.csv", "w");
                fprintf(save,"%d", 2);
                fclose(save);

                if(!cargado) cargado = true;

                if(savePoint == 2 || cargado == true){

                    mostrarHistoria(30,32);

                    opcion = 1;

                    do{

                        clrscr();

                        mostrarHistoriaSinPausas(30,32);
                        printf("\n");

                        if(opcion == 1) printf("-> Seguir adelante\n");
                        else printf("    Seguir adelante\n");
                        if(opcion == 2) printf("-> Intentar volver a la habitacion\n\n");
                        else printf("    Intentar volver a la habitacion\n\n");
                        printf("Presione i para abrir el inventario\n");
                        printf("Presione e para abrir sus estadisticas");

                        do{
                           key  = getch();
                        }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

                        switch(key){
                            case 72: if(opcion == 1) opcion = 2;
                                    else opcion--;
                                break;
                            case 80: if(opcion == 2) opcion = 1;
                                    else opcion++;
                                break;
                            case 105: abrirInventario(personaje);
                                break;
                            case 73: abrirInventario(personaje);
                                break;
                            case 101: abrirEstadisticas(personaje);
                                break;
                            case 69:  abrirEstadisticas(personaje);
                                break;
                        }

                        if(key == 13){

                            if(opcion == 1){

                                break;

                            }
                            else{

                                mostrarHistoria(34,35);

                            }
                        }

                    }while(1);

                    save = fopen("save.csv", "w");
                    fprintf(save,"%d", 3);
                    fclose(save);
                    if(!cargado) cargado = true;

                }

                if (savePoint == 3 || cargado){

                    mostrarHistoria(37,42);

                    opcion = 1;

                    do{

                        clrscr();

                        mostrarHistoriaSinPausas(37,42);
                        printf("\n");

                        if(opcion == 1) printf("-> Beber de la fuente\n");
                        else printf("    Beber de la fuente\n");
                        if(opcion == 2) printf("-> Desconfiar del liquido y seguir adelante\n\n");
                        else printf("    Desconfiar del liquido y seguir adelante\n\n");
                        printf("Presione i para abrir el inventario\n");
                        printf("Presione e para abrir sus estadisticas");

                        do{
                           key  = getch();
                        }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

                        switch(key){
                            case 72: if(opcion == 1) opcion = 2;
                                    else opcion--;
                                break;
                            case 80: if(opcion == 2) opcion = 1;
                                    else opcion++;
                                break;
                            case 105: abrirInventario(personaje);
                                break;
                            case 73: abrirInventario(personaje);
                                break;
                            case 101: abrirEstadisticas(personaje);
                                break;
                            case 69:  abrirEstadisticas(personaje);
                                break;
                        }

                        if(key == 13){

                            if(opcion == 1){

                                mostrarHistoria(44,45);
                                Sleep(400);
                                float vidaAntigua = personaje->vidaActual;
                                personaje->vidaActual = personaje->vidaMaxima;
                                printf("\nVida: %.1f -> %.1f", vidaAntigua, personaje->vidaActual);

                            }
                            else{

                                mostrarHistoria(46,47);

                            }

                            break;
                        }

                    }while(1);

                    if(!cargado) cargado = true;
                }

            }

        }

    }

    if (savePoint == 4 || cargado){

        save = fopen("save.csv", "w");
        fprintf(save,"%d", 4);
        fclose(save);

        mostrarHistoria(50,56);

        opcion = 1;

        do{

            clrscr();

            mostrarHistoriaSinPausas(50,56);
            printf("\n\n");

            if(opcion == 1) printf("-> Ir por el camino de la izquierda\n");
            else printf("    Ir por el camino de la izquierda\n");
            if(opcion == 2) printf("-> Ir por el camino de en medio\n");
            else printf("    Ir por el camino de en medio\n");
            if(opcion == 3) printf("-> Ir por el camino de la derecha\n\n");
            else printf("    Ir por el camino de la derecha\n\n");
            printf("Presione i para abrir el inventario\n");
            printf("Presione e para abrir sus estadisticas");

            do{
               key  = getch();
            }while(key != 72 && key != 80 && key != 13 && key != 105 && key != 73 && key != 101 && key != 69);

            switch(key){
                case 72: if(opcion == 1) opcion = 3;
                        else opcion--;
                    break;
                case 80: if(opcion == 3) opcion = 1;
                        else opcion++;
                    break;
                case 105: abrirInventario(personaje);
                    break;
                case 73: abrirInventario(personaje);
                    break;
                case 101: abrirEstadisticas(personaje);
                    break;
                case 69:  abrirEstadisticas(personaje);
                    break;
            }

        }while(1);

        save = fopen("save.csv", "w");
        fprintf(save,"%d", 5);
        fclose(save);

        if(!cargado) cargado = true;

    }

    if(savePoint >= 5 && savePoint <= 10){

         int ruta;

    }



    system("pause");

    free(personaje);

    return;

}
