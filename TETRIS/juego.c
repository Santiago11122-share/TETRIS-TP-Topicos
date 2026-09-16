#include "juego.h"

int loopPrincipal(t_tablero *tablero,t_pieza *pieza,SDL_Renderer *render,SDL_Texture *fondo,TTF_Font *fuente,long long int mejorpto)
{
    int tecla;
    int jugando = 1;
    int filaselim;
    t_pieza siguientepieza;
    int puntajeActual = 0;

    // Guarda el momento de la última caída automática
    Uint32 tiempoUltimaCaida = SDL_GetTicks();

    // Cada cuántos milisegundos baja sola la pieza
    Uint32 intervaloCaida = 300;

    *pieza = crearPieza();
    siguientepieza = crearPieza();

    while(jugando && findejuego(tablero, pieza) == 1)
    {
        // Leer teclado
        tecla = procesarEvento();

        if(tecla == TECLA_SALIR)
        {
            jugando = 0;
        }
        else
        {
            // Movimiento realizado por el jugador
            if(tecla != TECLA_NINGUNA)
            {
                moverpieza(tablero, pieza, &siguientepieza, tecla);
            }

            // Obtener tiempo actual
            Uint32 tiempoActual = SDL_GetTicks();

            // Solo bajar automáticamente si pasaron 500 ms
            if(tiempoActual - tiempoUltimaCaida >= intervaloCaida)
            {
                moverpieza_abajo(tablero, pieza,&siguientepieza);

                // Guardamos cuándo fue la última caída
                tiempoUltimaCaida = tiempoActual;
            }

            // Eliminar filas completas
            filaselim = eliminarFilas(tablero);

            // Actualizar puntaje
            puntajeActual = puntaje(puntajeActual, filaselim);

            // Dibujar juego
            dibujarJuego(render, tablero, pieza, fondo);

            SDL_Delay(16);

            //Mostrar siguiente pieza
            dibujarSiguientePieza(render, &siguientepieza);

            // Mostrar mejor puntaje
            mostrarPuntaje(render, fuente, mejorpto);

            // Mostrar puntaje actual
            mostrarPuntajeActual(render, fuente, puntajeActual);

            // Mostrar todo en pantalla
            SDL_RenderPresent(render);

            // Mantener el loop rápido
            SDL_Delay(16);
        }
    }
    guardarpuntaje(puntajeActual);
    return 0;
}

int IniciarJuego()
{
    // Variables principales del juego
    t_pieza pieza;
    t_tablero tablero;
    long long int mejorpto;

    // Punteros principales de SDL
    SDL_Window *ventana = NULL;
    SDL_Renderer *render = NULL;
    TTF_Font *fuente = NULL;

    // Inicializar SDL, crear ventana y renderer
    if(inicializar_sdl(&ventana, &render) != 0)
    {
        return -1;
    }

    // Inicializar SDL_ttf para poder usar fuentes
    if(TTF_Init() == -1)
    {
        printf("Error inicializando TTF: %s\n", TTF_GetError());

        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(ventana);
        SDL_Quit();

        return -1;
    }

    // Cargar la fuente
    fuente = TTF_OpenFont("fuentes/Montserrat-Bold.ttf", 40);

    // Verificar que la fuente se haya cargado correctamente
    if(fuente == NULL)
    {
        printf("Error cargando fuente: %s\n", TTF_GetError());

        TTF_Quit();
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(ventana);
        SDL_Quit();

        return -1;
    }

    // Inicializar sistema de audio
    iniciar_audio();

    // Inicializar SDL_mixer
    iniciar_mixer();

    // Cargar musica
    cargar_musica_menu();

    // Leer el mejor puntaje guardado
    mejorpto = mejorpuntaje();

    // Inicializar tablero
    tablero = inicializarTablero();

    // Cargar imagen de fondo
    SDL_Texture *fondo = cargarImagen(render, "img/Fondo.png");

    // Ejecutar ciclo principal del juego
    loopPrincipal(&tablero, &pieza, render, fondo, fuente, mejorpto);

    // Liberar textura del fondo
    if(fondo != NULL)
    {
        SDL_DestroyTexture(fondo);
    }

    // Liberar fuente
    TTF_CloseFont(fuente);

    // Cerrar SDL_ttf
    TTF_Quit();

    // Destruir renderer
    SDL_DestroyRenderer(render);

    // Destruir ventana
    SDL_DestroyWindow(ventana);

    // Cerrar SDL
    SDL_Quit();

    return 0;
}

