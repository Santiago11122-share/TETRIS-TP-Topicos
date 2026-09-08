#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Musica.h"

/* Inicializa SDL_mixer */



bool iniciar_audio (void)
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
        return false;

    return true;
}


bool iniciar_mixer(void)
{

    if (Mix_Init(MIX_INIT_MP3 || MIX_INIT_OGG) == 0)
    {
        printf("Error al inicializar SDL_mixer: %s\n", Mix_GetError());
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        fprintf(stderr, "Mix_OpenAudio error: %s\n", Mix_GetError());
        return false;
    }

    return true;
}

/* Carga una musica desde archivo */
Mix_Music* cargar_musica(const char* ubicacion)
{
    Mix_Music* music = Mix_LoadMUS(ubicacion);

    if (music == NULL)
    {
        fprintf(stderr, "Mix_LoadMUS error: %s\n", Mix_GetError());
    }

    return music;
}

/* Carga y reproduce la musica del menu */
Mix_Music* cargar_musica_menu(void)
{
    Mix_Music* musica = cargar_musica("snd/L-gante.mp3");

    if (musica == NULL)
        return NULL;

    if (Mix_PlayMusic(musica, -1) == -1)
    {
        fprintf(stderr, "Mix_PlayMusic error: %s\n", Mix_GetError());
        Mix_FreeMusic(musica);
        return NULL;
    }

    return musica;
}

/* Libera la musica */
void liberar_musica(Mix_Music* musica)
{
    if (musica != NULL)
        Mix_FreeMusic(musica);
}


/* Cierra SDL_mixer */
void cerrar_mixer(void)
{
    Mix_CloseAudio();
    Mix_Quit();
}
