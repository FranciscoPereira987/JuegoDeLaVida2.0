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

enum Estado{
	MUERTA = 0,
	VIVA
};

#define PRIMERA 0

/*
 *
 */
class Celula{

private:

	bool estado;

	bool cambioDeEstado;

	char puntaje;

	Lista<InformacionGenetica>* genes;


	/*
	 * Post: aplica las reglas del
	 * juego de la vida a la celula
	 */
	void aplicarReglas(int nrTurno);

	/*
	 * Post: pone el puntaje de la celula
	 * en cero
	 */
	void resetearPuntaje();

	/*
	 * pre: Debe haber tres cargas
	 * geneticas
	 * Post: devuelve el minimo
	 * de los tres genes superiores
	 */
	InformacionGenetica devolverMaximo();

	/*
	 * Pre: Debe haber tres padres
	 * para la celula(puntaje == 3)
	 * Post: Devuelve la mezcla de
	 * genes de la celula y pasa el puntaje a 0
	 */
	void mezclarGenes(int nrTurno);

	/*
	 * Pre: Debe haber tres secuencias
	 * geneticas disponibles
	 * Post: Segun el maximo, transfiere
	 * ese gen a las celulas
	 */
	void transferir(InformacionGenetica minimo,
			Lista<InformacionGenetica>* cargaFinal, int nrTurno);

	/*
	 * Pre: Debe haber tres cargas geneticas
	 * para transferir
	 * Post: Genera la carga genetica de la celula
	 */
	void transferenciaTriple(Lista<InformacionGenetica>* cargaFinal,
			int nrTurno);

	/*
	 * Pre: Debe haber dos cargas geneticas
	 * para transferir
	 * Post: Genera la carga genetica de la celula
	 */
	void transferenciaDoble(int primero, int segundo,
			Lista<InformacionGenetica>* cargaFinal, int nrTurno);

	/*
	 * Pre: Debe haber una unica carga genetica para
	 * transferir
	 * Post: Genera la carga genetica de la celula
	 */
	void transferenciaSimple(int indice,
			Lista<InformacionGenetica>* cargaFinal, int nrTurno);

	/*
	 * Post: Libera la memoria utilizada por los genes
	 */
	void destruirGenes();

	/*
	 * Pre: La celula tiene que tener 3 padres
	 * Post: nace la celula
	 */
	void nacer(int nrTurno);

public:

	/*
	 * Pre: La celula debe tener un padre
	 * Post: Crea una celula muerta
	 * con puntaje cero con genes
	 * y la carga genetica del padre
	 */
	Celula(Lista<InformacionGenetica> genesPadre);

	/*
	 * Post: ---
	 */
	~Celula();


	/*
	 * Pre: La celula debe estar muerta y su puntaje
	 * debe ser menor a 3
	 * Post: Le agrega un padre a la celula
	 */
	void agregarPadre(Lista<InformacionGenetica> nuevoPadre);

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
	 * post: Devuelve el cambio de estado de la celula
	 */
	bool obtenerCambio();

	/*
	 * Post: define el estado de la celula segun
	 * su puntaje
	 */
	void decidirEstado(int nrTurno);

	/*
	 * Pre: La celula debe estar viva
	 * Post: Devuelve la carga genetica de la
	 * celula
	 */
	Lista<InformacionGenetica>* obtenerGenes();

};



#endif /* CELULA_H_ */
