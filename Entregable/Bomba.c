#include "Tierra.h"
#include "Bomba.h"
#include "Tablero.h"
#include <stdio.h>
#include <stdlib.h>

extern void ***tablero;
extern int dimension;

void TryExplotar(int fila, int columna) 
{
    if ((fila > dimension) || (columna > dimension))
        return;

    Celda *celda = (Celda *) tablero[fila][columna];
    if (celda->type == CELDA_TYPE_BOMBA) {
        Bomba *bomba = (Bomba *) celda->objeto;
        bomba->contador_turnos--;
        if ((bomba->contador_turnos == 0)) { //&& (bomba->explotar != NULL))
            (*bomba->explotar)(fila, columna); //explota bomba
            Tierra *tierra = (Tierra*) bomba->tierra_debajo;
            BorrarBomba(fila, columna);
        }
    }
    return;
}

void BorrarBomba(int fila, int columna) 
{
    if ((fila > dimension) || (columna > dimension))
        return;

    Celda *celda = (Celda *) tablero[fila][columna];
    if (celda->type == CELDA_TYPE_BOMBA) {
        Bomba *bomba = (Bomba *) celda->objeto;
        celda->objeto = bomba->tierra_debajo;
        celda->type = CELDA_TYPE_TIERRA;
        free(bomba);
    }

    return;
}

void ExplosionPunto(int fila, int columna){
    Celda *celda = (Celda *) tablero[fila][columna];
    if (celda->type == CELDA_TYPE_BOMBA){
        Bomba *bomba = (Bomba *) celda->objeto;
        Tierra *tierra = (Tierra *) bomba->tierra_debajo;
        tierra->vida = 0; 
    }
    return;
}

void ExplosionX(int fila, int columna){
    int fila_d,columna_d;
    Celda *celda = (Celda *) tablero[fila][columna];
    if (celda->type == CELDA_TYPE_BOMBA){
        Bomba *bomba = (Bomba *) celda->objeto;
        Tierra *tierra = (Tierra *) bomba->tierra_debajo;
        tierra->vida--;
        if (tierra->vida <0){
            tierra->vida =0;
        }
    }

    for(int i =0;i<4;i++)
    {   
        if (i ==0){
            fila_d = (fila-1)%(dimension-1);
            columna_d = (columna-1)%(dimension-1);
        }
        else if(i ==1){
            fila_d = (fila-1)%(dimension-1);
            columna_d = (columna+1)%(dimension-1);
        }
        else if(i ==2){
            fila_d = (fila+1)%(dimension-1);
            columna_d = (columna-1)%(dimension-1);
        }
        else if(i ==3){
            fila_d = (fila+1)%(dimension-1);
            columna_d = (columna+1)%(dimension-1);
        }
        if (fila_d<0){
            fila_d = dimension-1;
        }
        if (columna_d<0){
            columna_d = dimension-1;
        }
        Celda *celda = (Celda *) tablero[fila_d][columna_d];

        if (celda->type == CELDA_TYPE_BOMBA){
            Bomba *bomba = (Bomba *) celda->objeto;
            Tierra *tierra = (Tierra *) bomba->tierra_debajo;
            tierra->vida--;
            if (tierra->vida <0){
                tierra->vida =0;
            }
        }
        else if (celda->type == CELDA_TYPE_TIERRA){
            Tierra *tierra = (Tierra *) celda->objeto;
            tierra->vida--;
            if (tierra->vida <0){
                tierra->vida =0;
            }
        }
    }
    return;
}