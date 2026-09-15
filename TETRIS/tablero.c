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

int hayColision(t_tablero *tablero, t_pieza *pieza, int nuevoX, int nuevoY)
{
    int f, c;

    for(f=0; f<4; f++)
    {
        for(c=0; c<4; c++)
        {
            if(pieza->forma[f][c] != 0)
            {
                // Verificar que no salga del tablero
                if(nuevoX+c < 0 || nuevoX+c >= COLUMNAS)
                    return 1;

                if(nuevoY+f < 0 || nuevoY+f >= FILAS)
                    return 1;

                // Verificar colision con otra pieza o borde
                if(tablero->celdas[nuevoY+f][nuevoX+c] != 0)
                    return 1;
            }
        }
    }
    //sin colision
    return 0;
}

void rotarPieza(t_tablero *tablero,t_pieza *pieza)
{
    t_pieza aux;
    aux.x=pieza->x;
    aux.y=pieza->y;
    for(int f=0;f<4;f++)
    {
        for(int c=0;c<4;c++)
        {
            aux.forma[c][f]=pieza->forma[3-f][c];
        }
    }
    if(hayColision(tablero,&aux,aux.x,aux.y)==0)
    {
        for(int f = 0; f < 4; f++)
        {
            for(int c = 0; c < 4; c++)
            {
                pieza->forma[f][c] = aux.forma[f][c];
            }
        }
    }
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
                rotarPieza(tablero,pieza);
                break;
        }
}


void eliminarFilas(t_tablero *tablero)
{
    int f, c, escompleta;

    for(f=INICIOFILAREAL; f<FILAS-1; f++)
    {
        escompleta=1;

        // Verificar si la fila está completa
        for(c=INICIOCOLREAL; c<COLUMNAS-1; c++)
        {
            if(tablero->celdas[f][c]!=1)
            {
                escompleta=0;
            }
        }

        if(escompleta==1)
        {
            // Bajar las filas superiores
            for(int fila=f; fila>INICIOFILAREAL; fila--)
            {
                for(c=INICIOCOLREAL; c<COLUMNAS-1; c++)
                {
                    tablero->celdas[fila][c]=
                        tablero->celdas[fila-1][c];
                }
            }

            // Limpiar la primera fila jugable
            for(c=INICIOCOLREAL; c<COLUMNAS-1; c++)
            {
                tablero->celdas[INICIOFILAREAL][c]=0;
            }

            // Volver a revisar la misma fila
            f--;
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
