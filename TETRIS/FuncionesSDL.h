#ifndef FUNCIONESSDL_H_INCLUDED
#define FUNCIONESSDL_H_INCLUDED
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
typedef struct
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *background;
}game;
int inicializar_sdl(SDL_Window **ventana, SDL_Renderer **renderer);


#endif // FUNCIONESSDL_H_INCLUDED
