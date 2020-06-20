#include <stdbool.h>

typedef struct Arma{

    char * nombre;

    float ataqueFisico;
    float ataqueDistancia;
    float ataqueCriticoDistancia;
    float ataqueCriticoCuerpo;
    float ataqueMagico;

    int fuerza;
    int agilidad;
    int vitalidad;
    int inteligencia;

    int requisitoMinimoFuerza;
    int requisitoMinimoAgilidad;
    int requisitoMinimoVitalidad;
    int requisitoMinimoInteligencia;

} Arma;

typedef struct Armadura{

    char * nombre;

    float puntosDefensa;
    float resistenciaMagica;

    int requisitoMinimoFuerza;
    int requisitoMinimoAgilidad;
    int requisitoMinimoVitalidad;
    int requisitoMinimoInteligencia;

} Armadura;

typedef struct Pocion{

    char * nombre;
    float puntosDeVida;

} Pocion;

typedef struct Item{

    char * nombre;
    Arma * arma;
    Armadura * armadura;
    Pocion * pocion;
    char * tipo;
    bool equipado;

} Item;

typedef struct Personaje{

    char nombre[20];

    int fuerza;
    int agilidad;
    int vitalidad;
    int inteligencia;

    int nivel;
    int puntosDeHabildad;

    //fuerza
    float ataqueFisico;
    //agilidad
    float ataqueDistancia;
    float ataqueCriticoDistancia;
    float ataqueCriticoCuerpo;
    //vitalidad
    float vidaMaxima;
    float vidaActual;
    //inteligencia
    float ataqueMagico;

    float puntosDefensa;
    float resistenciaMagica;

    int exp;
    int expMaxima;
    int oro;

    //arreglo de items en la mochila
    Item ** inventario;

} Personaje;

typedef struct Enemigo{

    char * nombre;

    float ataqueFisico;

    float ataqueDistancia;
    float ataqueMagico;

    float ataqueCriticoDistancia;
    float ataqueCriticoCuerpo;

    float vidaMaxima;
    float vidaActual;

    float puntosDefensa;
    float resistenciaMagica;

}Enemigo;

