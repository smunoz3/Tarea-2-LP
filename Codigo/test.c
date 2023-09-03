#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tablero.c"
#include "Tablero.h"

int main() {
    IniciarTablero(2);
    int n;

    for(int i = 0;i<dimension; i++){
        for(int j = 0;j<dimension;j++){
            printf("%p",&tablero[i][j]);
            printf("uno \n");
            printf("\n");
            struct Tierra *puntero = (struct Tierra*) tablero[i][j];
            puntero = tablero[i][j];
            printf("%p",puntero);
            printf("dos\n");
            printf("\n");
            struct Tierra p = *puntero; 
            printf("%d",p.vida);
            printf("\n");
        }
        printf("\n");
    }
    
    scanf("%d",&n);
    //BorrarTablero();
    return 0;
}
// \
// gcc-11 test.c -o test
// ./test



/*
temp 
if (tablero == NULL){
        exit(1);
    }
    for(int i = 0;i<n; i++){
        tablero[i]=malloc(n* sizeof(struct Tierra*));
        if (tablero[i] == NULL){
            exit(1);
        }
    }
    for(int i = 0;i<n; i++){
        for(int j = 0;j<n;j++){
            tablero[i][j]=malloc(n*sizeof(Tierra));
            if (tablero[i][j] == NULL){
                exit(1);
            }
            tablero;
            tablero[i][j]->vida = rand() % 3 +1;
            tablero[i][j]->es_tesoro = 0;
            printf("%d",tablero[i][j]->vida);
        }
        printf("\n");
    }
*/