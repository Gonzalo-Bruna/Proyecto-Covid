#ifndef functions_h
#define functions_h

#include "clases.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

//hace una copia del char
char * _strdup (const char *s);

//lee un campo de un archivo csv
const char *get_csv_field (char * tmp, int i);

//recibe un puntero a char, muestra el texto letra por letra con cierta lentitud, utilizando la funcion sleep
void mostrarLetraPorLetra(char *);

void mostrarAccionPelea(char *);

//crea un personaje nuevo y lo retorna
Personaje * crearPersonaje(char[]);

//esta funcion que carga las armas del archivo armas.csv en una tabla hash
void cargarArmas(HashTable *);

//funcion que carga las armaduras del archivo armaduras.csv en una tabla hash
void cargarArmaduras(HashTable *);

//funcion que carga las pociones del archivo pociones.csv en una tabla hash
void cargarPociones(HashTable *);

//función que aumenta los puntos de nivel, actualiza tu vida maxima y
void subirNivel(Personaje *);

//equipa un arma, por lo que suma los stats del arma al personaje, además comprueba los requisitos para equipar
void equiparArma(Item *, Personaje *);

//desequipa un arma, por lo tanto resta los stats del arma al personaje
void desequiparArma(Item *, Personaje *);

//equipa una armadura y suma los stats al personajes, además comprueba los requisitos para equipar
void equiparArmadura(Item *, Personaje *);

//desequipa una armadura y resta los stats al personaje
void desequiparArmadura(Item *, Personaje *);

/* muestra las caracteristicas del item seleccionado, el segundo parametro, si recibe 1 muestra el objeto con una flecha (se abrió
 dentro del inventario, si es 2, se muestra sin la flecha (se abrió desde la tienda))
 */
void mostrarObjeto(Item *, int);

//muestra las opciones de un objeto (equipar, utilizar, entre otras)
void verOpcionesDelObjeto(Item *, int, Personaje *);

//función que abre el inventario
void abrirInventario(Personaje *);

void abrirEstadisticas(Personaje *);

void mostrarOpcionesObjetoTienda(Item *, Personaje *);

void abrirTienda(Personaje *, char *, HashTable *, HashTable *, HashTable *);

/* crea un item, proporcionado por la tabla hash (púede ser arma, armadura o pocion)
   si es que el tercer parametro es 1, se busca crear un arma, si el parmametro es 2 una amardura, si es 3 una pocion */
Item * crearItem(HashTable *, char *, int);

//crea una nueva partida
void nuevaPartida(HashTable *, HashTable *, HashTable *, HashTable *);

void mostrarHistoria (int, int);

void mostrarHistoriaSinPausas (int, int);


#endif // functions_h
