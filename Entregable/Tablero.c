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
    /*
    Entradas:
    n Tipo: entero
    Funcionamiento:
    Recibe el tamaño de la matriz que se quiere hacer y se guarda en dimension,
    en ***tablero se empieza a pedir memoria para hacer la matriz y hace que cada celda quede apuntando a una tierra,
    que esta tiene vida aleatoria entre 1-3 y un 0.5 de probabilidad de tener un tesoro  
    Salida:
    Nada
    */
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
    /*
    Entradas:
    Nada
    Funcionamiento:
    Recorre el tablero y si encuntra una bomba llama a TryExplotar
    Salida:
    Nada
    */
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
    /*
    Entradas:
    *b Tipo: puntero a bomba
    fila Tipo: entero
    columna Tipo: entero
    Funcionamiento:
    Va a la fila y columna y hace que el puntero de celda apunte a la bomba que recibió (*b), 
    cambia el tipo de celda y la bomba queda apuntando a la tierra que había antes
    Salida:
    Nada
    */
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
    /*
    Entradas:
    Nada
    Funcionamiento:
    Recorre el tablero y revisa de que tipo es la celda,
    si es tierra ve si hay tesoro y si este fue descubierto (vida de la tierra = 0) si fue descubierto imprime "*" 
    si no imprime cuanta vida tiene la tierra
    si celda es de tipo bomba imprime "o"
    Salida:
    Nada
    */
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            Celda *celda = (Celda *) tablero[i][j];
            if (celda->type == CELDA_TYPE_TIERRA) { 
                Tierra *tierra = (Tierra *) celda->objeto;
                if ((tierra->vida == 0) && (tierra->es_tesoro == 1))
                    printf("*");
                else 
                    printf("%d", tierra->vida);
            } 
            else if (celda->type == CELDA_TYPE_BOMBA) {
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
    /*
    Entradas:
    Nada
    Funcionamiento:
    Recorre el tablero y revisa si celda es de tipo bomba,
    de ser así imprime el contador de turnos, la fila y columna de donde se encuentra, 
    el tipo de explosión (que este siempre es X porque las bombas tipo punto explotan al momento de ser colocados)
    y por último la vida de la tierra que tiene debajo
    Salida:
    Nada
    */
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
    /*
    Entradas:
    Nada
    Funcionamiento:
    Recorre el tablero y revisa de que tipo es la celda,
    Si la celda es tipo bomba primero libera la memoria de la tierra que tiene debajo,
    luego libera la celda, si celda es tipo tierra libera directamente la celda y va liberando hacia arriba
    Salida:
    Nada
    */
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
            free(celda);
        }
        free(tablero[i]);
    }
    free(tablero);
    return;
}

void VerTesoros()
{
    /*
    Entradas:
    Nada
    Funcionamiento:
    Recorre el tablero y revisa de que tipo es la celda,
    Si la celda es tipo bomba revisa si tierra debajo tiene tesoro de tenerlo imprime "*"
    si celda es de tipo es tierra revisa directamente si tiene tesoro y de tenerlo imprime "*"
    en caso de que celda no tenga tesoro imprime la vida de la tiera
    Salida:
    Nada
    */
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
    /*
    Entradas:
    Nada
    Funcionamiento:
    Revisa la tierra en busca de los tesoros,
    en caso de haber tesoro revisa si la vida de la tierra es 0
    Si en todos los tesoros la vida de la tierra es 0 retornara 1
    Salida:
    0 o 1 ,si se termino el juego 1 de caso contrario 0
    */
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            Celda *celda = (Celda *) tablero[i][j];
            if (celda->type == CELDA_TYPE_TIERRA) { 
                Tierra *tierra = (Tierra *) celda->objeto;
                if ((tierra->es_tesoro == 1) && (tierra->vida != 0))
                    return 0;
            } 
            else if (celda->type == CELDA_TYPE_BOMBA) {
                Bomba *bomba =(Bomba *)celda->objeto;
                Tierra *tierra = (Tierra*)bomba->tierra_debajo;
                if ((tierra->es_tesoro == 1) && (tierra->vida != 0))
                    return 0;
            }
        }
    }
    return 1;
}