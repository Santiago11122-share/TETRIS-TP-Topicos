#include "pieza.h"
#include <stdlib.h>
#include <stdio.h>
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

    t_color colores[] = {
    {0,   255, 255},  // Cyan
    {255, 255, 0},    // Amarillo
    {128, 0,   128},  // Violeta
    {0,   255, 0},    // Verde
    {255, 0,   0},    // Rojo
    {0,   0,   255},  // Azul
    {255, 165, 0}     // Naranja
    };

    p.tipo = rand() % 7;
    p.rgb= colores[p.tipo];

    p.x = 4;
    p.y = 0;

    for(int f = 0; f < 4; f++) {
        for(int c = 0; c < 4; c++) {
            p.forma[f][c] = piezas[p.tipo][f][c];
        }
    }

    return p;
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
