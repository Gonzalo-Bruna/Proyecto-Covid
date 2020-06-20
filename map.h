#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct Pair{

    const char * key; // Cadena
    void * value; // Puntero al valor

} Pair;

typedef struct HashTable{

    Pair ** buckets; // Arreglo de punteros a Pair
    long count; // Cantidad de datos no nulos
    long size; // Tamaño del arreglo
    long current; // Variable para poder recorrer el arreglo
    long loadFactor; // Factor de carga del arreglo

} HashTable;

/* Crea una tabla de hash, inicializando buckets con NULL, count en 0, size en el valor pasado por parametro
current - 1, y load factor en el procentaje de ocupacion con respecto a size */
HashTable * createHashTable(long);

/* Crea un dato tipo Pair inicializado con el key y el value pasado por parametro */
Pair * createPair(const char *, void *);

/* stringHash recibe una variable de tipo char y retorna una clave (sin aplicar hashing para calcular su posición) */
unsigned long stringHash(const char *);

/* linearProbing devuelve la posición en donde insertar un dato con clave key, si la posición está ocupada recorre linealmente
hasta encontrar una posición que esté vacía */
long linearProbing(HashTable *, const char *);

/* inserta en la tabla "table" el dato con su valor y clave  */
void insertHashTable(HashTable *, const char *, void *);

/* Busca un dato y lo retorna si es que lo encuentra, en caso contrario retorna NULL */
void * searchHashTable(HashTable *, const char *);

/* Elimina un dato de table "table", deja la casilla en donde se encontraba en NULL, también retorna el dato */
void * eraseKeyHashTable(HashTable *, const char *);

/* En caso de que la tabla hash supere el loadFactor (factor de carga) se encarga de duplicar su tamaño para evitar colisiones y mejorar su rendimiento */
void enlarge(HashTable *);

// Retorna el valor del primer dato no nulo de la tabla hash
void * firstHashTable(HashTable *);

// Retorna el valor del dato no nulo siguiente al current
void * nextHashTable(HashTable *);

#endif // MAP_H
