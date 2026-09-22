#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include "pieza.h"

#define FILAS 21
#define COLUMNAS 12
#define INICIOCOLREAL 1

#define TECLA_NINGUNA    0
#define TECLA_IZQUIERDA  1
#define TECLA_DERECHA    2
#define TECLA_ABAJO      3
#define TECLA_ROTAR      4
#define TECLA_SALIR      5

typedef struct {

    int celdas[FILAS][COLUMNAS];

}t_tablero;

t_tablero inicializarTablero();
void mostrartablero(t_tablero *tablero);
int hayColision(t_tablero *tablero, t_pieza *pieza, int nuevoX, int nuevoY);
void rotarPieza(t_tablero *tablero,t_pieza *pieza);
void colocarPieza(t_tablero *tablero,t_pieza *pieza,t_pieza *siguientepieza,int contadores[]);
int moverpieza_abajo(t_tablero *tablero,t_pieza *pieza,t_pieza *siguientepieza, int contadores[]);
void moverpieza(t_tablero *tablero,t_pieza *pieza,t_pieza *siguientepieza,int tecla, int contadores[]);
int eliminarFilas(t_tablero *tablero);
int findejuego(t_tablero *tablero,t_pieza *pieza);





#endif // TABLERO_H_INCLUDED
