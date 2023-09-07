#include "Tierra.h"
#include "Bomba.h"
#include "Tablero.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ***tablero;
int dimension;

void IniciarTablero(int n)
{
    dimension = n;
    srand(time(0));

    tablero = (void ***)malloc(n * sizeof(void **));
    for (int i = 0; i < n; i++)
    {
        tablero[i] = (void **)malloc(n * sizeof(void *));
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            tablero[i][j] = (void *)malloc(sizeof(void *));
            
            Tierra *tierra = (Tierra *) malloc(sizeof(struct Tierra));
            tierra->vida = (rand() % 3) + 1;
            int random = (rand() % 100) +1;
            if (random <=5)
                tierra->es_tesoro = 1;
            else
                tierra->es_tesoro =0;
            Celda *celda = (Celda *) malloc(sizeof(struct Celda));
            celda->type = CELDA_TYPE_TIERRA;
            celda->objeto = tierra;

            tablero[i][j] = celda;
        }
    }

    return;
}

void PasarTurno()
{
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            Celda *celda = (Celda *) tablero[i][j];
            if (celda->type == CELDA_TYPE_BOMBA) {
                TryExplotar(i,j);
            }
        }
    }
    return;
}

void ColocarBomba(Bomba *b, int fila, int columna)
{
    if ((fila > dimension) || (columna > dimension))
        return;

    Celda *celda = (Celda *) tablero[fila-1][columna-1];
    if (celda->type == CELDA_TYPE_TIERRA) {
        Tierra *tierra = (Tierra *) celda->objeto;
        b->tierra_debajo = tierra;
        celda->type = CELDA_TYPE_BOMBA;
        celda->objeto = b;
    }

    return;
}

void MostrarTablero()
{
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            Celda *celda = (Celda *) tablero[i][j];
            if (celda->type == CELDA_TYPE_TIERRA) { 
                // Tierra 
                Tierra *tierra = (Tierra *) celda->objeto;
                if ((tierra->vida == 0) && (tierra->es_tesoro == 1))
                    printf("*");
                else 
                    printf("%d", tierra->vida);
            } else if (celda->type == CELDA_TYPE_BOMBA) {
                // Bomba
                printf("o");
            }
            if (j < (dimension - 1))
                printf(" | ");
        }
        printf("\n");
    }    
    return;
}

void MostrarBombas()
{
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            Celda *celda = (Celda *) tablero[i][j];
            if (celda->type == CELDA_TYPE_BOMBA) {
                Bomba *bomba = (Bomba *) celda->objeto;
                Tierra *tierra = (Tierra *) bomba->tierra_debajo;
                printf("Turnos para explotar: %d\n",bomba->contador_turnos);
                printf("Coordenada: %d %d\n", i+1, j+1);
                printf("Forma de explosión: ExplosionX\n");
                printf("Vida de la Tierra Debajo: %d\n", tierra->vida);
                printf("\n");
            }
        }
    }

    return;
}

void BorrarTablero()
{
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            Celda *celda = (Celda *) tablero[i][j];
            if (celda->type == CELDA_TYPE_BOMBA) {
                Bomba *bomba = (Bomba *) celda->objeto;
                free(bomba->tierra_debajo);
            }
            free(celda->objeto);
            free(tablero[i][j]);
        }
        free(tablero[i]);
    }
    free(tablero);
    return;
}

void VerTesoros()
{
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            Celda *celda = (Celda *) tablero[i][j];
            if (celda->type == CELDA_TYPE_BOMBA) {
                Bomba *bomba = (Bomba *) celda->objeto;
                Tierra *tierra = (Tierra *) bomba->tierra_debajo;
                if (tierra->es_tesoro == 1)
                    printf("*");
                else
                    printf("%d",tierra->vida);   
            }
            else if (celda->type == CELDA_TYPE_TIERRA){
                Tierra *tierra = (Tierra *) celda->objeto;
                if (tierra->es_tesoro ==1)
                    printf("*");
                else
                    printf("%d",tierra->vida);
            }
        if (j < (dimension - 1))
                printf(" | ");
        }
        printf("\n");   
    }
    printf("\n");
    return;
}

int FinDelJuego()
{
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            Celda *celda = (Celda *) tablero[i][j];
            if (celda->type == CELDA_TYPE_TIERRA) { 
                // Tierra 
                Tierra *tierra = (Tierra *) celda->objeto;
                if ((tierra->es_tesoro == 1) && (tierra->vida != 0))
                    return 0;
            } else if (celda->type == CELDA_TYPE_BOMBA) {
                Bomba *bomba =(Bomba *)celda->objeto;
                Tierra *tierra = (Tierra*)bomba->tierra_debajo;
                if ((tierra->es_tesoro == 1) && (tierra->vida != 0))
                    return 0;
            }
        }
    }
    return 1;
}