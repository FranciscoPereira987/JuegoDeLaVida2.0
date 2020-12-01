/*
 * celula.h
 *
 *  Created on: Dec 1, 2020
 *      Author: francisco
 */

#ifndef CELULA_H_
#define CELULA_H_

/*
 *
 */
class Celula{

private:

	bool estado;

	char puntaje;

	/*
	 * Post: aplica las reglas del
	 * juego de la vida a la celula
	 */
	void aplicarReglas();

	/*
	 * Post: pone el puntaje de la celula
	 * en cero
	 */
	void resetearPuntaje();

public:

	/*
	 * Post: Crea una celula muerta
	 * con puntaje cero
	 */
	Celula();

	/*
	 * pre: La celula debe estar muerta
	 * Post: Cambia el estado de una celula
	 * a viva
	 */
	void nacer();

	/*
	 * Post: Aumenta en uno el puntaje
	 * de la celula
	 */
	void sumarVecina();

	/*
	 * Post: Devuelve el estado actual de la
	 * celula
	 */
	bool obtenerEstado();

	/*
	 * Post: define el estado de la celula segun
	 * su puntaje
	 */
	void decidirEstado();
};


#endif /* CELULA_H_ */
