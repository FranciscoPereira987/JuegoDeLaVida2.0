/*
 * tablero.h
 *
 *  Created on: Dec 1, 2020
 *      Author: francisco
 */

#ifndef TABLERO_H_
#define TABLERO_H_

#ifndef CELULA
#define CELULA
#include "celula.h"
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef STRING
#define STRING
#include <string>
using std::string;
#endif

typedef unsigned int uint;

/*
 *
 */
class Tablero{

private:

	int filas;
	int columnas;

	Celula*** juego;

	/*
	 * Pre: El nrFila y el nrColumna debe ser
	 * valido
	 * Post: Se le agrega puntaje a las celulas
	 * adyacentes
	 */
	void contarAdyacentes(int nrFila, int nrColumna);

	/*
	 * Pre: nrFila y nrColumna deben ser validos
	 * y debe haber una celula viva en una posicion
	 * adyacente
	 * Post: Se crea una celula con puntaje uno si no
	 * habia ninguna, caso contrario. Se le suma una vecina
	 */
	void contarVecina(int nrFila, int nrColumna);

	/*
	 * Post: Se libera la memoria de los punteros
	 */
	void limpiarTablero();

	/*
	 * Pre: La fila debe ser valida
	 * Post: Libera el espacio de esa fila
	 */
	void limpiarFila(int fila);

	/*
	 * pre: la fila y columna deben ser validas
	 * ademas, debe haber una celula en ese lugar
	 * Post: Se libera la memoria ocupada por las
	 * celulas
	 */
	void limpiarCelula(int fila, int columna);

	/*
	 * Post: Devuelve si la posicion pasada
	 * como parametro es valida
	 */
	bool posicionValida(int nrFila, int nrColumna);

	/*
	 * Post: Devuelve los puntajes a cero y mata celulas muertas
	 */
	void definirTablero();

	/*
	 * pre: nrFila y nrColumna deben ser validos
	 * Post: Devuelve si en esa posicion del tablero hay una
	 * celula y si la misma esta muerta
	 */
	bool celulaMuerta(int nrFila, int nrColumna);

	/*
	 * Post: inicializa todos los punteros a celula como NULL
	 */
	void inicializarFila(Celula**& fila);



public:
	/*
	 * pre: cantFilas y cantColumnas deben ser
	 * mayores a 0
	 * Post:Se crea el tablero
	 */
	Tablero(int cantFilas, int cantColumnas);

	/*
	 * Post: ---
	 */
	~Tablero();

	/*
	 * pre: el nrFila y el nrColumna deben
	 * ser validos entre [1-cantX]
	 * post: Se agrega una celula viva en
	 * esa posicion
	 */
	void agregarCelula(int nrFila, int nrColumna);

	/*
	 * Pre: ---
	 * Post: El tablero se actualiza
	 * al proximo turno
	 */
	void actualizar();

	/*
	 * Post: imprime el tablero
	 */
	void imprimirTablero();

};



#endif /* TABLERO_H_ */
