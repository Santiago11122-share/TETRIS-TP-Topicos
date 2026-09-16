#ifndef FUNCIONESSDL_H_INCLUDED
#define FUNCIONESSDL_H_INCLUDED
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "tablero.h"


typedef struct
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *background;
}game;
int inicializar_sdl(SDL_Window **ventana, SDL_Renderer **renderer);
void dibujarJuego(SDL_Renderer *renderer,t_tablero *tablero,t_pieza *pieza,SDL_Texture *fondo);
SDL_Texture *cargarImagen(SDL_Renderer *renderer, const char *ruta);
void ejecutar_juego(SDL_Renderer *renderer, t_tablero *tablero);
int procesarEvento(void);
void dibujarPieza(SDL_Renderer *renderer, t_pieza *pieza);
void mostrarPuntajeActual(SDL_Renderer *render,TTF_Font *fuente,long long int puntaje);
void dibujarSiguientePieza(SDL_Renderer *renderer, t_pieza *siguientepieza);

#endif // FUNCIONESSDL_H_INCLUDED
