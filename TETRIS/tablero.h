#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include "pieza.h"

#define FILAS 26
#define COLUMNAS 12

typedef struct {

    int celdas[FILAS][COLUMNAS];

}t_tablero;

t_tablero inicializarTablero();

int hayColision(t_tablero *tablero,t_pieza *pieza,int nuevoX,int nuevoY);

void colocarPieza(t_tablero *tablero,t_pieza *pieza);

int eliminarFilas(t_tablero *tablero);


#endif // TABLERO_H_INCLUDED
