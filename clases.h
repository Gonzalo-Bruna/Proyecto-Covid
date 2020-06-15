typedef struct Clase{

    char nombre[10];
    int fuerza;
    int agilidad;
    int vitalidad;
    int inteligencia;

} Clase;

typedef struct Personaje{

    char nombre[20];

    Clase * clase;

    //fuerza
    float ataqueFisico;
    //agilidad
    int ataqueDistancia;
    int ataqueCriticoDistancia;
    float ataqueCriticoCuerpo;
    //vitalidad
    int vida;
    //inteligencia
    int ataqueMagico;

    int exp;


} Personaje;
