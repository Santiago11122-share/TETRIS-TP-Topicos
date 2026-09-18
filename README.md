--DOCUMENTACION TETRIS--

BIBLIOTECAS
	


juego.h:	

Lleva el control del juego, lo inicializa y maneja el flujo principal del juego.
		
		Funciones:
		
		int IniciarJuego();
			inicializa tableros, piezas, interfaz grafica, audio y carga mejor puntaje. Pone a funcionar el juego y al finalizar, cierra las funciones de SDL. En caso de fallas en la inicialización, retorna -1.
		
		int LoopPrincipal();
			Controla la actualización continua del del juego, evalua condicion de fin, procesa las teclas, aplica la caída automática por tiempo, gestiona la eliminación de filas, y dibuja todos los elementos gráficos en pantalla. Retorna 0 cuando finaliza el juego

tablero.h:

Inicializa el tablero y se encarga de colocar las piezas en el tablero del juego, elimina filas y evalúa condición de fin de juego.
	
	Estructuras:
		
		t_tablero
			contiene una matriz de enteros que representa el tablero de juego, contiene 0 si no hay ninguna pieza en la celda, 1 si contiene pieza y 2 si pertenece a los bordes del tablero.
	
	Funciones:
		
		t_tablero inicializarTablero ();
			inicializa y retorna el tablero .
		
		void mostrartablero(t_tablero *tablero);
			muestra el tablero en pantalla con las piezas fijadas.
		
		int hayColision(t_tablero *tablero, t_pieza *pieza, int nuevoX, int nuevoY);
			Evalua si hay colision con otra pieza o con los bordes del tablero luego de un movimiento, retorna 1 si hubo colision y 0 si no hubo.
		
		void rotarPieza(t_tablero *tablero,t_pieza *pieza);
			rota la pieza solo en caso de que no haya colision.
		
		void colocarPieza(t_tablero *tablero, t_pieza *pieza,t_pieza *siguientepieza);
			coloca la pieza en el tablero y guarda la nueva pieza y la siguiente.
		
		int moverpieza_abajo(t_tablero *tablero,t_pieza *pieza,t_pieza *siguientepieza);
			mueve la pieza hacia abajo solo si no hay colision con otra pieza.
		
		void moverpieza(t_tablero *tablero,t_pieza *pieza,t_pieza *siguientepieza,int tecla);
			mueve la pieza a izquierda, derecha, abajo o rota la pieza solo en caso de que no haya colision.
		
		int eliminarFilas(t_tablero *tablero);
			verifica si hay filas completas, en caso de que haya, aumenta un contador y corre las filas por encima hacia abajo. Retorna el contador de filas eliminadas.
		
		int findejuego(t_tablero *tablero,t_pieza *pieza);
			verifica la condición de fin de juego, retorna 1 en caso de que el juego deba continuar y retorna 0 en caso de que el jeugo deba terminar
	
piezas.h:

Crea las piezas y las muestra en función de su posición en el tablero.
	
	Estructuras:
		
		t_pieza
			contiene:
			una matriz de enteros que indica la forma de la pieza, contiene 0 en celdas vacias y 1 en celdas que contengan bloque.
			un entero que indica su posición de columna en el tablero.
			un entero que indica su posición de fila en el tablero.
			un entero que indica el tipo de pieza (1 a 7)
	
	Funciones
		
		t_pieza crearPieza(void);
			Define cada una de las 7 piezas mediante un vector de matrices y elige aleatoriamente una de ellas, guarda su posición de inicio en el tablero (fila 1, columna 4), su tipo, y la forma. Luego retorna estos datos mediante estructura.
		void mostrarpieza(t_pieza *pieza);
			Muestra la pieza en la posición del tablero por cada movimiento.
	
puntaje.h:

Lleva el control del puntaje durante el juego y controla el mejor puntaje histórico.
	
	Funciones
	
	int mejorpuntaje();
		Crea un archivo en caso de que no haya registro, si hay registro, recupera el mejor puntaje. Retorna 		el mejor puntaje o 0 en caso de que no haya registro.
	
	int puntaje(int puntajeant,int filaselim);
		Calcula el puntaje en base a la cantidad de filas eliminadas, retorna el puntaje calculado.
	
	void guardarpuntaje(int puntaje);
		Compara el mejor puntaje histórico recuperado de un registro. Si el puntaje actual es mayor
		que el histórico pisa el registro, en caso contrario, no realiza cambios.
