/*
 * cola.h
 *
 *  Created on: 17 Dec 2020
 *      Author: luca
 */

#ifndef COLAINTENSIDADES_H_
#define COLAINTENSIDADES_H_



#include <iostream>

#include <string>

#include "nodo.h"

class Cola{

private:

	Nodo<unsigned int>* frente;

	Nodo<unsigned int>* fondo;

public:

	/*
	 * post: crea la cola vacia.
	 */
	Cola();

	/*
	 * post: devuelve si no hay elementos en la cola
	 */
	bool estaVacia();

	/*
	 * post: agrega un elemonto en el fondo de la lista
	 */
	void acolar(unsigned int elemento);

	/*
	 * pre: la cola no debe estar vacia
	 * post: remueve el frente de la cola y lo devuelve
	 */
	unsigned int desacolar();

	/*
	 * pre: la cola no esta vacia
	 * post: devuelve el frente de la cola
	 */
	unsigned int obtenerFrente();

	/*
	 * post: remueve los elementos y libera la memoria
	 */
	~Cola();
};








#endif /* COLA_H_ */
