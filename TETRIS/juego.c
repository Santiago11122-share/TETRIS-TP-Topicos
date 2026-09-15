#include "juego.h"
int loopPrincipal(t_tablero *tablero,t_pieza *pieza,SDL_Renderer *render,SDL_Texture *fondo)
{
    int tecla;
    int jugando = 1;

    *pieza = crearPieza();

    while(jugando && findejuego(tablero, pieza) == 1)
    {
        tecla = procesarEvento();

        if(tecla == TECLA_SALIR)
        {
            jugando = 0;
        }
        else
        {
            if(tecla != TECLA_NINGUNA)
            {
                moverpieza(tablero, pieza, tecla);
            }

            moverpieza_abajo(tablero, pieza);

            eliminarFilas(tablero);

            dibujarJuego(render,tablero,pieza,fondo);

            SDL_Delay(200);
        }
    }

    return 0;
}


int IniciarJuego()
{
    t_pieza pieza;
    t_tablero tablero;

    SDL_Window *ventana = NULL;
    SDL_Renderer *render = NULL;

    if(inicializar_sdl(&ventana, &render) != 0)
    {
        return -1;
    }

    iniciar_audio();
    iniciar_mixer();
    cargar_musica_menu();

    tablero = inicializarTablero();

    // Cargar fondo una sola vez
    SDL_Texture *fondo =
        cargarImagen(render, "img/Fondo.png");

    // Ejecutar juego
    loopPrincipal(&tablero,&pieza,render,fondo);

    // Liberar fondo
    if(fondo != NULL)
    {
        SDL_DestroyTexture(fondo);
    }

    // Cerrar SDL
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(ventana);

    SDL_Quit();

    return 0;
}

