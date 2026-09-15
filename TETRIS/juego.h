#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include "tablero.h"
#include "pieza.h"
#include "FuncionesSDL.h"
#include "Musica.h"
#include "puntaje.h"
int IniciarJuego();
int loopPrincipal(t_tablero *tablero, t_pieza *pieza,SDL_Renderer *render, SDL_Texture *fondo,TTF_Font *fuente, long long int mejorpto);
#endif // JUEGO_H_INCLUDED
