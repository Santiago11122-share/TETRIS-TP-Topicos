#include "juego.h"

int loopPrincipal(t_tablero *tablero,t_pieza *pieza,SDL_Renderer *render,SDL_Texture *fondo,TTF_Font *fuente,long long int mejorpto)
{
    int tecla;
    int jugando = 1;
    int filaselim;
    t_pieza siguientepieza;
    int puntajeActual = 0;

    // Guarda el momento de la ultima caida automatica
    Uint32 tiempoUltimaCaida = SDL_GetTicks();

    // Cada cuantos milisegundos baja sola la pieza
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

            // Solo bajar autom�ticamente si pasaron 500 ms
            if(tiempoActual - tiempoUltimaCaida >= intervaloCaida)
            {
                moverpieza_abajo(tablero, pieza,&siguientepieza);

                // Guardamos cu�ndo fue la �ltima ca�da
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

            // Mantener el loop r�pido
            SDL_Delay(16);
        }
    }
    guardarpuntaje(puntajeActual);
    return 0;
}

bool mouseSobre(SDL_Point *p, SDL_Rect *r) //funcion para saber si el mouse esta sobre un boton
{
    return (p->x >= r->x && p->x <= r->x + r->w &&
            p->y >= r->y && p->y <= r->y + r->h);
}

void renderizarTextoBoton(SDL_Renderer *render, TTF_Font *fuente, const char *texto, SDL_Rect *btnRect)
{
    SDL_Color colorTexto = {255, 255, 255, 255}; // Blanco

    //creado superficie con el texto
    SDL_Surface *surfaceTexto = TTF_RenderText_Blended(fuente, texto, colorTexto);
    if (!surfaceTexto) return;

    // creado textura a partir de la superficie
    SDL_Texture *texturaTexto = SDL_CreateTextureFromSurface(render, surfaceTexto);

    //calculo un rectángulo para centrar el texto dentro del boton de forma automática
    SDL_Rect rectDestino;
    rectDestino.w = surfaceTexto->w;
    rectDestino.h = surfaceTexto->h;
    rectDestino.x = btnRect->x + (btnRect->w - rectDestino.w) / 2; // Centrado horizontal
    rectDestino.y = btnRect->y + (btnRect->h - rectDestino.h) / 2; // Centrado vertical

    // dibujar la textura del texto en pantalla
    SDL_RenderCopy(render, texturaTexto, NULL, &rectDestino);

    // limpiar memoria de la superficie y la textura temporal
    SDL_FreeSurface(surfaceTexto);
    SDL_DestroyTexture(texturaTexto);
}

int IniciarJuego()
{
    t_pieza pieza;
    t_tablero tablero;
    long long int mejorpto;

    //SDL
    SDL_Window *ventana = NULL;
    SDL_Renderer *render = NULL;
    TTF_Font *fuente = NULL;

    // crear ventana y renderer
    if(inicializar_sdl(&ventana, &render) != 0)
    {
        return -1;
    }

    // SDL_ttf para fuentes
    if(TTF_Init() == -1)
    {
        printf("Error inicializando TTF: %s\n", TTF_GetError());
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return -1;
    }

    // cargar la fuente
    fuente = TTF_OpenFont("fuentes/Montserrat-Bold.ttf", 40);
    if(fuente == NULL)
    {
        printf("Error cargando fuente: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return -1;
    }

    // sistema de audio y mixer
    iniciar_audio();
    iniciar_mixer();
    cargar_musica_menu();

    // leer el mejor puntaje guardado
    mejorpto = mejorpuntaje();

    // cargar imagen de fondo de juego y menu
    SDL_Texture *fondo = cargarImagen(render, "img/Fondo.png");
    SDL_Texture *fondo_menu = cargarImagen(render, "img/menu.jpg");

    //CONFIGURACIÓN DEL MENÚ Y ESTADOS ---
    Estado estado = MENU;
    SDL_Event e;
    bool corriendo = true;

    //SDL_Rect para crear rectangulos, poniendo su posicion en pantalla
    SDL_Rect btnJugar = {320, 300, 250, 50};
    SDL_Rect btnControles = {320, 380, 250, 50};
    SDL_Rect btnSalir = {320, 460, 250, 50};

    SDL_Rect arriba = {290, 300, 308, 70};
    SDL_Rect lados = {290, 380, 308, 70};
    SDL_Rect salida = {290, 460, 308, 70};

    //CICLO ppal tetris
    while (corriendo && estado != EXIT)
    {
        SDL_Point mousePos = {-1, -1};

        //procesar eventos
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                estado = EXIT;
            }

            //si estas en el menú, toma los clics de los botones
            if (estado == MENU)
            {
                if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                {
                    mousePos.x = e.button.x;
                    mousePos.y = e.button.y;

                    if (mouseSobre(&mousePos, &btnJugar)) //si el mouse fue presionado sobre alguno de los botones
                    {
                        estado = JUGAR;
                    }
                    else if (mouseSobre(&mousePos, &btnControles))
                    {
                        estado = CONTROLES;
                    }
                    else if (mouseSobre(&mousePos, &btnSalir))
                    {
                        estado = EXIT;
                    }
                }
                if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_ESCAPE) //si se toca escape
                    {
                        estado = EXIT; //si estas en el menu principal, sale
                    }
                }
            }
            // Si estamos en controles, permitimos volver con la tecla ESC
            else if (estado == CONTROLES)
            {
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                {
                    estado = MENU;
                }
            }
        }

        //RENDERIZADO SEGÚN EL ESTADO ACTUAL
        if (estado == MENU)
        {
            //fondo
            SDL_RenderClear(render);
            SDL_RenderCopy(render, fondo_menu, NULL, NULL);

            // btn jugar
            SDL_SetRenderDrawColor(render, 46, 204, 113, 255);
            SDL_RenderFillRect(render, &btnJugar);
            renderizarTextoBoton(render, fuente, "Jugar", &btnJugar);

            // btn controles
            SDL_SetRenderDrawColor(render, 52, 152, 219, 255);
            SDL_RenderFillRect(render, &btnControles);
            renderizarTextoBoton(render, fuente, "Controles", &btnControles);

            // btn salir
            SDL_SetRenderDrawColor(render, 231, 76, 60, 255);
            SDL_RenderFillRect(render, &btnSalir);
            renderizarTextoBoton(render, fuente, "Salir", &btnSalir);

            SDL_RenderPresent(render);
        }
        else if (estado == JUGAR)
        {
            // inicializar el tablero limpio para la nueva partida
            tablero = inicializarTablero();

            //loop de juego
            loopPrincipal(&tablero, &pieza, render, fondo, fuente, mejorpto);

            //al terminar la partida, actualiza el mejor puntaje
            mejorpto = mejorpuntaje();

            // vuelve al menú
            estado = MENU;
        }
        else if (estado == CONTROLES)
        {
            //pantalla de controles
            SDL_RenderClear(render);

            SDL_RenderCopy(render, fondo_menu, NULL, NULL);

            SDL_SetRenderDrawColor(render, 46, 204, 113, 255);
            SDL_RenderFillRect(render, &arriba);
            renderizarTextoBoton(render, fuente, "Arriba - Rotar", &arriba);

            SDL_SetRenderDrawColor(render, 52, 152, 219, 255);
            SDL_RenderFillRect(render, &lados);
            renderizarTextoBoton(render, fuente, "Izq Der - Mover", &lados);

            SDL_SetRenderDrawColor(render, 231, 76, 60, 255);
            SDL_RenderFillRect(render, &salida);
            renderizarTextoBoton(render, fuente, "ESC - Atras", &salida);

            SDL_RenderPresent(render);
        }
    }

    //limpieza de recursos
    if(fondo != NULL)
    {
        SDL_DestroyTexture(fondo);
    }

    TTF_CloseFont(fuente);
    TTF_Quit();
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(ventana);
    SDL_Quit();

    return 0;
}

