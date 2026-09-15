#include "tablero.h"
#include <stdio.h>
#include <stdlib.h>
t_tablero inicializarTablero()
{
    t_tablero tablero;
    for(int f=0;f<FILAS;f++)
    {
        //dibujamos # para marcar el tablero o 0 para marcar espacios libres
        if(f==25)
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

int hayColision(t_tablero *tablero,t_pieza *pieza,int nuevoX,int nuevoY)
{
    int f,c;
    for(f=0;f<4;f++)
    {
        for(c=0;c<4;c++)
        {
            if(pieza->forma[f][c]!=0)
            {
                if(tablero->celdas[nuevoY+f][nuevoX+c]!=0)
                    //con colision
                    return 1;
            }
        }
    }
    //Sin colision
    return 0;
}

void colocarPieza(t_tablero *tablero, t_pieza *pieza)
{
    for(int f = 0; f < 4; f++)
    {
        for(int c = 0; c < 4; c++)
        {
            if(pieza->forma[f][c] != 0)
            {
                tablero->celdas[pieza->y + f][pieza->x + c] =
                    pieza->forma[f][c];
            }
        }
    }
    *pieza=crearPieza();
}

int moverpieza_abajo(t_tablero *tablero,t_pieza *pieza)
{
    if(hayColision(tablero,pieza,pieza->x,pieza->y+1)==0)
    {
        pieza->y++;
        //se bajo la pieza
        return 0;
    }
    else
    {
        //se fija la pieza en el tablero
        colocarPieza(tablero,pieza);
    }
    return 0;
}

void moverpieza(t_tablero *tablero,t_pieza *pieza,int tecla)
{
    switch(tecla)
        {
            case TECLA_IZQUIERDA:

                if(hayColision(tablero,pieza,pieza->x-1,pieza->y)==0)
                {
                    pieza->x--;
                }
                break;

            case TECLA_DERECHA:
                if(hayColision(tablero,pieza,pieza->x+1,pieza->y)==0)
                {
                    pieza->x++;
                }
                break;

            case TECLA_ABAJO:
                moverpieza_abajo(tablero,pieza);
                break;

            case TECLA_ROTAR:
                rotarPieza(pieza);
                break;
        }
}


void eliminarFilas(t_tablero *tablero)
{
    int f,c=INICIOCOLREAL, escompleta=1;
    for(f=INICIOFILAREAL;f<FILAS;f++)
    {
        while(tablero->celdas[f][c]==1&&c<COLUMNAS)
        {
            c++;
        }

        if(tablero->celdas[f][c]==0)
            escompleta=0;

        if(escompleta==1)
        {
            c=INICIOCOLREAL;
            while(tablero->celdas[f][c]==1&&c<COLUMNAS)
            {
                tablero->celdas[f][c]=0;
            }
        }
    }
}

int findejuego(t_tablero *tablero,t_pieza *pieza)
{
    int sigueElJuego=1,c=INICIOCOLREAL;
    while(tablero->celdas[INICIOFILAREAL][c]==0&&c<COLUMNAS)
    {
        c++;
    }
    if(tablero->celdas[INICIOFILAREAL][c]==1)
        sigueElJuego=0;
    return sigueElJuego;
}
