#ifndef TABLERO_H
#define TABLERO_H
#include "Tierra.h"
#include "Bomba.h"

#define CELDA_TYPE_TIERRA 1
#define CELDA_TYPE_BOMBA  2

typedef struct Celda {
    int type;
    void *objeto;
} Celda;

extern void*** tablero;
extern int dimension; // 7 en 7x7, 10 en 10x10, 12 en 12x12

void IniciarTablero(int n);
void PasarTurno();
void ColocarBomba(Bomba* b, int fila, int columna);
void MostrarTablero();
void MostrarBombas();
void BorrarTablero();
void VerTesoros();
int FinDelJuego();

#endif