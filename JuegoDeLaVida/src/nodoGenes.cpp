/*
 * nodoGenes.cpp
 *
 *  Created on: 17 Dec 2020
 *      Author: luca
 */

#include <iostream>
#include <string>
#include "nodoGenes.h"
#include "lista.h"

using std::string;

NodoGen::NodoGen(string genASeguir, unsigned int turno){
	gen = genASeguir;
	primerTurno = turno;
	intensidad = 0;
	intensidadesAcumuladas = new Cola;
	siguiente = NULL;
}

string NodoGen::obtenerGen(){
	return gen;
}

unsigned int NodoGen::obtenerTurno(){
	return primerTurno;
}

bool NodoGen::estaVacia(){
	return intensidadesAcumuladas->estaVacia();
}

void NodoGen::sumarIntensidad(unsigned int intensidadCelula){
	intensidad += intensidadCelula;
}

unsigned int NodoGen::obtenerIntensidad(){
	return intensidadesAcumuladas->desacolar();
}

NodoGen* NodoGen::obtenerSiguiente(){
	return siguiente;
}

void NodoGen::agregarIntensidad(){
	intensidadesAcumuladas->acolar(intensidad);
	intensidad = 0;
}

void NodoGen::cambiarSiguiente(NodoGen* nuevoSiguiente){
	siguiente = nuevoSiguiente;
}

bool NodoGen::operator==(InformacionGenetica genetica){
	return (genetica.devolverBits() == this->gen);
}

bool NodoGen::buscarGen(Lista<InformacionGenetica>* gen){

	gen->inicializarCursor();
	while((!gen->finDeLaLista()) && !(this->operator ==(*(gen->obtenerCursor())))){
		gen->avanzarCursor();
	};
	return (!gen->finDeLaLista() &&
			this->operator ==(*(gen->obtenerCursor())));
}

NodoGen::~NodoGen(){
	delete intensidadesAcumuladas;
}


