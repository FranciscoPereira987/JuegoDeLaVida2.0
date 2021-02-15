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

	unsigned int longitud;

public:

	/*
	 * post: crea la cola vacia.
	 */
	Cola();

	/*
	 * Post: Crea una cola copia de otra
	 */
	Cola(const Cola &otra);

	/*
	 * post: devuelve si no hay elementos en la cola
	 */
	bool estaVacia();

	/*
	 * post: agrega un elemonto en el fondo de la lista
	 */
	void acolar(unsigned int elemento);

	/*
	 * Post: Devuelve la cantidad de elementos que hay en la cola
	 */
	int obtenerLongitud();

	/*
	 * Post: Devuelve el maximo valor que hay en la cola
	 */
	unsigned int obtenerMaximo();


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
