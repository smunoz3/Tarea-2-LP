#include <stdio.h>
#include <stdlib.h>
#include "Tablero.c"
#include "Tablero.h"

int main() {
    IniciarTablero(7);
    /* for(int i = 0;i<7;i++){
        for(int j=0;j<7;j++){
            printf(tablero[i][j]);
        } */
    printf("e\n");
    //int **celda = tablero[1][1]->vida;

    BorrarTablero();
    return 0;
}
// \
// gcc-11 test.c -o test
// ./test