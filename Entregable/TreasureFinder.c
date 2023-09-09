#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tierra.h"
#include "Bomba.h"
#include "Tablero.h"
#include "Bomba.c"

int main(int argc, char const *argv[])
{
    int n,turno;
    turno = 1;
    
    printf("¡Bienvenido a TreasureFinder!\n");
    printf("Indique el tamaño del tablero a jugar:\n");
    printf("1.7x7  2.10x10  3.12x12\n");

    scanf("%d",&n);
    if(n==1){
        n = 7;
    }
    else if(n==2){
        n = 10;
    }
    else if(n==3){
        n = 12;
    }

    IniciarTablero(n);
    printf("Empezando juego... ¡listo!\n");
    printf("\n");
    while (1)
    {
        
        printf("Tablero (Turno %d)\n",turno);
        MostrarTablero();
        
        printf("Seleccione una accion: \n");
        printf("1.Colocar Bomba  2.Mostrar Bombas  3.Mostrar Tesoros \n");
        scanf("%d",&n);

        //Colocar Bomba
        if(n==1){
            printf("Indique coordenadas de la bomba \n");
            int fila,columna,tipo_bomba;
           
            printf("Fila: ");
            scanf("%d",&fila);
            printf("Columna: ");
            scanf("%d",&columna);
            printf("Indique forma en que explota la bomba \n");
            printf("1.Punto  2.X\n");
            scanf("%d",&tipo_bomba);
            printf("\n");
            if (tipo_bomba == 1){
                Bomba *bPunto = (Bomba *) malloc (sizeof(struct Bomba));
                bPunto->contador_turnos = 1;
                bPunto->explotar = &ExplosionPunto;
                ColocarBomba(bPunto, fila, columna);
            }
            else if (tipo_bomba == 2){
                Bomba *bX = (Bomba *) malloc (sizeof(struct Bomba));
                bX->contador_turnos = 3;
                bX->explotar = &ExplosionX;
                ColocarBomba(bX, fila, columna);
            }
            PasarTurno();
            turno +=1;
        }

        //Mostrar Bombas
        else if(n==2){
            MostrarBombas();
        }

        //Mostrar Tesoros
        else if(n==3){
            VerTesoros();
        } 
        
        if (FinDelJuego()==1){
            MostrarTablero();
            char c;
            printf("Felicidades has ganado\n ");
            scanf(" %c",&c);
            break;
        }
    }
    BorrarTablero();
    return 0;
}