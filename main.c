#include "functions.h"
#include "conio2.h"

int main(){

    char key;
    int opcion = 1;

    HashTable * armas = createHashTable(50);
    HashTable * armaduras = createHashTable(50);
    HashTable * pociones = createHashTable(50);
    HashTable * enemigos = createHashTable(50);
    cargarArmas(armas);
    cargarArmaduras(armaduras);
    cargarPociones(pociones);
    cargarEnemigos(enemigos);

    do{

        clrscr();

        printf("ANOTHER QUARENTINE RPG GAME\n\n");
        if(opcion == 1) printf("->  NUEVO JUEGO\n");
        else printf("     NUEVO JUEGO\n");
        if(opcion == 2)  printf("->  CARGAR PARTIDA\n");
        else printf("     CARGAR PARTIDA\n");
        if(opcion == 3) printf("->  SALIR\n");
        else printf("     SALIR\n");

        do{

            key = getch();

        }while(key != 72 && key != 80 && key != 13);

        switch(key){
            case 72: if(opcion == 1) opcion = 3;
                    else opcion--;
                break;
            case 80: if(opcion == 3) opcion = 1;
                    else opcion++;
                break;
        }

        if(key == 13){

            switch(opcion){

              case 1: nuevaPartida(armas, armaduras, pociones, enemigos);

            }


            if(opcion == 3){

                opcion = 1;

                do{
                    clrscr();

                    printf("Estas seguro que deseas salir :c?\n\n");
                    if(opcion == 1) printf("->  SI\n");
                    else printf("     SI\n");
                    if(opcion == 2)  printf("->  NO\n");
                    else printf("     NO\n");

                    do{

                        key = getch();

                    }while(key != 72 && key != 80 && key != 13);

                    switch(key){
                        case 72: if(opcion == 1) opcion = 2;
                                else opcion--;
                            break;
                        case 80: if(opcion == 2) opcion = 1;
                                else opcion++;
                            break;
                    }

                    if(key == 13) break;

                }while(1);

                if(opcion == 1) break;
                else opcion = 1;

            }

        }

    }while(1);


    clrscr();
    mostrarLetraPorLetra("Nos veremos en la siguiente...");
    Sleep(1000);

    return 0;

}
