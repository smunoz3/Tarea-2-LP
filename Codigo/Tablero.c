#include "Tierra.h"
#include "Tablero.h"
#include "Bomba.h"

void*** tablero;
int dimension;

void IniciarTablero(int n){
    //struct Tierra *tierra1;
    //tierra1->vida = 1;
    dimension = n;
    struct Tierra ***tablero = malloc(n* sizeof(struct Tierra**));
    if (tablero == NULL){
        perror("error memoria");
        exit(1);
    }
    for(int i = 0;i<n; i++){
        tablero[i]=malloc(n* sizeof(struct Tierra*));
        if (tablero[i] == NULL){
            perror("error memoria");
            exit(1);
        }
    }
    for(int i = 0;i<n; i++){
        for(int j = 0;j<n;j++){
            tablero[i][j]=malloc(n*sizeof(Tierra));
            if (tablero[i][j] == NULL){
                perror("error memoria");
                exit(1);
            }
            tablero[i][j]->vida = 1;
            tablero[i][j]->es_tesoro = 0;
        }
    }
    return;
}

void PasarTurno(){
    // Su codigo
    return;
}


void ColocarBomba(Bomba* b, int fila, int columna){
    // Su codigo
    return;
}


void MostrarTablero(){
    // Su codigo
    return;
}


void MostrarBombas(){
    // Su codigo
    return;
}


void VerTesoros(){
    // Su codigo
    return;
}


void BorrarTablero(){
    for(int i = 0;i<dimension; i++){
        for(int j = 0;j<dimension;j++){
            if (tablero[i][j] == NULL){
                printf("ERROR");
            }
            free(tablero[i][j]);
        }
        free(tablero[i]);
    }
    free(tablero);
    return;
}