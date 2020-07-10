#ifndef functions_h
#define functions_h

#include "clases.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

/* FUNCIONES PARA USO GENERAL*/

//Realiza una copia del char pasado por parametro.
char * _strdup (const char *s);

//Lee un campo de un archivo csv.
const char *get_csv_field (char * tmp, int i);

/* FUNCIONES PARA MOSTRAR TEXTO EN PANTALLA */

//Recibe un puntero a char, muestra el texto letra por letra con cierta lentitud, utilizando la funcion sleep.
void mostrarLetraPorLetra(char *);

/*Esta función se encarga de mostrar el texto pasado por parametro, incluyendo algunos saltos de linea,
esto es para mostrar correctamente el texto en la función de pelea. */
void mostrarAccionPelea(char *);

/*Se encarga de mostrar la historia del archivo csv que creamos, el algoritmo muestra las lineas pasadas por parametro, por ejemplo,
si paso el 2 y el 6, mostrará desde la linea 2 a la 6 de manera lenta (como el texto de pokemon), si se apreta el espacio, se salta la "animación"*/
void mostrarHistoria (int, int);

/*Muestra el texto de las lineas pasadas por parametro, pero a diferencia de la función mostrarHistoria, esta lo hace sin ningún tipo de
"animación", solamente muestra el texto por pantalla.*/
void mostrarHistoriaSinPausas (int, int);

/* FUNCIONES DE CARGA DESDE ARCHIVOS CSV */

//Esta funcion que carga las armas del archivo armas.csv en una tabla hash.
void cargarArmas(HashTable *);

//Funcion que carga las armaduras del archivo armaduras.csv en una tabla hash.
void cargarArmaduras(HashTable *);

//Funcion que carga las pociones del archivo pociones.csv en una tabla hash.
void cargarPociones(HashTable *);

//Carga los enemigos del arhcivo enemigos.csv en una tabla hash.
void cargarEnemigos(HashTable *);

/* FUNCIONES DE CREACIÓN DE STRUCTS */

//Crea un personaje nuevo, inicializando los miembros del personaje y lo retorna.
Personaje * crearPersonaje(char[]);

/*Crea un item, proporcionado por la tabla hash (púede ser arma, armadura o pocion) que recibe por parametro, recibe el nombre del item
(para buscarlo en su respectiva tabla), y por último un número.
 Si es que el tercer parametro es 1, se busca crear un arma, si es 2 una amardura, si es 3 una pocion */
Item * crearItem(HashTable *, char *, int);

/* FUNCIONES NECESARIAS PARA LA LOGICA DEL JUEGO ( INVENTARIO, TIENDA, SUBIR NIVEL, EQUIPAR ITEMS ) */

//Función que aumenta los puntos de nivel, actualiza la vida maxima del personaje y muestra por pantalla los nuevos stats.
void subirNivel(Personaje *);

//Equipa un arma, suma los stats del arma al personaje, comprueba que el arma pueda ser equipada y que si había un arma equipada anteriormente.

void equiparArma(Item *, Personaje *);

//Desequipa un arma, por lo tanto resta los stats del arma al personaje.
void desequiparArma(Item *, Personaje *);

//Equipa una armadura y suma los stats al personajes, además comprueba los requisitos para equipar y si es que había una armadura equipada anteriormente.
void equiparArmadura(Item *, Personaje *);

//Desequipa una armadura, por lo tanto, resta los stats de la armadura al personaje.
void desequiparArmadura(Item *, Personaje *);

/*Muestra las caracteristicas del item seleccionado, el segundo parametro, si recibe 1 muestra el objeto con una flecha (se abrió
 dentro del inventario, si es 2, se muestra sin la flecha (se abrió desde la tienda)) esto con el fin de no crear una función exclusiva para la tienda.*/
void mostrarObjeto(Item *, int);

//Muestra las opciones de un objeto cuando se ve el inventario (equipar, utilizar, botar, etc).
void verOpcionesDelObjeto(Item *, int, Personaje *);

/*Función que abre el inventario, utiliza otras funciones como mostrarObjeto, para cumplir con su función correctamente.
 Muestra todo el inventario, si hay objetos vaciós muestra que está vacío, permite interactuar con las flechas y seleccionar objetos.*/
void abrirInventario(Personaje *);

/*Permite ver las estadísticas de un jugador (fuerza, agilidad, etc), incluyendo información del uso de cada una.
Además, permite interactuar con el teclado e ir moviendose, en caso de haber puntos de habilidad, se pueden aumentar en tiempo real las estadísticas.*/
void abrirEstadisticas(Personaje *);

/*muestra las opciones del objeto para la tienda (comprar y volver atrás), si el objeto es comprado, resta el oro y cambia
el booleano "compraado" del item a verdadero, así la función abrir tienda sabe si mostrar el nombre del objeto, o un texto que dice "comprado".*/
void mostrarOpcionesObjetoTienda(Item *, Personaje *);

/*Esta función lo que hace es abrir la tienda, cargar un archivo con objetos, mostrar los 12 objetos de la tienda, y usa la función
mostrarOpcionesObjetoTienda para mostrar las opciones y poder realizar compras, permite interactuar con los objetos
y además puedes moverte a tu inventario que se muestra más abajo presionando la letra i.*/
void abrirTienda(Personaje *, char *, HashTable *, HashTable *, HashTable *);

/* La función pelear recibe como parametro al personaje, y el enemigo con el que se va a enfrentar, utiliza un algoritmo que proporcionará
golpes criticos de manera random (dependiento de la probabilidad del enemigo y del personaje de dar golpes críticos), muestra los sucesos
en el medio de la pantalla, e indica si perdiste o ganaste.
Si ganas retorna 1, en caso contrario retorna 0.*/
int pelear(Personaje *, Enemigo *);

/*Funcion principal 1, se encarga de crear una nueva partida, mostrando la historia de manera lineal haciendo uso de
 las funciones definidas anteriormente. Recibe como parametro las 4 tablas hash correspondientes. */
void nuevaPartida(HashTable *, HashTable *, HashTable *, HashTable *);

void cargarPartida(HashTable *, HashTable *, HashTable *, HashTable *);

#endif // functions_h
