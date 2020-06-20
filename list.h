#ifndef LIST_H
#define LIST_H

//definición de structs de la lista

typedef struct Node{

    void * data;
    struct Node* next;
    struct Node* prev;

}Node;

typedef struct List{

    Node * head;
    Node * tail;
    Node * current;
    int size;

}List;

//Crea una lista y la retorna inicializada
List * createList();

//Crea un nodo y lo retorna inicializado
Node * createNode(void * data);

//Operaciones de la lista

//retorna el primer dato de la lista
void * first(List *);

//retorna el dato del nodo siguiente al current
void * next(List *);

//inserta al final de la lista
void pushBack(List *, void*);

//insterta al principio de la lista
void pushFront(List *, void*);

//elimina el ultimo elemento de la lista
void popBack(List *);

//elimina el primer elemento de la lista
void popFront(List *);

//elimina el elemento actual (current)
void popCurrent(List *);

#endif // LIST_H
