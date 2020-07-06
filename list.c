#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

//funciones de creacion de listas y nodos

List * createList(){

    List * list = (List *) malloc (sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    list->size = 0;
    return list;

}

Node * createNode(void * data){

    Node * node = (Node *) malloc (sizeof(Node));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;

}

void * returnNodeData(Node * node){

    return node->data;

}

Node * retornarNodoCabeza(List * list){

    return list->head;

}

//funciones para interactuar con las listas

void * first(List * list){

    if(!list->head) return NULL;
    list->current = list->head;
    return list->head->data;

}

void * next(List * list){

    if(list && list->head && list->current && list->current->next){
        list->current = list->current->next;
        return list->current->data;
    }

    return NULL;

}

void pushBack(List * list, void* data){

    if( list == NULL ) return;

    Node * node =  createNode(data);

    if  (list->head){
        node->prev = list->tail;
        list->tail->next = node;
    }else{
        list->head = node;
    }

    list->tail = node;
    list->current = node;
    list->size++;

}

void pushFront(List * list, void* data){

    if(list == NULL) return;

    Node * node = createNode(data);

    if(list->head){
        list->head->prev = node;
        node->next = list->head;
    }
    else{
       list->tail = node;
    }

    list->head = node;
    list->current = node;
    list->size++;

}

void popBack(List * list){

    if(list == NULL || list->head == NULL) return;

    Node * aux = list->tail;

    if(list->head == list->tail){
        list->head = list->tail = list->current = NULL;
    }
    else{
        list->current = list->tail->prev;
        list->tail = list->tail->prev;
        list->tail->next = NULL;

    }

    list->size--;
    free(aux);

}

void popFront(List * list){

    if(list == NULL || list->head) return;

    Node * aux = list->head;

    if(list->head == list->tail){
        list->head = list->tail = list->current = NULL;
    }else{
        list->current = list->head->next;
        list->head = list->head->next;
        list->head->prev = NULL;
    }

    list->size--;
    free(aux);

}

void popCurrent(List * list){

    if(list == NULL || list->head == NULL || list->current == NULL) return;

    Node * aux = list->current;

    if(list->current == list->head){

        if(list->head == list->tail){
            list->tail = list->head = NULL;
        } else{

            list->head = list->head->next;
            list->head->prev = NULL;
        }
    } else if(list->current == list->tail){
        list->tail = list->tail->prev;
        list->tail->next = NULL;

    } else{
        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
    }

    list->current = aux->next;
    list->size--;
    free(aux);

}

