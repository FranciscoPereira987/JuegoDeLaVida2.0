/*
 * celula.h
 *
 *  Created on: Dec 3, 2020
 *      Author: shory
 */

#ifndef CELULA_H_
#define CELULA_H_

#include "lista.h"
#include "informacionGenetica.h"

#include "genes.h"

enum Estado{
	MUERTA = 0,
	VIVA
};
/*
 *
 */
class Celula{

private:

	bool estado;

	bool cambioDeEstado;

	Genes* genes;


	/*
	 * Post: aplica las reglas del
	 * juego de la vida a la celula
	 */
	void aplicarReglas(int nrTurno, Lista<InformacionGenetica>* baseGenetica);

	/*
	 * Post: pone el puntaje de la celula
	 * en cero
	 */
	void resetearPuntaje();

	/*
	 * Pre: La celula tiene que tener 3 padres
	 * Post: nace la celula
	 */
	void nacer(int nrTurno, Lista<InformacionGenetica>* baseGenetica);

	/*
	 * Pre: La celula debe tener tres padres
	 * Post: Se realiza la mezcla de genes
	 */
	void mezclarGenes(int nrTurno, Lista<InformacionGenetica>* baseGenetica);

public:

	/*
	 * Pre: La celula debe tener un padre
	 * Post: Crea una celula muerta
	 * con puntaje uno con genes
	 * y la carga genetica del padre
	 */
	Celula(Genes genesPadre);

	/*
	 * post: Se crea una celula viva
	 * con la carga genetica deseada
	 */
	Celula(Lista<InformacionGenetica> cargaGenetica);

	/*
	 * Post: ---
	 */
	~Celula();


	/*
	 * Pre: La celula debe estar muerta y su puntaje
	 * debe ser menor a 3
	 * Post: Le agrega un padre a la celula
	 */
	void agregarPadre(Genes nuevoPadre);

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
	void sumarVecina(Genes progenitor);

	/*
	 * Post: Devuelve el estado actual de la
	 * celula
	 */
	bool obtenerEstado();

	/*
	 * post: Devuelve el cambio de estado de la celula
	 */
	bool obtenerCambio();

	/*
	 * Post: define el estado de la celula segun
	 * su puntaje
	 */
	void decidirEstado(int nrTurno,
			Lista<InformacionGenetica>* baseGenetica);

	/*
	 * Pre: La celula debe estar viva
	 * Post: Devuelve la carga genetica de la
	 * celula
	 */
	Genes obtenerGenes();

	/*
	 * Post: Envejece los genes de la celula
	 */
	void envejecerGenes();

};



#endif /* CELULA_H_ */
