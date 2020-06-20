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

Personaje * crearPersonaje(char nombre[]){

    Personaje * personaje = (Personaje *) malloc (sizeof(Personaje));
    strcpy(personaje->nombre, nombre);

    personaje->nivel = 1;
    personaje->puntosDeHabildad = 0;

    personaje->fuerza = 1;
    personaje->agilidad = 1;
    personaje->vitalidad = 1;
    personaje->inteligencia = 1;

    personaje->ataqueFisico;
    personaje->ataqueDistancia;
    personaje->ataqueCriticoDistancia;
    personaje->ataqueCriticoCuerpo;
    personaje->vidaMaxima;
    personaje->vidaActual = 6;
    personaje->ataqueMagico;

    personaje->puntosDefensa = 0;
    personaje->resistenciaMagica = 0;

    actualizarStats(personaje);

    personaje->exp = 0;
    personaje->expMaxima = 12;
    personaje->oro = 0;

    personaje->inventario = (Item **) calloc (5, sizeof(Item *));

    return personaje;

}

void actualizarStats(Personaje * personaje){
    personaje->ataqueFisico = 1.5 * personaje->fuerza;
    personaje->ataqueDistancia = 1 * personaje->agilidad;
    personaje->ataqueCriticoDistancia = 1 * personaje->agilidad;
    personaje->ataqueCriticoCuerpo = 1.5 * personaje->agilidad;
    personaje->vidaMaxima = 6 * personaje->vitalidad;
    personaje->ataqueMagico = 2 * personaje->inteligencia;
}

void subirNivel(Personaje * personaje){

    int expMaximaAntigua = personaje->expMaxima;
    int puntosHabilidadAntiguos = personaje->puntosDeHabildad;

    if (personaje->exp > personaje->expMaxima){

        personaje->exp = personaje->exp - personaje->expMaxima;

    }
    else{

        personaje->exp = 0;

    }

    personaje->expMaxima = personaje->expMaxima * 1.2;

    personaje->nivel++;
    personaje->puntosDeHabildad = personaje->puntosDeHabildad + 5;

    char * texto = "Felicidades, has subido de nivel!";
    mostrarLetraPorLetra(texto);

    Sleep(1000);

    printf("\n\n    Tu nuevo nivel: %d\n", personaje->nivel);
    printf("    Tu nueva experiencia: %d\n", personaje->exp);
    printf("    Exp para subir al siguiente nivel: %d -> %d\n", expMaximaAntigua, personaje->expMaxima);
    printf("    Puntos de habilidad: %d -> %d\n", puntosHabilidadAntiguos, personaje->puntosDeHabildad);
    printf("    Puedes utilizar los puntos de habilidad en el menu de estadisticas.\n\n");
    system("pause");

}

void cargarEnemigos(HashTable * enemigos){

    FILE * fp = fopen("enemigos.csv", "r");
    if(fp == NULL) return;
    char linea[128];

    while(fgets(linea, 127, fp) != NULL){

        Enemigo * nuevo = (Enemigo *) malloc (sizeof(Enemigo));

        nuevo->nombre = get_csv_field(linea, 1);
        nuevo->ataqueFisico = atof(get_csv_field(linea, 2));
        nuevo->ataqueDistancia = atof(get_csv_field(linea, 3));
        nuevo->ataqueMagico = atof(get_csv_field(linea, 4));
        nuevo->ataqueCriticoDistancia = atof(get_csv_field(linea, 5));
        nuevo->ataqueCriticoCuerpo = atof(get_csv_field(linea, 6));

        nuevo->vidaMaxima = atof(get_csv_field(linea, 7));
        nuevo->vidaActual = atof(get_csv_field(linea, 8));
        nuevo->puntosDefensa = atof(get_csv_field(linea, 9));
        nuevo->resistenciaMagica = atof(get_csv_field(linea, 10));

        insertHashTable(enemigos, nuevo->nombre, nuevo);
    }

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

        nueva->fuerza = atoi(get_csv_field(linea, 7));
        nueva->agilidad = atoi(get_csv_field(linea, 8));
        nueva->vitalidad = atoi(get_csv_field(linea, 9));
        nueva->inteligencia = atoi(get_csv_field(linea, 10));

        nueva->requisitoMinimoFuerza = atoi(get_csv_field(linea, 11));
        nueva->requisitoMinimoAgilidad = atoi(get_csv_field(linea, 12));
        nueva->requisitoMinimoVitalidad = atoi(get_csv_field(linea, 13));
        nueva->requisitoMinimoInteligencia = atoi(get_csv_field(linea, 14));

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
        nueva->resistenciaMagica = atof(get_csv_field(linea, 3));

        nueva->requisitoMinimoFuerza = atoi(get_csv_field(linea, 4));
        nueva->requisitoMinimoAgilidad = atoi(get_csv_field(linea, 5));
        nueva->requisitoMinimoVitalidad = atoi(get_csv_field(linea, 6));
        nueva->requisitoMinimoInteligencia = atoi(get_csv_field(linea, 7));

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

        personaje->fuerza = personaje->fuerza + item->arma->fuerza;
        personaje->agilidad = personaje->agilidad + item->arma->agilidad;
        personaje->vitalidad = personaje->vitalidad + item->arma->vitalidad;
        personaje->inteligencia = personaje->inteligencia + item->arma->inteligencia;

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

    personaje->fuerza = personaje->fuerza - item->arma->fuerza;
    personaje->agilidad = personaje->agilidad - item->arma->agilidad;
    personaje->vitalidad = personaje->vitalidad - item->arma->vitalidad;
    personaje->inteligencia = personaje->inteligencia - item->arma->inteligencia;

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
        personaje->resistenciaMagica = personaje->resistenciaMagica + item->armadura->resistenciaMagica;

        printf("\nLa armadura \"%s\" ha sido equipada correctamente.", item->armadura->nombre);

    }

}

void desequiparArmadura(Item * item, Personaje * personaje){

    item->equipado = false;

    personaje->puntosDefensa = personaje->puntosDefensa - item->armadura->puntosDefensa;
    personaje->resistenciaMagica = personaje->resistenciaMagica - item->armadura->resistenciaMagica;

    printf("\nLa armadura \"%s\" ha sido desequipada correctamente.", item->armadura->nombre);

}

void mostrarObjeto(Item * item){

    if (strcmp(item->tipo, "Arma") == 0){

        printf("->  %s\n", item->arma->nombre);

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

            if(item->arma->ataqueCriticoCuerpo > 0) printf("        Ataque Critico a Cuerpo: %.1f\n", item->arma->ataqueCriticoCuerpo);
            printf("        Ataque Critico a Cuerpo: %.1f\n", item->arma->ataqueCriticoCuerpo);

        }

        if(item->arma->ataqueMagico != 0){

            if(item->arma->ataqueMagico > 0)  printf("        Ataque Magico: %.1f\n", item->arma->ataqueMagico);
            printf("        Ataque Magico: %.1f\n", item->arma->ataqueMagico);

        }

        if(item->arma->fuerza != 0){

            if(item->arma->fuerza > 0) printf("        Fuerza: +%d\n", item->arma->fuerza);
            else printf("        Fuerza: %d\n", item->arma->fuerza);

        }

        if(item->arma->agilidad != 0){

            if(item->arma->agilidad > 0) printf("        Agilidad: +%d\n", item->arma->agilidad);
            else printf("        Agilidad: %d\n", item->arma->agilidad);

        }

        if(item->arma->vitalidad != 0){

            if(item->arma->vitalidad > 0) printf("        Vitalidad: +%d\n", item->arma->vitalidad);
            else printf("        Vitalidad: %d\n", item->arma->vitalidad);

        }

        if(item->arma->inteligencia != 0){

            if(item->arma->inteligencia > 0) printf("        Inteligencia: +%d\n", item->arma->inteligencia);
            else printf("        Inteligencia: %d\n", item->arma->inteligencia);

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

        printf("->  %s\n", item->armadura->nombre);

        if(item->armadura->puntosDefensa != 0){

            if(item->armadura->puntosDefensa > 0) printf("        Puntos de defensa: +%.1f", item->armadura->puntosDefensa);
            else printf("        Puntos de defensa: %.1f", item->armadura->puntosDefensa);

        }

        if(item->armadura->resistenciaMagica != 0){

            if(item->armadura->resistenciaMagica > 0) printf("        Resistencia Magica: +%.1f", item->armadura->resistenciaMagica);
            else printf("        Resistencia Magica: %.1f", item->armadura->resistenciaMagica);

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

        printf("        Puntos de vida: +%.1f", item->pocion->puntosDeVida);

    }

}

void verOpcionesDelObjeto(Item * item, int pos, Personaje * personaje, bool hayArma, bool hayArmadura, Item ** objetosEquipados, int lenghtObjetosEquipados){

    char key;
    int opcion = 1;

    int i;

    do{

        clrscr();

        if (strcmp(item->tipo, "Arma") == 0){

            printf("    %s\n", item->arma->nombre);

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

                if(item->arma->ataqueCriticoCuerpo > 0) printf("        Ataque Critico a Cuerpo: %.1f\n", item->arma->ataqueCriticoCuerpo);
                printf("        Ataque Critico a Cuerpo: %.1f\n", item->arma->ataqueCriticoCuerpo);

            }

            if(item->arma->ataqueMagico != 0){

                if(item->arma->ataqueMagico > 0)  printf("        Ataque Magico: %.1f\n", item->arma->ataqueMagico);
                printf("        Ataque Magico: %.1f\n", item->arma->ataqueMagico);

            }

            if(item->arma->fuerza != 0){

                if(item->arma->fuerza > 0) printf("        Fuerza: +%d\n", item->arma->fuerza);
                else printf("        Fuerza: %d\n", item->arma->fuerza);

            }

            if(item->arma->agilidad != 0){

                if(item->arma->agilidad > 0) printf("        Agilidad: +%d\n", item->arma->agilidad);
                else printf("        Agilidad: %d\n", item->arma->agilidad);

            }

            if(item->arma->vitalidad != 0){

                if(item->arma->vitalidad > 0) printf("        Vitalidad: +%d\n", item->arma->vitalidad);
                else printf("        Vitalidad: %d\n", item->arma->vitalidad);

            }

            if(item->arma->inteligencia != 0){

                if(item->arma->inteligencia > 0) printf("        Inteligencia: +%d\n", item->arma->inteligencia);
                else printf("        Inteligencia: %d\n", item->arma->inteligencia);

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

            printf("    %s\n", item->armadura->nombre);

            if(item->armadura->puntosDefensa != 0){

                if(item->armadura->puntosDefensa > 0) printf("        Puntos de defensa: +%.1f", item->armadura->puntosDefensa);
                else printf("        Puntos de defensa: %.1f", item->armadura->puntosDefensa);

            }

            if(item->armadura->resistenciaMagica != 0){

                if(item->armadura->resistenciaMagica > 0) printf("        Resistencia Magica: +%.1f", item->armadura->resistenciaMagica);
                else printf("        Resistencia Magica: %.1f", item->armadura->resistenciaMagica);

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

            printf("        Puntos de vida: +%.1f", item->pocion->puntosDeVida);
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
        if(opcion == 2) printf("->  Botar\n");
        else printf("     Botar\n");
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

            if(personaje->vidaActual == personaje->vidaMaxima){

                printf("\nTu vida ya se encuentra llena");

            }
            else if ( (personaje->vidaActual + item->pocion->puntosDeVida) >= personaje->vidaMaxima ){

                personaje->vidaActual = personaje->vidaMaxima;

            }
            else{

                personaje->vidaActual = personaje->vidaActual + item->pocion->puntosDeVida;

            }

        }
        else{

            if( strcmp(item->tipo, "Arma") == 0 ){

                if( item->equipado == true ){

                    desequiparArma(item, personaje);

                }
                else{

                    if(hayArma == true){

                        //se busca el arma equipada y se quita
                        for (i = 0 ; i < lenghtObjetosEquipados; i++){

                            if( strcmp(objetosEquipados[i]->tipo, "Arma") == 0 ){

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
                        for (i = 0 ; i < lenghtObjetosEquipados; i++){

                            if( strcmp(objetosEquipados[i]->tipo, "Armadura") == 0 ){

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

            if( strcmp(item->tipo, "Arma") == 0 ) desequiparArma(item, personaje);
            else desequiparArmadura(item, personaje);

            printf(" Has tirado el objeto.");

        }
        else{

            printf("\nHas tirado el objeto.");

        }

        personaje->inventario[pos] = NULL;

    }
    else if (opcion == 3) return;

    printf("\n\n");
    system("pause");
    return;

}

void abrirInventario(Personaje * personaje){

    Item ** objetosEquipados = (Item **) calloc (5, sizeof(Item *));
    int opcion = 1;
    char key;
    bool hayObjetos;
    bool hayArma = false;
    bool hayArmadura = false;
    int i;
    int cont2;

    do{

        clrscr();

        int cont = 0;
        hayObjetos = false;

        for (i = 0 ; i < 5 ; i++){

            if(personaje->inventario[i] != NULL && personaje->inventario[i]->equipado == true){

                hayObjetos = true;
                break;

            }

        }

        if(hayObjetos == true){

            cont = 0;

            for (i = 0 ; i < 5 ; i++){

                if(personaje->inventario[i] != NULL && personaje->inventario[i]->equipado == true){

                    if( strcmp(personaje->inventario[i]->tipo, "Arma") == 0 ) hayArma = true;
                    else if( strcmp(personaje->inventario[i]->tipo, "Armadura") == 0 ) hayArmadura = true;

                    objetosEquipados[cont] = personaje->inventario[i];
                    cont++;

                }

            }

        }

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

                mostrarObjeto(personaje->inventario[0]);

            }
            else printf("    %s\n", personaje->inventario[0]->nombre);

        }

        if(personaje->inventario[1] == NULL){

            if (opcion == 2) printf("->  Vacio\n");
            else printf("    Vacio\n");

        }
        else{

            if(opcion == 2){

                mostrarObjeto(personaje->inventario[1]);

            }
            else printf("    %s\n", personaje->inventario[1]->nombre);

        }

        if(personaje->inventario[2] == NULL){

            if (opcion == 3) printf("->  Vacio\n");
            else printf("    Vacio\n");

        }
        else{

            if(opcion == 3){

                mostrarObjeto(personaje->inventario[2]);

            }
            else printf("    %s\n", personaje->inventario[2]->nombre);

        }

        if(personaje->inventario[3] == NULL){

            if (opcion == 4) printf("->  Vacio\n");
            else printf("    Vacio\n");

        }
        else{

            if(opcion == 4){

                mostrarObjeto(personaje->inventario[3]);
            }
            else printf("    %s\n", personaje->inventario[3]->nombre);

        }

        if(personaje->inventario[4] == NULL){

            if (opcion == 5) printf("->  Vacio\n");
            else printf("    Vacio\n");

        }
        else{

            if(opcion == 5){

                mostrarObjeto(personaje->inventario[4]);

            }
            else printf("    %s\n", personaje->inventario[4]->nombre);

        }

        printf("\n\nPresione enter para ver las opciones del objeto.\n");
        printf("Presione i para cerrar el inventario.");

        do{

            key = getch();

        }while(key != 72 && key != 80 && key != 13 && key != 105);

        switch(key){
            case 72: if(opcion == 1) opcion = 5;
                    else opcion--;
                break;
            case 80: if(opcion == 5) opcion = 1;
                    else opcion++;
                break;
        }

        if(key == 105) break;

        if(key == 13 && personaje->inventario[opcion - 1]){

            verOpcionesDelObjeto(personaje->inventario[opcion - 1], opcion - 1, personaje, hayArma, hayArmadura, objetosEquipados, cont);

        }

    }while(1);

}

void abrirEstadisticas(Personaje * personaje){

    int opcion = 1;
    char key;

    do{

        clrscr();
        printf("Estadisticas: \n\n");
        printf("    Nombre: %s                                         Puntos de habilidad: %d\n", personaje->nombre, personaje->puntosDeHabildad);
        printf("    Vida Actual: %.1f / %.1f\n", personaje->vidaActual, personaje->vidaMaxima);
        printf("    Nivel: %d\n\n", personaje->nivel);

        if(personaje->puntosDeHabildad == 0){

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
        printf("\nPresione e para cerrar las estadisticas");
        printf("\nPresione enter para aumentar sus estadisticas");

        do{
           key  = getch();
        }while(key != 72 && key != 80 && key != 13 && key != 101);

        if(key == 101) break;

        switch(key){
            case 72: if(opcion == 1) opcion = 4;
                    else opcion--;
                break;
            case 80: if(opcion == 4) opcion = 1;
                    else opcion++;
                break;
        }

        if(key == 13){

            if(personaje->puntosDeHabildad == 0){

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
                    actualizarStats(personaje);
                    personaje->puntosDeHabildad--;

                }
                else if(opcion == 2){

                    personaje->agilidad++;
                    actualizarStats(personaje);
                    personaje->puntosDeHabildad--;

                }
                else if(opcion == 3){

                    personaje->vitalidad++;
                    actualizarStats(personaje);
                    personaje->vidaActual = personaje->vidaActual + 6;
                    personaje->puntosDeHabildad--;

                }
                else{

                    personaje->inteligencia++;
                    actualizarStats(personaje);
                    personaje->puntosDeHabildad--;

                }

            }


        }

    }while(1);

}

Item * crearItem(HashTable * items, char * nombre, int opcion){

    Item * item = (Item *) malloc (sizeof(Item));

    if(opcion == 1){

        Arma * arma = (Arma *) malloc (sizeof(Arma));
        arma = searchHashTable(items, nombre);

        if(arma == NULL) return NULL;

        item->tipo = "Arma";
        item->nombre = arma->nombre;
        item->arma = arma;
        item->equipado = false;

        item->armadura = NULL;
        item->pocion = NULL;

    }
    else if(opcion == 2){

        Armadura * armadura = (Armadura *) malloc (sizeof(Armadura));
        armadura = searchHashTable(items, nombre);

        if(armadura == NULL) return NULL;

        item->tipo = "Armadura";
        item->nombre = armadura->nombre;
        item->armadura = armadura;
        item->equipado = false;

        item->arma = NULL;
        item->pocion = NULL;


    }
    else if(opcion == 3){

        Pocion * pocion = (Pocion *) malloc (sizeof(Pocion));
        pocion = searchHashTable(items, nombre);

        if(pocion == NULL) return NULL;

        item->tipo = "Pocion";
        item->nombre = pocion->nombre;
        item->pocion = pocion;
        item->equipado = false;

        item->arma = NULL;
        item->armadura = NULL;

    }

    return item;

}

int pelear(Personaje * personaje, Enemigo * enemigo){

    char key;
    int opcion;
    int turno;

    do{

        printf("-------------------------------------------------------------------------------------------");
        printf("                                       %s\n\n", enemigo->nombre);
        printf("                                       Vida: %.1f / %.1f\n\n\n\n", enemigo->vidaActual, enemigo->vidaMaxima);
        printf("                //aqui van las actualizaciones                    \n\n\n\n");
        printf("                                       %s\n\n", personaje->nombre);
        printf("                                          Nivel: %d\n\n", personaje->nivel);
        printf("                                       Vida: %.1f / %.1f", personaje->vidaActual, personaje->vidaMaxima);
        printf("                                       Exp: %d / %d", personaje->exp, personaje->expMaxima);
        printf("                                       Arma: %s", personaje->inventario->);



    }



}

void nuevaPartida(HashTable * armas, HashTable * armaduras, HashTable * pociones, HashTable * enemigos){

    clrscr();

    printf("\nIndicanos tu nombre: ");
    char nombreJugador[20];
    scanf("%[^\n]s",nombreJugador);
    fflush(stdin);

    Personaje * personaje = crearPersonaje(nombreJugador);
    clrscr();

    char texto[50] = "Aqui comienza tu aventura ";
    strcat(texto, nombreJugador);
    strcat(texto, "!");

    size_t len = strlen(texto);

    int i;
    for (i = 0 ; i < len ; i++){
        Sleep(18);
        printf("%c", texto[i]);

    }

    Sleep(1100);
    clrscr();

    //mostrarHistoria(2,6);

    Item * item = crearItem(armas, "Katana", 1);

    personaje->inventario[0] = item;

    item = crearItem(armaduras, "Poleron Suprim", 2);

    personaje->inventario[2] = item;

    item = crearItem(armas, "Espada", 1);

    personaje->inventario[4] = item;

    item = crearItem(pociones, "Pocion Mediana", 3);

    personaje->inventario[5] = item;

    char key;
    int opcion = 1;

    do{

        clrscr();

        mostrarHistoriaSinPausas(5,6);
        printf("\n");

        if(opcion == 1) printf("->  Pelear contra el monstruo\n");
        else printf("     Pelear contra el monstruo\n");
        if(opcion == 2) printf("->  Pasar por la puerta a tu derecha\n");
        else printf("     Pasar por la puerta a tu derecha\n");

        printf("\n\nPresione i para abrir el inventario");
        printf("\nPresione e para abrir las estadisticas");

        do{
           key  = getch();
        }while(key != 72 && key != 105 && key != 80 && key != 13 && key != 73 && key != 101);

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
            case 101: abrirEstadisticas(personaje);

        }

        if(key == 13) break;

    }while(1);

    FILE * save = fopen("save.csv", "w");
    fprintf(save,"%d", 1);

    Enemigo * enemigo = searchHashTable(enemigos, "Slime");

    if(opcion == 1){

        if ( pelear(personaje, enemigo) == 0 ){

            printf("\nperdiste\n");
            return;

        }


    }

    return;

}

void mostrarHistoria (int primeraLinea, int ultimaLinea){
    FILE * fp = fopen("prueba.txt", "r");
    int i;
    size_t len;
    int leidas=0;
    int n;
    char linea[1024];
    char key;

    while(fgets(linea, 1023, fp) != NULL){
        leidas++;
        len = strlen(linea);
        if (leidas >= primeraLinea){

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
                    else if(linea[i] == '.') Sleep(450);

                }

            }

        Sleep(450);

        }

        if (leidas == ultimaLinea) break;

    }

    fclose(fp);
}

void mostrarHistoriaSinPausas (int primeraLinea, int ultimaLinea){
    FILE * fp = fopen("prueba.txt", "r");
    int leidas=0;
    int n, i;
    size_t len;
    char linea[1024];

    while(fgets(linea, 1023, fp) != NULL){
        leidas++;
        if (leidas >= primeraLinea){

             len = strlen(linea);

            for(n = 0 ; n < 5 ; n++){

                if(linea[n] == '/') break;

            }

            for(i = n + 1 ; i < len ; i++){

                printf("%c", linea[i]);

            }

        }

        if (leidas == ultimaLinea) break;

    }

    fclose(fp);
}
