#include "FuncionesSDL.h"
#include <stdio.h>
#include <stdlib.h>

int inicializar_sdl(SDL_Window **ventana, SDL_Renderer **renderer)
{
    #ifdef _WIN32 //Manejo de dpi en windows
    SDL_SetHint(SDL_HINT_WINDOWS_DPI_AWARENESS, "permonitorv2");
    #endif


    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
    fprintf(stderr, "Error al inicializar SDL: %s\n", SDL_GetError());
    return -1;
    }

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
            celda.y = 250 + f * 25;

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


void dibujarJuego(SDL_Renderer *renderer,t_tablero *tablero,t_pieza *pieza,SDL_Texture *fondo)
{
    SDL_Rect destinoImagen;

    destinoImagen.x = 0;
    destinoImagen.y = 0;
    destinoImagen.w = 890;
    destinoImagen.h = 800;

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    if(fondo != NULL)
    {
        SDL_RenderCopy(renderer,fondo,NULL,&destinoImagen);
    }

    // Piezas ya fijadas
    dibujarTablero(renderer, tablero);

    // Pieza que esta cayendo
    dibujarPieza(renderer, pieza);

}

int procesarEvento()
{
    SDL_Event evento;

    while(SDL_PollEvent(&evento))
    {
        if(evento.type == SDL_QUIT)
        {
            return TECLA_SALIR;
        }

        if(evento.type == SDL_KEYDOWN)
        {
            switch(evento.key.keysym.sym)
            {
                case SDLK_LEFT:
                    return TECLA_IZQUIERDA;

                case SDLK_RIGHT:
                    return TECLA_DERECHA;

                case SDLK_DOWN:
                    return TECLA_ABAJO;

                case SDLK_UP:
                    return TECLA_ROTAR;

                case SDLK_ESCAPE:
                    return TECLA_SALIR;
            }
        }
    }

    return TECLA_NINGUNA;
}

void dibujarPieza(SDL_Renderer *renderer, t_pieza *pieza)
{
    SDL_Rect bloque;

    bloque.w = 23;
    bloque.h = 23;

    for(int f = 0; f < 4; f++)
    {
        for(int c = 0; c < 4; c++)
        {
            if(pieza->forma[f][c] != 0)
            {

                    bloque.x = 325 + (pieza->x + c) * 25 + 1;
                    bloque.y = 250 + (pieza->y + f) * 25 + 1;

                    SDL_SetRenderDrawColor(renderer, 0, 150, 255, 255);
                    SDL_RenderFillRect(renderer, &bloque);

                    SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
                    SDL_RenderDrawRect(renderer, &bloque);
            }
        }
    }
}

void mostrarPuntaje(SDL_Renderer *render, TTF_Font *fuente, long long int puntaje)
{
    char texto[50];

    sprintf(texto, "%lld", puntaje);

    SDL_Color color = {255, 255, 255, 255};

    SDL_Surface *superficie =
        TTF_RenderText_Solid(fuente, texto, color);

    if(superficie == NULL)
    {
        printf("Error superficie: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *textura =
        SDL_CreateTextureFromSurface(render, superficie);

    if(textura == NULL)
    {
        printf("Error textura: %s\n", SDL_GetError());
        SDL_FreeSurface(superficie);
        return;
    }

    SDL_Rect destino = {
        675,
        105,
        superficie->w,
        superficie->h
    };

    SDL_RenderCopy(render, textura, NULL, &destino);

    SDL_DestroyTexture(textura);
    SDL_FreeSurface(superficie);
}

void mostrarPuntajeActual(SDL_Renderer *render,TTF_Font *fuente,long long int puntaje)
{
    char texto[50];

    sprintf(texto, "%lld", puntaje);

    SDL_Color color = {255, 255, 255, 255};

    SDL_Surface *superficie =
        TTF_RenderText_Solid(fuente, texto, color);

    if(superficie == NULL)
    {
        return;
    }

    SDL_Texture *textura =
        SDL_CreateTextureFromSurface(render, superficie);

    if(textura == NULL)
    {
        SDL_FreeSurface(superficie);
        return;
    }

    SDL_Rect destino = {
        675,
        200,   // cambiar segun donde este el cuadro SCORE
        superficie->w,
        superficie->h
    };

    SDL_RenderCopy(render, textura, NULL, &destino);

    SDL_DestroyTexture(textura);
    SDL_FreeSurface(superficie);
}

void dibujarSiguientePieza(SDL_Renderer *renderer, t_pieza *siguientepieza)
{
    SDL_Rect bloque;

    int inicioX = 700;
    int inicioY = 410;
    int tam = 25;

    bloque.w = tam - 2;
    bloque.h = tam - 2;

    for(int f = 0; f < 4; f++)
    {
        for(int c = 0; c < 4; c++)
        {
            if(siguientepieza->forma[f][c] != 0)
            {
                bloque.x = inicioX + c * tam + 1;
                bloque.y = inicioY + f * tam + 1;

                SDL_SetRenderDrawColor(renderer, 0, 150, 255, 255);
                SDL_RenderFillRect(renderer, &bloque);

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawRect(renderer, &bloque);
            }
        }
    }
}
