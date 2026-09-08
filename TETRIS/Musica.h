#ifndef MUSICA_H_INCLUDED
#define MUSICA_H_INCLUDED
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
bool iniciar_audio (void);
bool iniciar_mixer(void);
Mix_Music* cargar_musica(const char* ubicacion);
Mix_Music* cargar_musica_menu(void);
void liberar_musica(Mix_Music* musica);
void cerrar_mixer(void);

#endif // MUSICA_H_INCLUDED
