#include "functions.h"
#include "conio2.h"

int main(){

    char key;
    int opcion = 1;

    HashTable * enemigos = createHashTable(50);
    HashTable * armas = createHashTable(50);
    HashTable * armaduras = createHashTable(50);
    HashTable * pociones = createHashTable(50);
    cargarEnemigos(enemigos);
    cargarArmas(armas);
    cargarArmaduras(armaduras);
    cargarPociones(pociones);

    do{

        clrscr();

        printf("\n     ANOTHER QUARENTINE RPG GAME\n\n");
        if(opcion == 1) printf("->  NOVO JOGO\n");
        else printf("     NOVO JOGO\n");
        if(opcion == 2)  printf("->  CARREGAR JOGO\n");
        else printf("     CARREGAR JOGO\n");
        if(opcion == 3) printf("->  IRTE A LA CHUCHINHA\n");
        else printf("     IRTE A LA CHUCHINHA\n");

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

        if(key == 13) break;

    }while(1);

    switch(opcion){

      case 1: nuevaPartida(armas, armaduras, pociones, enemigos);

    }

    system("pause");


    return 0;

}
