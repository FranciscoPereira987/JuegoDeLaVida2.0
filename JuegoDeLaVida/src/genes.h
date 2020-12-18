/*
 * genes.h
 *
 *  Created on: Dec 11, 2020
 *      Author: francisco
 */

#ifndef GENES_H_
#define GENES_H_

#include "lista.h"
#include "informacionGenetica.h"
#include "pila.h"


enum tranferidos{

	NOTRANSFERIDOS = 0,
	TRANSFERIDOS = 1
};

#define PRIMERA 0

/*
 * Clase genes:
 * 				Se compone de una lista de Informacion genetica
 * 				y un booleano que determina si se realizo la
 * 				transferencia de los mismos.
 *
 */
class Genes{

private:

	Lista<InformacionGenetica>* cargaGenetica;

	bool transferidos;

	int progenitores;

	/*
	 * Post: Devuelve el siguiente gen
	 * para la mezcla de los mismos
	 */
	InformacionGenetica devolverMaximo();

	/*
	 * Pre: La celula no haber completado
	 * el proceso de transferencia
	 * Post: cargaGenetica deja de tener
	 * espacio para tres secuencias de genes
	 */
	void reacomodarCargaGenetica();

	/*
	 * Post: Reordena la carga genetica para
	 * que solamente pueda contener una secuencia
	 * de genes
	 */
	void finalizarTransferencia(Lista<InformacionGenetica>* cargaFinal);

	/*
	 * Post: Transfiere los genes de los progenitores
	 * para generar la carga genetica final
	 */
	void transferir(InformacionGenetica maximo,
			Lista<InformacionGenetica>* cargaFinal,
			Pila<InformacionGenetica>* genesACombinar,
			int nrTurno);

	/*
	 * Pre: Debe haber tres cargas geneticas
	 * para transferir
	 * Post: Genera la carga genetica de la celula
	 */
	void transferenciaTriple(Lista<InformacionGenetica>* cargaFinal,
			Pila<InformacionGenetica>* genesACombinar,
			int nrTurno);

	/*
	 * Pre: Debe haber dos cargas geneticas
	 * para transferir
	 * Post: Genera la carga genetica de la celula
	 */
	void transferenciaDoble(int primero, int segundo,
			Pila<InformacionGenetica>* genesACombinar,
			Lista<InformacionGenetica>* cargaFinal, int nrTurno);

	/*
	 * Pre: Debe haber una unica carga genetica para
	 * transferir
	 * Post: Genera la carga genetica de la celula
	 */
	void transferenciaSimple(int indice,
			Pila<InformacionGenetica>* genesACombinar,
			int nrTurno);

	/*
	 * Pre: Debe haber al menos un gen para combinar
	 * Post: Combina los genes dando lugar al gen mutado
	 * y lo devuelve
	 */
	InformacionGenetica combinarGenes(Pila<InformacionGenetica>* genesACombinar,
			int nrTurno);

	/*
	 * Post: Revisa si un gen se encuentra en
	 * la base de genes, si no es asi. Lo agrega.
	 * Si, en cambio, se encuentra. Cambia su edad.
	 */
	void revisarGen(InformacionGenetica genARevisar,
			Lista<InformacionGenetica>* cargaFinal,
			Lista<InformacionGenetica>* baseGenetica);


public:

	/*
	 * Post: Genera una instancia de carGenetica en base
	 * a un conjunto de genes, los inicializa como transferidos
	 */
	Genes(Lista<InformacionGenetica> genes);

	/*
	 * Post: Genera una celula con una cargaGenetica no
	 * transferida
	 */
	Genes(Genes& genesPadre, bool listos = true);

	/*
	 * Post: ---
	 */
	~Genes();

	/*
	 * Pre: Los genes no deben de haber sido transferidos
	 *
	 * Post: Se agrega la carga genetica de un progenitor si
	 * es que hay menos de tres progenitores. Si no, se agrega
	 * un progenitor pero no sus genes
	 */
	void agregarProgenitor(Genes progenitor);


	/*
	 * Pre: Debe haber tres progenitores
	 * Post: Se realiza la mezcla de los genes
	 */
	void mezclarGenes(int nrTurno, Lista<InformacionGenetica>* baseGenetica);

	/*
	 * Pre: Los genes deben de estar transferidos
	 * Post: Devuelve los genes
	 */
	Lista<InformacionGenetica>* obtenerGenes();

	/*
	 * Post: Devuelve la cantidad de progenitores
	 */
	int obtenerProgenitores();

	/*
	 * Post: Setea la cantidad de progenitores a cero
	 */
	void resetearProgenitores();


};


#endif /* GENES_H_ */
