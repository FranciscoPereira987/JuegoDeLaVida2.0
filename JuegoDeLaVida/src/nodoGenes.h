/*
 * nodoGenes.h
 *
 *  Created on: 17 Dec 2020
 *      Author: luca
 */

#ifndef NODOGENES_H_
#define NODOGENES_H_

#ifndef COLA_H_
#define COLA_H_
#include "colaIntensidades.h"
#endif

#include <iostream>
#include <string>
#include "informacionGenetica.h"
#include "lista.h"

using std::string;

class NodoGen{

private:

	string gen;

	unsigned int intensidad;

	unsigned int primerTurno;

	Cola* intensidadesAcumuladas;

	NodoGen* siguiente;

public:

	/*
	 * pre: el gen debe existir en el tablero
	 * 		el turno es el primer turno en el cual se lo empieza a seguir
	 * post: crea un nodo con el siguiente en NULL
	 */
	NodoGen(string genASeguir, unsigned int turno);

	/*
	 * Post: Crea un nodo en base a otro
	 */
	NodoGen(const NodoGen &otro);

	/*
	 * post: devuelve el gen
	 */
	string obtenerGen();

	/*
	 * Post: Devuelve la cantidad de elementos acolados
	 */
	unsigned int obtenerLongitudCola();

	/*
	 * Post: Devuelve la intesidad maxima acolada
	 */
	unsigned int obtenerMaximaIntesidad();

	/*
	 * post: devuelve el turno en que se comenzo a seguir
	 */
	unsigned int obtenerTurno();

	/*
	 * pre: intensidadCelula es la carga genetica de una celula determinada
	 * post: suma la carga genetica a la intensidad acumulada
	 */
	void sumarIntensidad(unsigned int intensidadCelula);

	/*
	 * post: devuelve si hay  mas intensidades en la cola
	 */
	bool estaVacia();

	/*
	 * pre: la cola no debe estar vacia
	 * post: devuelve la intensidad acumulada de un turno
	 */
	unsigned int obtenerIntensidad();

	/*
	 *
	 * post: devuelve el siguiente elemento en la cola
	 */
	NodoGen* obtenerSiguiente();

	/*
	 * pre: la intensidad es la intensidad acumulada en un determinado turno
	 * post: agrega la intensidad del turno a la cola
	 */
	void agregarIntensidad();

	/*
	 * post: cambia el siguiente elemento
	 */
	void cambiarSiguiente(NodoGen* nuevoSiguiente);

	bool operator==(InformacionGenetica gen);

	bool operator!=(NodoGen otroValor);
	bool operator==(NodoGen otroValor);

	bool buscarGen(Lista<InformacionGenetica>* gen);

	~NodoGen();

};




#endif /* NODOGENES_H_ */
