/*
 * colaIntensidades.cpp
 *
 *  Created on: 17 Dec 2020
 *      Author: luca
 */

#include <string>
#include "colaIntensidades.h"

using std::string;

Cola::Cola(){

	frente = NULL;
	fondo =NULL;
}


bool Cola::estaVacia(){
	return (frente == NULL);
}


void Cola::acolar(unsigned int elemento){

	Nodo<unsigned int>* nuevoFondo = new Nodo<unsigned int>(elemento);

	if(this->estaVacia()){
		frente = nuevoFondo;
	} else{
		fondo->setNext(nuevoFondo);
	}

	fondo = nuevoFondo;
}


unsigned int Cola::desacolar(){

	if(this->estaVacia()){
		throw std::string("No se puede desacolar. Cola vacia");
	}

	Nodo<unsigned int>* frenteAnterior = frente;
	frente = frenteAnterior->getNext();

	if(frente == NULL){
		fondo = NULL;
	}

	unsigned int elemento = frenteAnterior->getValue();
	delete frenteAnterior;

	return elemento;
}


unsigned int Cola::obtenerFrente(){

	if(this->estaVacia()){
		throw std::string("no se puede obtener el frente, la cola esta vacia");
	}

	unsigned int elemento = frente->getValue();

	return elemento;
}


Cola::~Cola(){

	while(!this->estaVacia()){
		this->desacolar();
	}
}


