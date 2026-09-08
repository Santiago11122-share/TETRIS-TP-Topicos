#include "tablero.h"
#include <stdio.h>
#include <stdlib.h>
t_tablero inicializarTablero()
{
    t_tablero tablero;
    for(int f=0;f<FILAS;f++)
    {
        //dibujamos # para marcar el tablero o 0 para marcar espacios libres
        if(f==4||f==25)
        {
            for(int c=0; c<COLUMNAS; c++)
            {
                tablero.celdas[f][c]=2;
            }
        }
        else
        {
            for(int c=0; c<COLUMNAS; c++)
            {
                if(c==0||c==11)
                    tablero.celdas[f][c]=2;
                else
                    tablero.celdas[f][c]=0;
            }
        }
    }
    return tablero;
}
void mostrartablero(t_tablero *tablero)
{
    for(int f = 0; f < FILAS; f++)
    {
        for(int c = 0; c < COLUMNAS; c++)
        {
            printf("%d",tablero->celdas[f][c]);
        }
        printf("\n");
    }
}

int hayColision(t_tablero *tablero,t_pieza *pieza,int nuevoX,int nuevoY);

void colocarPieza(t_tablero *tablero,t_pieza *pieza)
{
    for(int f = 0; f < 4; f++)
    {
        for(int c = 0; c < 4; c++)
        {
            if(pieza->forma[f][c] != 0)
            {
                tablero->celdas[f][c + 4] = pieza->forma[f][c];
            }
        }
        printf("\n");
    }
}


int eliminarFilas(t_tablero *tablero);
