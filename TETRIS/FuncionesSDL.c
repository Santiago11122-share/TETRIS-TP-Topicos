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
        890,
        800,
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

void dibujarTablero(SDL_Renderer *render, t_tablero *tablero)
{
    SDL_Rect celda;
    SDL_Rect bloque;

    celda.w = 25;
    celda.h = 25;

    for(int f = 0; f < FILAS; f++)
    {
        for(int c = 0; c < COLUMNAS; c++)
        {
            celda.x = 325 + c * 25;
            celda.y = 125 + f * 25;

            // Rectangulo un poco mas chico
            // para dejar separacion entre bloques
            bloque.x = celda.x + 1;
            bloque.y = celda.y + 1;
            bloque.w = celda.w - 2;
            bloque.h = celda.h - 2;


            // CELDA VACIA
            if(tablero->celdas[f][c] == 0)
            {
                // Fondo negro
                SDL_SetRenderDrawColor(render, 15, 15, 15, 255);
                SDL_RenderFillRect(render, &celda);

                // Linea de la cuadricula
                SDL_SetRenderDrawColor(render, 45, 45, 45, 255);
                SDL_RenderDrawRect(render, &celda);
            }


            // PIEZA
            else if(tablero->celdas[f][c] == 1)
            {
                // Fondo de la celda
                SDL_SetRenderDrawColor(render, 15, 15, 15, 255);
                SDL_RenderFillRect(render, &celda);

                // Bloque azul
                SDL_SetRenderDrawColor(render, 0, 150, 255, 255);
                SDL_RenderFillRect(render, &bloque);

                // Borde claro del bloque
                SDL_SetRenderDrawColor(render, 220, 220, 220, 255);
                SDL_RenderDrawRect(render, &bloque);
            }


            // BORDE DEL TABLERO
            else if(tablero->celdas[f][c] == 2)
            {
                SDL_SetRenderDrawColor(render, 150, 150, 150, 255);
                SDL_RenderFillRect(render, &celda);

                SDL_SetRenderDrawColor(render, 220, 220, 220, 255);
                SDL_RenderDrawRect(render, &celda);
            }
        }
    }
}

SDL_Texture *cargarImagen(SDL_Renderer *renderer, const char *ruta)
{
    SDL_Surface *superficie = IMG_Load(ruta);

    if(superficie == NULL)
    {
        printf("Error al cargar imagen: %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Texture *textura =
        SDL_CreateTextureFromSurface(renderer, superficie);

    SDL_FreeSurface(superficie);

    if(textura == NULL)
    {
        printf("Error al crear textura: %s\n", SDL_GetError());
        return NULL;
    }

    return textura;
}

void ejecutar_juego(SDL_Renderer *renderer, t_tablero *tablero)
{
    int ejecutando = 1;
    SDL_Event evento;

    // Cargar la imagen UNA SOLA VEZ
    SDL_Texture *imagen = cargarImagen(renderer, "img/Fondo.png");

    // Posicion fija de la imagen
    SDL_Rect destinoImagen;

    destinoImagen.x = 0;   // posicion horizontal
    destinoImagen.y = 0;   // posicion vertical
    destinoImagen.w = 890;   // ancho
    destinoImagen.h = 800;   // alto


    while (ejecutando)
    {
        while (SDL_PollEvent(&evento))
        {
            if (evento.type == SDL_QUIT)
            {
                ejecutando = 0;
            }
        }

        // 1. Limpiar pantalla
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        // 2. Dibujar imagen siempre en la misma posicion
        if(imagen != NULL)
        {
            SDL_RenderCopy(
                renderer,
                imagen,
                NULL,
                &destinoImagen
            );
        }

        // 3. Dibujar tablero
        dibujarTablero(renderer, tablero);

        // 4. Dibujar siguiente pieza


        // 5. Mostrar todo
        SDL_RenderPresent(renderer);
    }


    // Liberar imagen al terminar el juego
    if(imagen != NULL)
    {
        SDL_DestroyTexture(imagen);
    }
}
