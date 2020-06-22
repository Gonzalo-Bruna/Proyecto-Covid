#ifndef functions_h
#define functions_h

#include "clases.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

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

//actualiza los stats del personaje, como cuando sube de nivel y mejora sus habilidades
void actualizarStats(Personaje *);

//funci�n que aumenta los puntos de nivel, actualiza tu vida maxima y
void subirNivel(Personaje *);

//equipa un arma, por lo que suma los stats del arma al personaje, adem�s comprueba los requisitos para equipar
void equiparArma(Item *, Personaje *);

//desequipa un arma, por lo tanto resta los stats del arma al personaje
void desequiparArma(Item *, Personaje *);

//equipa una armadura y suma los stats al personajes, adem�s comprueba los requisitos para equipar
void equiparArmadura(Item *, Personaje *);

//desequipa una armadura y resta los stats al personaje
void desequiparArmadura(Item *, Personaje *);

//muestra las caracteristicas del item seleccionado
void mostrarObjeto(Item *);

//muestra las opciones de un objeto (equipar, utilizar, entre otras)
void verOpcionesDelObjeto(Item *, int, Personaje *, bool, bool, Item **, int);

//funci�n que abre el inventario
void abrirInventario(Personaje *);

void abrirEstadisticas(Personaje *);

/* crea un item, proporcionado por la tabla hash (p�ede ser arma, armadura o pocion)
   si es que el tercer parametro es 1, se busca crear un arma, si el parmametro es 2 una amardura, si es 3 una pocion */
Item * crearItem(HashTable *, char *, int);

//crea una nueva partida
void nuevaPartida(HashTable *, HashTable *, HashTable *, HashTable *);

#endif // functions_h
