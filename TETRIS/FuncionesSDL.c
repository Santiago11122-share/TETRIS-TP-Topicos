#include "FuncionesSDL.h"
#include <stdio.h>
#include <stdlib.h>
int inicializar_sdl(SDL_Window **ventana, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Error al inicializar SDL: %s\n", SDL_GetError());
        return -1;
    }

    *ventana = SDL_CreateWindow(
        "TETRIS-LOS TETROMINOS",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN
    );

    if (*ventana == NULL)
    {
        fprintf(stderr, "Error al crear la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    *renderer = SDL_CreateRenderer(
        *ventana,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (*renderer == NULL)
    {
        fprintf(stderr, "Error al crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(*ventana);
        SDL_Quit();
        return -1;
    }

    return 0;
}

void ejecutar_juego(SDL_Renderer *renderer)
{
    int ejecutando = 1;
    SDL_Event evento;

    SDL_Rect cuadrado = {
        350,    // X
        250,    // Y
        100,    // Ancho
        100     // Alto
    };

    while (ejecutando)
    {
        // Procesar eventos
        while (SDL_PollEvent(&evento))
        {
            if (evento.type == SDL_QUIT)
            {
                ejecutando = 0;
            }
        }

        // Limpiar pantalla
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        // Color del cuadrado
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        // Dibujar cuadrado
        SDL_RenderFillRect(renderer, &cuadrado);

        // Mostrar lo dibujado
        SDL_RenderPresent(renderer);
    }
}
