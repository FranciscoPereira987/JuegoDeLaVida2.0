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

typedef unsigned int uint;

/*
 *
 */
class Tablero{

private:

	uint filas;
	uint columnas;

	Celula** juego;

	/*
	 * Pre: El nrFila y el nrColumna debe ser
	 * valido
	 * Post: Se le agrega puntaje a las celulas
	 * adyacentes
	 */
	void contarAdyacentes(uint nrFila, uint nrColumna);

	/*
	 * Post: Se libera la memoria de los punteros
	 */
	void limpiarPunteros();

	/*
	 * Post: Se libera la memoria ocupada por las
	 * celulas
	 */
	void limpiarCelulas();

	/*
	 * Post: Devuelve si la posicion pasada
	 * como parametro es valida
	 */
	bool posicionValida(uint nrFila, uint nrColumna);

	/*
	 * Post: Devuelve los puntajes a cero y mata a
	 * las celulas muertas
	 */
	void definirTablero();

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
	void agregarCelula(uint nrFila, uint nrColumna);

	/*
	 * Pre: ---
	 * Post: El tablero se actualiza
	 * al proximo turno
	 */
	void actualizar();



};



#endif /* TABLERO_H_ */
