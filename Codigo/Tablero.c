#include "Tierra.h"
#include "Tablero.h"
#include "Bomba.h"


void*** tablero;
int dimension;

void IniciarTablero(int n){
    dimension = n;
    srand(time(NULL));

    tablero = (void***)malloc(n * sizeof(void**));
    for(int i = 0;i<n;i++){
        tablero[i] = (void**)malloc(n * sizeof(void*));
    }

    
    
    for(int i = 0;i<n; i++){
        for(int j = 0;j<n;j++){
            tablero[i][j] = (void*)malloc(sizeof(void));
            
            struct Tierra terra;
            //terra.vida = 2;
            printf("%d",terra.vida);
            
            printf("\n");
            //terra.es_tesoro = 0;


            tablero[i][j]= &terra;
            // printf("%p",&tablero[i][j]);
            // printf("\n");
        }

    }
    for(int i = 0;i<n; i++){
        for(int j = 0;j<n;j++){
            tablero[i][j];
        }
    }
    printf("%p\n",tablero[1][0]);

    printf("fin iniciar tablero \n");
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
            free(tablero[i][j]);
        }
    }
    for(int i = 0;i<dimension;i++){
        free(tablero[i]);
    }
    free(tablero);
    return;
}