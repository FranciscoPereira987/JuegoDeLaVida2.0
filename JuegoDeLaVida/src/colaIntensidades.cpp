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

	longitud = 0;
}

Cola::Cola(const Cola & otra){
	if(!otra.frente){
		this->frente = NULL;
		this->fondo = NULL;
		this->longitud = 0;
	}
	else{
		Nodo<unsigned int>* actual = otra.frente;

		while (actual){
			this->acolar(actual->getValue());
			actual = actual->getNext();
		}

		this->longitud = otra.longitud;
	}

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

	this->longitud++;
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

	this->longitud--;

	return elemento;
}


unsigned int Cola::obtenerMaximo(){

	Nodo<unsigned int>* cursor = this->frente;
	unsigned int maximo = 0;

	while(cursor){

		if(cursor->getValue() > maximo){
			maximo = cursor->getValue();
		}

		cursor = cursor->getNext();

	}

	return maximo;

}

int Cola::obtenerLongitud(){

	return this->longitud;
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


