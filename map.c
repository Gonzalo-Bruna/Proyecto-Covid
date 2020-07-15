#include "map.h"

HashTable * createHashTable(long size) {
    HashTable * ht = (HashTable *) malloc(sizeof(HashTable));
    ht->buckets = (Pair **) calloc(size, sizeof(Pair *));
    ht->count = 0;
    ht->size = size;
    ht->current = -1;
    ht->loadFactor = (long)ceil(size * 0.77);
    return ht;
}

Pair * createPair(const char * key, void * value){
    Pair * par = (Pair *) malloc (sizeof(Pair));
    par->key = key;
    par->value = value;
    return par;
}

unsigned long stringHash(const char * key){

    unsigned long num = 5381;
    int i;
    size_t length = strlen(key);

    for (i = 0 ; i < length ; i++){

        num *= 33;
        num += key[i];

    }

    return num;
}

long linearProbing(HashTable * table, const char * key) {

    long pos = stringHash(key) % table->size;
    if (table->buckets[pos] == NULL) return pos;

    while(table->buckets[pos] && strcmp(key, table->buckets[pos]->key) != 0){

        if (pos == table->size - 1) pos = 0;
        else pos++;

    }

    return pos;
}

void insertHashTable(HashTable * table, const char * key, void * value) {

    if (table == NULL) return;

    long pos = linearProbing(table, key);

    if ( table->buckets[pos] == NULL || table->buckets[pos]->value == NULL ){

        table->buckets[pos] = createPair(key, value);
        table->count++;

    }

    if (table->count > table->loadFactor) enlarge(table);

}

void * searchHashTable(HashTable * table, const char * key) {

    long pos = linearProbing(table, key);

    if (table->buckets[pos] == NULL || table->buckets[pos]->value == NULL) return NULL;

    table->current = pos;

    return table->buckets[pos]->value;

}

void * eraseKeyHashTable(HashTable * table, const char * key) {

    long pos = linearProbing(table, key);

    if (table->buckets[pos] == NULL){

        return NULL;

    }

    void * value = table->buckets[pos]->value;
    table->buckets[pos]->value = NULL;

    return value;
}

void enlarge(HashTable * table) {

    if (!table) return;

    //guardamos un puntero al arreglo antiguo y su tamaño, y una variable newSize que vale oldSize * 2

    long oldSize = table->size;
    long newSize = oldSize * 2;
    Pair ** aux = table->buckets;

    //creamos un nuevo arreglo

    Pair ** newArray = (Pair **) calloc (newSize, sizeof(Pair *));
    table->buckets = newArray;

    //reinicializamos los elementos count y size de la tabla, además asignamos su nuevo loadFactor

    table->count = 0;
    table->size = newSize;
    table->loadFactor = (long) ceil(newSize * 0.77);

    int i;

    for (i = 0 ; i < oldSize ; i++){

        if (aux[i]){

            insertHashTable(table, aux[i]->key, aux[i]->value);
            free(aux[i]);

        }

    }

    free(aux);
}

void * firstHashTable(HashTable * table) {

    if(!table) return NULL;

    int i = 0;

    while(table->buckets[i] == NULL || table->buckets[i]->value == NULL){

        i++;
        if ( i == table->size) return NULL;

    }


    table->current = i;
    return table->buckets[i]->value;
}

void * nextHashTable(HashTable * table) {

    if (!table  || table->current == ( table->size - 1 )) return NULL;

    int i = table->current + 1;

    while(table->buckets[i] == NULL || table->buckets[i]->value == NULL){

        if (i == (table->size - 1) ) break;
        i++;

    }

    if (table->buckets[i] == NULL || table->buckets[i]->value == NULL ) return NULL;

    table->current = i;

    return table->buckets[i]->value;

}

void deleteHashTable(HashTable * table){

    int i;

    for (i = 0 ; i < table->size ; i++){
        if(table->buckets[i] != NULL) free(table->buckets[i]);
    }

    free(table->buckets);
    free(table);

}
