#include <stdbool.h>

typedef struct Arma{

    char * nombre;

    float ataqueFisico;
    float ataqueDistancia;
    float ataqueCriticoDistancia;
    float ataqueCriticoCuerpo;
    float ataqueMagico;

    int requisitoMinimoFuerza;
    int requisitoMinimoAgilidad;
    int requisitoMinimoVitalidad;
    int requisitoMinimoInteligencia;

} Arma;

typedef struct Armadura{

    char * nombre;

    float puntosDefensa;

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
    bool comprado;
    int precio;

} Item;

typedef struct Personaje{

    char nombre[20];

    int fuerza;
    int agilidad;
    int vitalidad;
    int inteligencia;

    int nivel;
    int puntosDeHabilidad;

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

    int exp;
    int expMaxima;

    int oro;

    //arreglo de items en la mochila
    Item ** inventario;

} Personaje;

typedef struct Enemigo{

    char * nombre;

    float ataque;

    float ataqueCritico;

    float vidaMaxima;
    float vidaActual;

    float puntosDefensa;
    float resistenciaMagica;

}Enemigo;

