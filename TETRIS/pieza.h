#ifndef PIEZA_H_INCLUDED
#define PIEZA_H_INCLUDED
#define TAM_PIEZA 4
typedef struct {
    int forma[TAM_PIEZA][TAM_PIEZA];
    int x;
    int y;
    int tipo;
} t_pieza;

t_pieza crearPieza();


#endif // PIEZA_H_INCLUDED
