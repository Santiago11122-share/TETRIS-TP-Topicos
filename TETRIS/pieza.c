#include "pieza.h"
#include <stdlib.h>
#include <time.h>

t_pieza crearPieza() {

    t_pieza p;
    srand(time(NULL));
    int piezas[7][4][4] = {

        // I
        {
            {0,0,0,0},
            {1,1,1,1},
            {0,0,0,0},
            {0,0,0,0}
        },

        // O
        {
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },

        // T
        {
            {0,1,0,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },

        // L
        {
            {0,0,1,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },

        // J
        {
            {1,0,0,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },

        // S
        {
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },

        // Z
        {
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        }
    };

    p.tipo = rand() % 7;

    p.x = 4;
    p.y = 0;

    for(int f = 0; f < 4; f++) {
        for(int c = 0; c < 4; c++) {
            p.forma[f][c] = piezas[p.tipo][f][c];
        }
    }

    return p;
}

void rotarPieza(t_pieza *pieza)
{
    t_pieza aux;
    for(int f=0;f<4;f++)
    {
        for(int c=0;c<4;c++)
        {
            aux.forma[c][f]=pieza->forma[3-f][c];
        }
    }
    for(int f = 0; f < 4; f++) {
        for(int c = 0; c < 4; c++) {
            pieza->forma[f][c] = aux.forma[f][c];
        }
    }
}

void mostrarpieza(t_pieza *pieza)
{
    for(int f = 0; f < 4; f++)
    {
        for(int c = 0; c < 4; c++)
        {
            printf("%d",pieza->forma[f][c]);
        }
        printf("\n");
    }
}
