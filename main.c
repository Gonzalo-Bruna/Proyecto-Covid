#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

int main(){

    char key;
    int opcion = 1;

    do{

        system("cls");

        printf("JUEGO QLO\n\n");
        if(opcion == 1) printf("-> NOVO JOGO\n");
        else printf("   NOVO JOGO\n");
        if(opcion == 2) printf("-> CARREGAR JOGO\n");
        else printf("   CARREGAR JOGO\n");
        if(opcion == 3) printf("-> IRTE A LA CHUCHINHA\n");
        else printf("   IRTE A LA CHUCHINHA\n");

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

    //switch(opcion){

      //  case 1: nuevaPartida();

    //}


    system("pause");


    return 0;

}
