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

NodoGen::NodoGen(const NodoGen &otro){

	this->gen = otro.gen;
	this->intensidad = otro.intensidad;
	this->primerTurno = otro.primerTurno;
	this->intensidadesAcumuladas = new Cola(*otro.intensidadesAcumuladas);
	this->siguiente = otro.siguiente;

}

string NodoGen::obtenerGen(){
	return gen;
}

unsigned int NodoGen::obtenerTurno(){
	return primerTurno;
}

unsigned int NodoGen::obtenerLongitudCola(){

	return this->intensidadesAcumuladas->obtenerLongitud();
}

unsigned int NodoGen::obtenerMaximaIntesidad(){

	return this->intensidadesAcumuladas->obtenerMaximo();
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

bool NodoGen::operator ==(NodoGen otroValor){

	return (this->obtenerGen() == otroValor.obtenerGen());

}

bool NodoGen::operator !=(NodoGen otroValor){


	return !(this->operator ==(otroValor));
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


