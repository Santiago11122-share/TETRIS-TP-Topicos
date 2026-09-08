#include <stdio.h>
#include <stdlib.h>
#include "pieza.h"
#include "tablero.h"
#include "FuncionesSDL.h"


int main()
{
    t_pieza pieza;
    t_tablero tablero;
    SDL_Window *ventana=NULL;
    SDL_Renderer *render=NULL;
    inicializar_sdl(&ventana,&render);
    iniciar_audio ();
    iniciar_mixer();
    cargar_musica_menu();
    ejecutar_juego(render);


    pieza=crearPieza();
    mostrarpieza(&pieza);
    printf("\n");

    /*

    TEST DE FICHAS RANDOM Y ROTACION


    rotarPieza(&pieza);
    printf("\n");
    mostrarpieza(&pieza);
    rotarPieza(&pieza);
    printf("\n");
    mostrarpieza(&pieza);
    rotarPieza(&pieza);
    printf("\n");
    mostrarpieza(&pieza);*/
    tablero=inicializarTablero();
    colocarPieza(&tablero,&pieza);
    mostrartablero(&tablero);


    return 0;
}
