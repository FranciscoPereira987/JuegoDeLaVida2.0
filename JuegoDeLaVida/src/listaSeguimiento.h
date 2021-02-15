/*
 * seguimientoGenes.h
 *
 *  Created on: 17 Dec 2020
 *      Author: luca
 */

#ifndef LISTASEGUIMIENTO_H_
#define LISTASEGUIMIENTO_H_

#include <iostream>
#include <string>
#include "nodoGenes.h"
#include "lista.h"
#include "EasyBMP.h"
#include "EasyBMP_Geometry.h"


using std::string;

class ListaSeguimiento{

private:

	Lista<NodoGen>* seguimientos;

	/*
	 * post: devuelve si no hay mas intensidades en la cola
	 */
	bool colaVacia();

	/*
	 * Post: Genera el grafico al finalizar el seguimiento de un gen
	 */
	BMP* crearGrafico();


public:


	/*
	 * post: crea una lista vacia
	 */
	ListaSeguimiento();

	/*
	 * post: crea una lista con un elemento
	 */
	ListaSeguimiento(string Gen, unsigned int turno);

	/*
	 * post: agrega un elemento al principio de la lista
	 */
	void insertar(string Gen, unsigned int turno);

	/*
	 * post: el cursor vuelve a la primer posicion de la lista
	 */
	void reiniciarCursor();

	/*
	 * post: devuelve si la lista esta vacia
	 */
	bool estaVacia();

	/*
	 * post: devuelve si el gen a seguir esta en los
	 * 		 genes de la celula
	 */
	bool buscarEnLalista(Lista<InformacionGenetica>* lista);

	/*
	 * post:revisa si hay intensidades para sumar
	 * 		y las agrega al seguimiento
	 */
	void compararGenes(Lista<InformacionGenetica>* lista);

	/*
	 * post: devuelve el gen del elemento apuntado
	 */
	string obtenerGen();

	/*
	 * pre: la lista no debe estar vacia
	 * post: devuelve si un gen esta en la lista y lo apunta
	 */
	bool buscarGen(string gen);

	void finalizarAcumulacion();




	/*
	 * pre: la intensidad es la suma de las intensidades de
	 *  	todas las celulas en un determinado turno
	 * post: agrega la intensidad acumulada de un truno al gen
	 */
	void agregarIntensidad(unsigned int intensidad);

	/*
	 * post: devuelve la intensidad acumulada de cada turno del gen apuntado
	 */
	unsigned int obtenerIntensidad();

	/*
	 * post: agrega la intensidad acumulada del turno en la cola
	 */
	void acolarIntensidad();

	/*
	 * post: devuelve el turno en el que se empezo a seguir el gen del gen apuntado
	 */
	unsigned int obtenerTurno();

	/*
	 * pre: el gen debe estar dentro de la lista de seguimineto
	 * post: devuelve las cargas acumuladas de los turnos en que
	 * 		 se le hizo el seguimiento
	 */

	void detenerSeguimiento(string gen);

	/*
	 * post: se libera la memoria de cada elemento
	 */
	~ListaSeguimiento();
};



#endif /* LISTASEGUIMIENTO_H_ */
