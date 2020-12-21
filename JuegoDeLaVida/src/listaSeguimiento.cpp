/*
 * listaSeguimiento.cpp
 *
 *  Created on: 17 Dec 2020
 *      Author: luca
 */

#include <iostream>
#include <string>
#include "listaSeguimiento.h"
#include "nodoGenes.h"

using std::string;

ListaSeguimiento::ListaSeguimiento(){

	cursor = NULL;
	primerElemento = NULL;
}

ListaSeguimiento::ListaSeguimiento(string gen, unsigned int turno){

	primerElemento = new NodoGen(gen, turno);

	cursor = primerElemento;
}

void ListaSeguimiento::insertar(string gen, unsigned int turno){

	NodoGen* nuevoGen = new NodoGen(gen, turno);

	nuevoGen->cambiarSiguiente(primerElemento);

	primerElemento = nuevoGen;

}

bool ListaSeguimiento::estaVacia(){
	return (primerElemento == NULL);
}

void ListaSeguimiento::avanzarCursor(){
	cursor = cursor->obtenerSiguiente();
}

bool ListaSeguimiento::colaVacia(){
	return cursor->estaVacia();
}

void ListaSeguimiento::reiniciarCursor(){
	cursor = primerElemento;
}



bool ListaSeguimiento::buscarEnLalista(Lista<InformacionGenetica>* lista){
	return cursor->buscarGen(lista);
}

void ListaSeguimiento::compararGenes(Lista<InformacionGenetica>* lista){
	this->reiniciarCursor();
	while(cursor != NULL){

		if((cursor!= NULL) &&(this->buscarEnLalista(lista))){
			this->agregarIntensidad(lista->obtenerCursor()->obtenerIntensidad());
		}
		this->avanzarCursor();
	}
}

void ListaSeguimiento::finalizarAcumulacion(){
	this->reiniciarCursor();
	while(cursor != NULL){
		this->acolarIntensidad();
		this->avanzarCursor();
	}
}

string ListaSeguimiento::obtenerGen(){
	return cursor->obtenerGen();
}

bool ListaSeguimiento::buscarGen(string gen){

	this->reiniciarCursor();

	bool estaEnLaLista = false;

	if(!this->estaVacia()){
		while((cursor != NULL) && (gen != this->obtenerGen())){
			this->avanzarCursor();
		}

		if((cursor != NULL) && (this->obtenerGen() == gen)){
			estaEnLaLista = true;
		}
	}
	return estaEnLaLista;
}

void ListaSeguimiento::agregarIntensidad(unsigned int intensidad){
	cursor->sumarIntensidad(intensidad);
}

void ListaSeguimiento::acolarIntensidad(){
	cursor->agregarIntensidad();
}

unsigned int ListaSeguimiento::obtenerIntensidad(){
	return cursor->obtenerIntensidad();
}

unsigned int ListaSeguimiento::obtenerTurno(){
	return cursor->obtenerTurno();
}

void ListaSeguimiento::detenerSeguimiento(string gen){
	this->reiniciarCursor();

	if(this->buscarGen(gen)){

		unsigned int turnos = this->obtenerTurno();

		std::cout << this->obtenerGen() << std::endl;

		std::cout << "Turno" << " | "  << "Intensidad acumulada" << std::endl;
		while(!this->colaVacia()){
			std::cout << turnos << "  " << this->obtenerIntensidad() << std::endl;
			turnos ++;
		}
		std::cout << std::endl;
		if(cursor == primerElemento){
			primerElemento = cursor->obtenerSiguiente();
			NodoGen* actual = cursor;
			this->reiniciarCursor();
			delete actual;
		}
	}

}

ListaSeguimiento::~ListaSeguimiento(){
	this->reiniciarCursor();
	NodoGen* actual;
	while(!this->estaVacia()){
		actual = cursor;
		this->avanzarCursor();
		primerElemento = cursor;
		delete actual;

	}
}
